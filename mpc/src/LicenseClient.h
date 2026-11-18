#pragma once
// Pairing and license verification run off the real-time audio thread.
#include <dlfcn.h>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <functional>
#include <string>
#include <thread>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include "3rdparty/json/json.hpp"

class LicenseClient {
public:
 enum State { Unregistered=0, Connecting=1, Waiting=2, Registered=3, Error=4, Expired=5 };
 struct Display { State state; int first; int second; std::string email = {}; };
 using Update = std::function<void(Display)>;
 explicit LicenseClient(Update cb): update(std::move(cb)) {}
 ~LicenseClient() { shutdown(); }
 void shutdown() { stop.store(true); if (worker.joinable()) worker.join(); }
 void start() { if (!worker.joinable()) worker=std::thread([this]{run();}); }
 void begin() { requested.store(true); }
 void removeLicense() { removalRequested.store(true); }
 bool isLicensed() const { return licensed.load(); }
private:
 using json=nlohmann::json;
 std::atomic<bool> stop{false}, requested{false}, removalRequested{false}, licensed{false};
 std::thread worker;
 Update update;
 static constexpr const char* directory="/media/az01-internal-sd/Elsewave/Scatterloom";
 static constexpr const char* filename="/media/az01-internal-sd/Elsewave/Scatterloom/license.json";
 static const unsigned char* publicKey() {
  static const unsigned char key[]={0xad,0x09,0xb9,0x88,0x81,0x45,0x28,0x3d,0xc6,0xd7,0xbd,0x8b,0xe9,0xab,0x2c,0x70,0x00,0x9c,0xb5,0x7d,0xfd,0x66,0x59,0xa4,0x54,0x39,0xd0,0x28,0xee,0x84,0xaa,0xe4}; return key;
 }
 static std::vector<unsigned char> decode(const std::string& s) {
  std::vector<unsigned char> out; unsigned acc=0; int bits=0;
  for (unsigned char c:s) { int v=c>='A'&&c<='Z'?c-'A':c>='a'&&c<='z'?c-'a'+26:c>='0'&&c<='9'?c-'0'+52:c=='-'?62:c=='_'?63:-1; if(v<0)return {}; acc=(acc<<6)|v;bits+=6; if(bits>=8){bits-=8;out.push_back((acc>>bits)&255);} }
  return out;
 }
 static std::string deviceSerial() {
  std::ifstream f("/sys/firmware/devicetree/base/serial-number",std::ios::binary);
  std::string serial; char c;
  while (f.get(c) && c != '\0') { if (serial.size() >= 128) return {}; serial += c; }
  return serial;
 }
 static bool verify(const std::string& text, std::string* verifiedEmail=nullptr) {
  if(text.empty()||text.size()>65536) return false;
  try {
   auto envelope=json::parse(text); if(envelope.value("format","")!="elsewave-license-v1"||envelope.value("algorithm","")!="Ed25519")return false;
   auto msg=decode(envelope.at("payload").get<std::string>()), sig=decode(envelope.at("signature").get<std::string>()); if(msg.empty()||sig.size()!=64)return false;
   void* lib=dlopen("libcrypto.so.3",RTLD_NOW|RTLD_LOCAL); if(!lib)return false;
   auto newkey=reinterpret_cast<void*(*)(void*,const char*,const char*,const unsigned char*,size_t)>(dlsym(lib,"EVP_PKEY_new_raw_public_key_ex"));
   auto keyfree=reinterpret_cast<void(*)(void*)>(dlsym(lib,"EVP_PKEY_free"));
   auto ctxnew=reinterpret_cast<void*(*)()>(dlsym(lib,"EVP_MD_CTX_new"));
   auto ctxfree=reinterpret_cast<void(*)(void*)>(dlsym(lib,"EVP_MD_CTX_free"));
   auto init=reinterpret_cast<int(*)(void*,void**,const void*,void*,void*)>(dlsym(lib,"EVP_DigestVerifyInit"));
   auto check=reinterpret_cast<int(*)(void*,const unsigned char*,size_t,const unsigned char*,size_t)>(dlsym(lib,"EVP_DigestVerify"));
   bool ok=false;
   if(newkey&&keyfree&&ctxnew&&ctxfree&&init&&check){void* key=newkey(nullptr,"ED25519",nullptr,publicKey(),32);void* ctx=ctxnew();if(key&&ctx&&init(ctx,nullptr,nullptr,nullptr,key)==1)ok=check(ctx,sig.data(),sig.size(),msg.data(),msg.size())==1;if(ctx)ctxfree(ctx);if(key)keyfree(key);}
   dlclose(lib); if(!ok)return false;
   auto payload=json::parse(std::string(msg.begin(),msg.end()));
   const std::string email=payload.value("email", "");
   const std::string serial=deviceSerial();
   const bool okFields=!serial.empty() && payload.value("deviceSerial",std::string{})==serial && payload.value("version",0)==1 && payload.value("product","")=="Scatterloom" && !email.empty() && email.size()<=254 && !payload.value("licenseId","").empty();
   if(okFields && verifiedEmail) *verifiedEmail=email;
   return okFields;
  } catch (...) { return false; }
 }
 static bool load(std::string* email=nullptr) {
  std::ifstream f(filename,std::ios::binary); if(!f)return false;
  std::string s; char b[4096]; while(f && s.size()<=65536){f.read(b,sizeof b);s.append(b,static_cast<size_t>(f.gcount()));} return verify(s,email);
 }
 static bool save(const std::string& value) {
  if(!verify(value))return false;
  mkdir("/media/az01-internal-sd/Elsewave",0700);mkdir(directory,0700);
  // Unique name prevents simultaneous instances from overwriting one another's temporary file.
  std::string pattern=std::string(directory)+"/.license-XXXXXX"; std::vector<char> buf(pattern.begin(),pattern.end());buf.push_back(0);
  int fd=mkstemp(buf.data()); if(fd<0)return false;
  FILE* f=fdopen(fd,"wb"); if(!f){close(fd);remove(buf.data());return false;}
  bool ok=fwrite(value.data(),1,value.size(),f)==value.size() && fflush(f)==0; if(fclose(f)!=0)ok=false;
  if(ok)ok=rename(buf.data(),filename)==0; if(!ok)remove(buf.data()); return ok;
 }
 static size_t append(char* ptr,size_t size,size_t count,void* user) {
  auto& s=*static_cast<std::string*>(user); size_t n=size*count; if(n>65536||s.size()+n>65536)return 0;s.append(ptr,n);return n;
 }
 static int progress(void* user, long long, long long, long long, long long) {
  return static_cast<LicenseClient*>(user)->stop.load(std::memory_order_relaxed) ? 1 : 0;
 }
 bool post(const char* path,const json& input,json& output) {
  void* lib=dlopen("libcurl.so.4",RTLD_NOW|RTLD_LOCAL);if(!lib)return false;
  auto init=reinterpret_cast<void*(*)()>(dlsym(lib,"curl_easy_init"));auto set=reinterpret_cast<int(*)(void*,int,...)>(dlsym(lib,"curl_easy_setopt"));auto perform=reinterpret_cast<int(*)(void*)>(dlsym(lib,"curl_easy_perform"));auto cleanup=reinterpret_cast<void(*)(void*)>(dlsym(lib,"curl_easy_cleanup"));auto getinfo=reinterpret_cast<int(*)(void*,int,...)>(dlsym(lib,"curl_easy_getinfo"));
  auto listadd=reinterpret_cast<void*(*)(void*,const char*)>(dlsym(lib,"curl_slist_append"));auto listfree=reinterpret_cast<void(*)(void*)>(dlsym(lib,"curl_slist_free_all"));
  bool ok=false; if(init&&set&&perform&&cleanup&&getinfo&&listadd&&listfree){
   void* c=init();if(c){std::string body=input.dump(), response, url=std::string("https://elsewave.pages.dev/api/pairing/")+path;void* headers=listadd(nullptr,"Content-Type: application/json");
    if(headers){set(c,10002,url.c_str());set(c,10015,body.c_str());set(c,60,(long)body.size());set(c,10023,headers);set(c,10018,"Elsewave-Scatterloom-MPC/1.0");set(c,20011,&append);set(c,10001,&response);set(c,155,4000L);set(c,156,2000L);set(c,99,1L);set(c,43,0L);set(c,20219,&progress);set(c,10057,this);
     long status=0;if(perform(c)==0&&getinfo(c,0x200002,&status)==0&&status==200){try{output=json::parse(response);ok=true;}catch(...){}} listfree(headers);}
    cleanup(c);}
  } dlclose(lib);return ok;
 }
 void run() {
  bool last=false; int tick=0; std::string email;
  if(load(&email)){licensed.store(true);last=true;update({Registered,0,0,email});}else update({Unregistered,0,0});
  while(!stop.load()) {
   if(++tick>=50){tick=0;std::string currentEmail;bool valid=load(&currentEmail);if(valid!=last || (valid && currentEmail!=email)){last=valid;email=currentEmail;licensed.store(valid);update({valid?Registered:Unregistered,0,0,email});}}
   if(removalRequested.exchange(false)) {
    if(std::remove(filename)==0 || errno==ENOENT) {last=false;email.clear();licensed.store(false);update({Unregistered,0,0});}
    else update({Registered,0,0,email});
   }
   if(requested.exchange(false)){
    update({Connecting,0,0}); json session; auto requestStarted=std::chrono::steady_clock::now();
    const std::string serial=deviceSerial();
    if(serial.empty() || !post("start",{{"deviceSerial",serial}},session)){update({last?Registered:Error,0,0,email});}
    else try {
     std::string code=session.at("code").get<std::string>(), token=session.at("token").get<std::string>();
     static constexpr const char* alphabet="0123456789abcdefghijklmnpqrstuvwxyz";
     if(code.size()!=5 || token.size()!=64)throw 1;
     int a=0,b=0;
     for (size_t i=0;i<code.size();++i) {
      const char* digit=std::strchr(alphabet,code[i]); if(!digit)throw 1;
      if(i<2) a=a*35+static_cast<int>(digit-alphabet);
      else b=b*35+static_cast<int>(digit-alphabet);
     }
     update({Waiting,a,b});
     // The server creates the code after the request starts; expire locally
     // conservatively so a code is never presented as valid for too long.
     auto until=requestStarted+std::chrono::minutes(10)-std::chrono::seconds(1);
     while(!stop.load()&&std::chrono::steady_clock::now()<until){
      for(int i=0;i<30&&!stop.load()&&std::chrono::steady_clock::now()<until;++i)std::this_thread::sleep_for(std::chrono::milliseconds(100));
      if(stop.load())break;
      if(std::chrono::steady_clock::now()>=until)break;
      if(!last && load(&email)){licensed.store(true);last=true;update({Registered,0,0,email});break;}
      if(requested.exchange(false)){requested.store(true);break;}
      json response;
      if(post("poll",{{"code",code},{"token",token}},response)&&response.value("status","")=="complete"){
       std::string record=response.at("license").dump();if(save(record) && load(&email)){licensed.store(true);last=true;update({Registered,0,0,email});}else update({last?Registered:Error,0,0,email});break;
      }
     }
     if(!stop.load()&&!requested.load() && !licensed.load() && std::chrono::steady_clock::now()>=until)update({Expired,a,b});
     else if(!stop.load() && last) update({Registered,0,0,email});
    }catch(...){update({last?Registered:Error,0,0,email});}
   }
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
 }
};

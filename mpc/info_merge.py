"""Generate the four-page Info screen."""
import json
import subprocess
from PIL import Image, ImageDraw, ImageFont


def combine_info(raw, skins, version):
    data = json.loads(raw)
    pd = data['pageData']
    tabs = pd['tabs']
    info = next(t for t in tabs if t['tabName'] == 'INFO')
    definitions = pd['componentDefinitions']['localComponentDefinitions']
    def font(size):
        try: return ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc', size)
        except OSError: return ImageFont.load_default()
    def bounds(rect, conditions=()):
        return {'version':2,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':rect,'additionalInvalidatingHandles':list(conditions)}
    def component(name, image_name, rect, conditions=(), type_name='Image'):
        d={'version':2,'imageType':'Regular','colour':'0','image':image_name} if type_name=='Image' else {'version':1,'handleName':'Data'}
        return {'version':2,'componentData':{'version':1,'name':name,'type':type_name,'data':d},'handle remapping':{'version':1,'map':[]},'bounds':bounds(rect,conditions)}
    def choice(handle,index): return 'IndexedEnabling/%d/2/Local/2/%s' % (index,handle)
    for name, symbol in [('info-prev.png','‹'),('info-next.png','›')]:
        im=Image.new('RGBA',(72,260),(0,0,0,0)); d=ImageDraw.Draw(im)
        d.rounded_rectangle((2,2,69,257),radius=8,fill='#253d38',outline='#729a8c',width=2)
        d.text((36,130),symbol,anchor='mm',font=font(58),fill='#f0e6d6'); im.save(skins/name)
    for name,image,handles in [('InfoPagePrevOne','info-prev.png',['infoPageLow']),('InfoPagePrevTwo','info-prev.png',['infoPageLow','infoPageHigh']),('InfoPageNextOne','info-next.png',['infoPageLow']),('InfoPageNextTwo','info-next.png',['infoPageLow','infoPageHigh']),('InfoPageNextThree','info-next.png',['infoPageLow','infoPageHigh','infoPageTop']),('InfoPagePrevThree','info-prev.png',['infoPageLow','infoPageHigh','infoPageTop'])]:
        definitions.append({'key':name,'value':{'version':2,'actions':[{'version':1,'onAction':'Mouse Down','handler':'Toggle Switch','handleName':'Local/2/'+h,'additionalData':''} for h in handles], 'backgroundData':{'version':1,'focussed':{'version':1,'colour':'0','image':''},'unfocussed':{'version':1,'colour':'0','image':''}},'ignoreMousePresses':False,'disableCoarseDataWheel':False,'componentsData':[component(name+' art',image,'0 0 72 260')]}})
    swift = r'''import AppKit
import CoreImage
let filter = CIFilter(name: "CIQRCodeGenerator")!
filter.setValue("https://ko-fi.com/elsewavedsp".data(using: .utf8)!, forKey: "inputMessage")
filter.setValue("M", forKey: "inputCorrectionLevel")
let qr = filter.outputImage!.transformed(by: CGAffineTransform(scaleX: 6, y: 6))
let context = CIContext(options: nil)
let cg = context.createCGImage(qr, from: qr.extent)!
let rep = NSBitmapImageRep(cgImage: cg)
try! rep.representation(using: .png, properties: [:])!.write(to: URL(fileURLWithPath: CommandLine.arguments[1]))
'''
    qr_raw=skins/'info-tip-qr-raw.png'
    subprocess.run(['/usr/bin/swift','-',str(qr_raw)],input=swift,text=True,check=True)
    qr=Image.open(qr_raw).convert('RGBA')
    im=Image.new('RGBA',(qr.width+48,qr.height+48),'white'); im.alpha_composite(qr,(24,24)); im.save(skins/'info-tip-qr.png'); qr_raw.unlink()
    pages=[('THANK YOU',['Thanks for trying out Scatterloom.', 'I hope it helps you interface your warm,', 'human heart with cold data.', "If you'd like to buy me an Americano,", 'scan the QR or go to:', 'ko-fi.com/elsewavedsp']),('CAPTURE',['Route audio into Scatterloom and turn Capture on.','A signal crossing the sensitivity threshold captures a grain.','Adjust Sensitivity or use Auto Sens on the Settings page.','The pool holds up to nine grains; the pads show its contents.','Turn Capture off to keep the pool while you play.','Clear Pool removes the captured grains.']),('PATTERN',['Steps set the length of the rhythmic cycle; Pulses set','how many triggers are spread across those steps.','For example, 7 pulses over 16 steps creates seven hits.','Division sets the rhythmic rate; Rotate shifts the pattern.','The ring shows the steps, playhead and grain lengths.','Grain Length controls how long each captured grain plays.']),('GRAIN SELECTION',['Recent Grains limits selection to the newest pool entries.','On Pattern, each row represents the current grain; each','column represents a possible next grain. The cell bars','show their probabilities: larger bars are more likely.','Choose a pattern preset, or tap a cell to adjust it.','Only captured grains within Recent Grains are available.']),('CREDITS AND LICENSES',['Scatterloom © Elsewave — MIT License',"RNBO © Cycling '74 — MIT runtime; Export/GPLv3 code",'MPC Plugin Builder SDK © inMusic — MIT','Queues © Cameron Desrochers — BSD; Jeff Preshing — zlib','JSON for Modern C++ © Niels Lohmann — MIT','Full license texts are included in the Licenses folder.'])]
    items=[]
    for idx,(title,lines) in enumerate(pages):
        im=Image.new('RGBA',(1080,390),(0,0,0,0)); d=ImageDraw.Draw(im)
        d.text((0,0),title,font=font(36),fill='#efb05c')
        for row,line in enumerate(lines): d.text((0,70+row*40),line,font=font(27),fill='#9bd4c3' if idx==0 and row==5 else '#f0e6d6')
        d.text((0,340),'PAGE %d / 5'%(idx+1),font=font(20),fill='#9bbdb3'); image='info-page-%d.png'%idx; im.save(skins/image)
        cond=[choice('infoPageTop',idx//4),choice('infoPageHigh',(idx//2)%2),choice('infoPageLow',idx%2)]
        items.append(component('Help page %d'%(idx+1),image,'100 80 1080 390',cond))
        if idx == 0: items.append(component('Ko-fi QR','info-tip-qr.png','900 125 %d %d' % (qr.width+48, qr.height+48),cond))
        if idx: items.append(component('Previous help page','','10 145 72 260',cond,'InfoPagePrevThree' if idx==4 else ('InfoPagePrevTwo' if idx==2 else 'InfoPagePrevOne')))
        if idx<4: items.append(component('Next help page','','1198 145 72 260',cond,'InfoPageNextThree' if idx==3 else ('InfoPageNextTwo' if idx==1 else 'InfoPageNextOne')))
    im=Image.new('RGBA',(480,48),(0,0,0,0)); ImageDraw.Draw(im).text((0,8),'Scatterloom version '+version,font=font(21),fill='#9bbdb3'); im.save(skins/'info-version.png')
    items.append(component('Scatterloom version','info-version.png','310 540 480 48'))
    info['componentDefinition']['componentsData']=items
    info['fnKeyIndex']=4
    return json.dumps(data,indent=2)+'\n'


def update_qlinks(path):
    obj=json.loads(path.read_text()); maps=obj['Screen Mode Q-Links']['map']
    for entry in maps:
        if entry.get('Tab') == 1:
            entry['Q-Links']['Q-Link 4'] = -1
            entry['Q-Links']['Q-Link 11'] = 5
            entry['Q-Links']['Q-Link 12'] = 10
        if entry.get('Tab') == 2: entry['Q-Links']['Q-Link 4'] = 5
        if entry.get('Tab') == 3:
            for key, value in entry['Q-Links'].items():
                if value in (9, 10, 25): entry['Q-Links'][key] = -1
            entry['Q-Links']['Q-Link 4'] = 10
        if entry.get('Tab') == 4:
            entry['Bank Direction'] = 'RowTopDown'
            entry['Q-Links'] = {'Q-Link %d' % i: -1 for i in range(1,17)}
            for index, parameter in {13:0,14:4,15:9,16:161,9:1,10:26,11:25,12:14}.items():
                entry['Q-Links']['Q-Link %d' % index] = parameter
    path.write_text(json.dumps(obj, indent=2)+'\n')

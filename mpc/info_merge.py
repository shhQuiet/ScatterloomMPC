"""Build the combined Info screen from the generated MPC skin (no DSP changes)."""
import copy
import json
import subprocess
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont


def combine_info(raw, skins, version):
    data = json.loads(raw)
    pd = data['pageData']
    tabs = pd['tabs']
    license_tab = next(t for t in tabs if t['tabName'] == 'LICENSE')
    info = next(t for t in tabs if t['tabName'] == 'INFO')
    definitions = pd['componentDefinitions']['localComponentDefinitions']
    info_components = info['componentDefinition']['componentsData']
    demo = next(c for c in info_components if c['componentData']['name'] == 'Demo unregistered overlay')
    license_components = [copy.deepcopy(c) for c in license_tab['componentDefinition']['componentsData'] if c['componentData']['name'] != 'Demo unregistered overlay']
    for item in license_components:
        bounds = item['bounds']
        bounds['version'] = 2
        handles = bounds.setdefault('additionalInvalidatingHandles', [])
        # Move the registered certificate and its controls together, below the
        # tabs while leaving the lower-left Scatterloom logo unobstructed.
        if 'IndexedEnabling/3/6/Parameter 163' in handles:
            x, y, width, height = map(int, bounds['bounds'].split())
            bounds['bounds'] = f'{x} {y+45} {width} {height}'
        handles.append('IndexedEnabling/1/2/Local/2/infoLicense')

    font_path = '/System/Library/Fonts/Helvetica.ttc'
    def font(size):
        try: return ImageFont.truetype(font_path, size)
        except OSError: return ImageFont.load_default()
    def tab_image(name, title, active):
        im = Image.new('RGBA', (640, 84), (0, 0, 0, 0)); draw = ImageDraw.Draw(im)
        draw.rectangle((0, 0, 639, 83), fill='#29413d' if active else '#192624')
        draw.line((0, 81, 639, 81), fill='#78c1ae' if active else '#465d57', width=3)
        draw.text((320, 41), title, anchor='mm', font=font(22), fill='#f0e6d6' if active else '#aab8b0')
        im.save(skins / name)
    for name, text in [('info-help','HELP'),('info-license','LICENSE')]:
        tab_image(name+'-on.png', text, True); tab_image(name+'-off.png', text, False)
    for name, symbol in [('info-prev.png', '‹'), ('info-next.png', '›')]:
        im=Image.new('RGBA',(72,260),(0,0,0,0)); d=ImageDraw.Draw(im)
        d.rounded_rectangle((2,2,69,257),radius=8,fill='#253d38',outline='#729a8c',width=2)
        d.text((36,130),symbol,anchor='mm',font=font(58),fill='#f0e6d6')
        im.save(skins/name)
    im=Image.new('RGBA',(480,48),(0,0,0,0)); d=ImageDraw.Draw(im)
    d.text((0,8),'Scatterloom version '+version,font=font(21),fill='#9bbdb3')
    im.save(skins/'info-version.png')
    # The product page leads to the license-key download. Generate a crisp QR
    # with the macOS Core Image encoder, without putting credentials in assets.
    swift = r"""import AppKit
import CoreImage
let url = "https://elsewave.pages.dev/mpc/scatterloom"
let filter = CIFilter(name: "CIQRCodeGenerator")!
filter.setValue(url.data(using: .utf8)!, forKey: "inputMessage")
filter.setValue("M", forKey: "inputCorrectionLevel")
let qr = filter.outputImage!.transformed(by: CGAffineTransform(scaleX: 6, y: 6))
let context = CIContext(options: nil)
let cg = context.createCGImage(qr, from: qr.extent)!
let rep = NSBitmapImageRep(cgImage: cg)
try! rep.representation(using: .png, properties: [:])!.write(to: URL(fileURLWithPath: CommandLine.arguments[1]))
"""
    qr_path = skins / 'info-product-qr-raw.png'
    subprocess.run(['/usr/bin/swift', '-', str(qr_path)], input=swift, text=True, check=True)
    qr = Image.open(qr_path).convert('RGBA')
    qr_image = Image.new('RGBA', (qr.width+48, qr.height+48), 'white')
    qr_image.alpha_composite(qr, (24,24)); qr_image.save(skins/'info-product-qr.png')
    qr_path.unlink()
    pages = [
      ('CAPTURE', ['Scatterloom keeps up to nine captured grains in a pool.', 'It listens to the input and captures audio when it crosses', 'the sensitivity threshold. Turn Capture off to keep the', 'current pool while you continue playing.']),
      ('PATTERN', ['Steps and Pulses create a Euclidean rhythm that decides', 'when grains play. For example, 7 pulses across 16 steps', 'spreads seven triggers through the pattern.']),
      ('GRAIN SELECTION', ['The Markov matrix controls which grain follows another.', 'Choose a pattern or tap a cell and adjust its probability.', 'The available grains depend on what is in the pool.'])]
    im=Image.new('RGBA',(1080,390),(0,0,0,0)); d=ImageDraw.Draw(im)
    d.text((0,0),'LICENSE',font=font(36),fill='#efb05c')
    d.text((0,60),'Scatterloom requires a license for full functionality.',font=font(27),fill='#f0e6d6')
    d.text((0,116),'Scan the QR or visit:',font=font(27),fill='#f0e6d6')
    d.text((0,155),'elsewave.pages.dev/mpc/scatterloom',font=font(25),fill='#9bd4c3')
    d.text((0,205),'to get your license key.',font=font(27),fill='#f0e6d6')
    d.text((0,255),'Once you have a key, select the',font=font(27),fill='#f0e6d6')
    d.text((0,294),'License tab',font=font(27),fill='#9bd4c3')
    d.line((0,327,140,327),fill='#9bd4c3',width=2)
    d.text((150,294),'above to pair your MPC.',font=font(27),fill='#f0e6d6')
    d.text((0,360),'PAGE 1 / 4',font=font(20),fill='#9bbdb3')
    im.save(skins/'info-help-intro.png')
    for idx,(title,lines) in enumerate(pages):
        for licensed in (False,True):
            im=Image.new('RGBA',(1080,390),(0,0,0,0)); d=ImageDraw.Draw(im)
            d.text((0,0),title,font=font(36),fill='#efb05c')
            for row,line in enumerate(lines): d.text((0,70+row*40),line,font=font(27),fill='#f0e6d6')
            d.text((0,340),'PAGE %d / %d' % (idx+1 if licensed else idx+2,3 if licensed else 4),font=font(20),fill='#9bbdb3')
            im.save(skins / ('info-help-%d-%s.png' % (idx, 'licensed' if licensed else 'unlicensed')))
    def bounds(rect, conditions=()):
        return {'version':2,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':rect,'additionalInvalidatingHandles':list(conditions)}
    def component(name,image_name,rect,conditions=(),type_name='Image'):
        component_data={'version':1,'name':name,'type':type_name,'data':{'version':2,'imageType':'Regular','colour':'0','image':image_name} if type_name=='Image' else {'version':1,'handleName':'Data'}}
        component_bounds = bounds(rect, conditions)
        if type_name == 'Image': component_bounds['showWhenDataModelInvalid'] = 'Show'
        return {'version':2,'componentData':component_data,'handle remapping':{'version':1,'map':[]},'bounds':component_bounds}
    def choice(handle,index): return 'IndexedEnabling/%d/2/Local/2/%s' % (index,handle)
    def action_def(name,image_name,handles,width,height):
        definitions.append({'key':name,'value':{'version':2,'actions':[{'version':1,'onAction':'Mouse Down','handler':'Toggle Switch','handleName':'Local/2/'+h,'additionalData':''} for h in handles], 'backgroundData':{'version':1,'focussed':{'version':1,'colour':'0','image':''},'unfocussed':{'version':1,'colour':'0','image':''}},'ignoreMousePresses':False,'disableCoarseDataWheel':False,'componentsData':[component(name+' art',image_name,'0 0 %d %d'%(width,height))]}})
    transparent = Image.new('RGBA',(145,40),(0,0,0,0)); transparent.save(skins/'info-link-touch.png')
    action_def('InfoSelectLicenseLink','info-link-touch.png',['infoLicense'],145,40)
    action_def('InfoSelectHelp','info-help-off.png',['infoLicense'],640,84)
    action_def('InfoSelectLicense','info-license-off.png',['infoLicense'],640,84)
    action_def('InfoPagePrevHigh','info-prev.png',['infoPageHigh'],72,260)
    action_def('InfoPagePrevOne','info-prev.png',['infoPageLow'],72,260)
    action_def('InfoPagePrevTwo','info-prev.png',['infoPageLow','infoPageHigh'],72,260)
    action_def('InfoPageNextOne','info-next.png',['infoPageLow'],72,260)
    action_def('InfoPageNextTwo','info-next.png',['infoPageLow','infoPageHigh'],72,260)
    items = []
    # Active choices are inert; selecting the other choice toggles the local view.
    for mode,name,x in [(0,'help',640),(1,'license',0)]:
        items.append(component('Info '+name+' selected','info-'+name+'-on.png',f'{x} 0 640 84',[choice('infoLicense',mode)]))
        items.append(component('Select '+name,'',f'{x} 0 640 84',[choice('infoLicense',1-mode)],'InfoSelect'+name.title()))
    # Local page indices start at zero for both states; registration determines
    # which artwork and navigation are offered for each index.
    for status in range(6):
        licensed = status == 3
        status_cond = 'IndexedEnabling/%d/6/Parameter 163' % status
        states = [(0,0),(0,1),(1,0),(1,1)]
        for idx,(high,low) in enumerate(states):
            cond=[choice('infoLicense',0),choice('infoPageHigh',high),choice('infoPageLow',low),status_cond]
            intro = not licensed and idx == 0
            image_name = 'info-help-intro.png' if intro else 'info-help-%d-%s.png' % (min(idx,2) if licensed else idx-1, 'licensed' if licensed else 'unlicensed')
            items.append(component('Help page %d status %d'%(idx+1,status),image_name,'100 110 1080 390',cond))
            if intro:
                items.append(component('Product QR','info-product-qr.png','885 160 220 220',cond))
                # The underlined words toggle the same local view as the License tab.
                items.append(component('Open License tab','','100 404 145 40',cond,'InfoSelectLicenseLink'))
            if idx: items.append(component('Previous help page','', '10 170 72 260',cond,'InfoPagePrevHigh' if licensed and idx==3 else ('InfoPagePrevTwo' if idx==2 else 'InfoPagePrevOne')))
            if idx < (2 if licensed else 3): items.append(component('Next help page','', '1198 170 72 260',cond,'InfoPageNextTwo' if idx==1 else 'InfoPageNextOne'))
    items.append(component('Scatterloom version', 'info-version.png', '310 540 480 48', [choice('infoLicense',0)]))
    info['componentDefinition']['componentsData'] = license_components + items + [demo]
    tabs.remove(license_tab)
    info['fnKeyIndex'] = 4
    return json.dumps(data, indent=2)+'\n'


def remove_license_qlinks(path):
    obj=json.loads(path.read_text()); maps=obj['Screen Mode Q-Links']['map']
    maps[:] = [m for m in maps if m.get('Tab') != 5]
    for entry in maps:
        if entry.get('Tab') == 1: entry['Q-Links']['Q-Link 4'] = 10
        if entry.get('Tab') == 6: entry['Tab'] = 5
        if entry.get('Tab') == 3:
            for key, value in entry['Q-Links'].items():
                if value in (9, 10, 25): entry['Q-Links'][key] = -1
        if entry.get('Tab') == 4:
            entry['Bank Direction'] = 'RowTopDown'
            entry['Q-Links'] = {'Q-Link %d' % i: -1 for i in range(1,17)}
            for index, parameter in {13:0,14:4,15:9,16:161,9:1,10:26,11:25,12:14,8:10}.items():
                entry['Q-Links']['Q-Link %d' % index] = parameter
    path.write_text(json.dumps(obj, indent=2)+'\n')

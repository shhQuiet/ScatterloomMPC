#!/usr/bin/env python3
"""Regenerate SDK skin, then insert the static Capture artwork without reserializing overlay keys."""
import json
import math
import os
from pathlib import Path
import shutil
import subprocess
import sys

project = Path(__file__).resolve().parent
sdk = Path(os.environ.get('MPC_SDK', ''))
if not (sdk / 'tools/gen_ui.py').is_file():
    sys.exit('Set MPC_SDK to the official MPC Plugin SDK directory.')
params = project / 'build/params.json'
if not params.is_file():
    sys.exit('Build the native plugin first to generate build/params.json.')
skins = project / 'skins'
skins.mkdir(exist_ok=True)
subprocess.run([sys.executable, str(sdk / 'tools/gen_ui.py'), '--params', str(params), '--ui', str(project / 'ui.json'), '--out', str(skins), '--kit-cache', str(project / 'build')], check=True)
# Bank the Main page by screen row, keeping its physical Q-Link positions.
qlink_path = skins / 'Q-Links.json'
qlinks = json.loads(qlink_path.read_text())
qlinks['Screen Mode Q-Links']['map'][0]['Bank Direction'] = 'RowTopDown'
qlinks['Screen Mode Q-Links']['map'][1]['Bank Direction'] = 'RowTopDown'
qlink_path.write_text(json.dumps(qlinks, indent=2) + '\n')
shutil.copy2(project / 'assets/capture-weave.png', skins / 'capture-weave.png')
path = skins / 'TUI.json'
raw = path.read_text()
# Match the focus rectangles to the four horizontal banks on Main.
main_start = raw.index('"tabName": "MAIN"')
main_end = raw.index('"qlinkBoundsData"', main_start)
bounds_end = raw.index(']', main_end) + 1
raw = raw[:main_end] + '"qlinkBoundsData": ["0 30 1280 130", "0 180 1280 130", "0 330 1280 130", "0 480 1280 130"]' + raw[bounds_end:]
grains_focus = raw.index('"tabName": "GRAINS"')
grains_bounds = raw.index('"qlinkBoundsData"', grains_focus)
grains_bounds_end = raw.index(']', grains_bounds) + 1
raw = raw[:grains_bounds] + '"qlinkBoundsData": ["0 30 1280 130", "0 180 1280 130", "0 330 1280 130", "0 480 1280 130"]' + raw[grains_bounds_end:]

# The same artwork is the background on every plugin page.
for page_name in ('MAIN', 'MARKOV', 'GRAINS', 'MIX', 'INFO'):
    anchor = '"tabName": "%s"' % page_name
    if raw.count(anchor) != 1: sys.exit('Page missing or ambiguous: %s' % page_name)
    start = raw.index(anchor)
    end = raw.index('"ignoreMousePresses"', start)
    section = raw[start:end]
    if section.count('"image": ""') != 2:
        sys.exit('Background fields missing or ambiguous: %s' % page_name)
    section = section.replace('"image": ""', '"image": "capture-weave.png"')
    raw = raw[:start] + section + raw[end:]
# Place Play beside Capture in the same row.
play_start = raw.index('"name": "Play"')
play_end = raw.index('"handle remapping"', play_start)
part = raw[play_start:play_end]
part = part.replace('"type": "toggle"', '"type": "Button"')
part = part.replace('"version": 1,\n                                    "handleName": "Data"',
 '"version": 2,\n                                    "onImage": "play-control-on.png",\n                                    "offImage": "play-control-off.png",\n                                    "buttonId": 1,\n                                    "numButtonsInGroup": 1,\n                                    "handleName": "Data",\n                                    "gestureBehaviour": "Instant"')
if '"onImage": "play-control-on.png"' not in part: sys.exit('Could not configure Play button.')
raw = raw[:play_start] + part + raw[play_end:]
play_bounds = raw.index('"bounds": "343 196 278 107"', play_start)
raw = raw[:play_bounds] + raw[play_bounds:].replace('"bounds": "343 196 278 107"', '"bounds": "1170 397 91 107"', 1)
subprocess.run(['swift', str(project / 'tools' / 'draw-play.swift'), str(skins)], check=True)
# Capture is a labeled latching button, not a switch or a momentary control.
capture_name = '"name": "Capture"'
if raw.count(capture_name) != 1:
    sys.exit('Capture button missing or ambiguous.')
begin = raw.index(capture_name)
end = raw.index('"handle remapping"', begin)
component = raw[begin:end]
if component.count('"type": "toggle"') != 1 or component.count('"handleName": "Data"') != 1:
    sys.exit('Capture button structure changed.')
component = component.replace('"type": "toggle"', '"type": "Button"')
component = component.replace('"version": 1,\n                                    "handleName": "Data"',
    '"version": 2,\n                                    "onImage": "capture-button-on.png",\n                                    "offImage": "capture-button-off.png",\n                                    "buttonId": 1,\n                                    "numButtonsInGroup": 1,\n                                    "handleName": "Data",\n                                    "gestureBehaviour": "Instant"')
if '"onImage": "capture-button-on.png"' not in component:
    sys.exit('Could not configure Capture button images.')
raw = raw[:begin] + component + raw[end:]
# Share the existing Capture column between Capture and Play.
capture_bounds = raw.index('"bounds": "983 346 278 107"', begin)
raw = raw[:capture_bounds] + raw[capture_bounds:].replace('"bounds": "983 346 278 107"', '"bounds": "983 397 175 107"', 1)
# Confirmation's Yes action clears first, then closes the local panel.
yes_definition = {'key': 'ClearConfirmYes', 'value': {'version': 2,
 'actions': [
  {'version': 1, 'onAction': 'Mouse Down', 'handler': 'Toggle Switch', 'handleName': 'ResetOnGestureEnd/Parameter 12', 'additionalData': ''},
  {'version': 1, 'onAction': 'Mouse Down', 'handler': 'Toggle Switch', 'handleName': 'Local/2/clearConfirm', 'additionalData': ''}],
 'backgroundData': {'version': 1, 'focussed': {'version': 1, 'colour': '0', 'image': ''},
                    'unfocussed': {'version': 1, 'colour': '0', 'image': ''}},
 'ignoreMousePresses': False, 'disableCoarseDataWheel': False,
 'componentsData': [{'version': 2,
  'componentData': {'version': 1, 'name': 'Yes Clear', 'type': 'Image',
    'data': {'version': 2, 'imageType': 'Regular', 'colour': '0', 'image': 'clear-confirm-yes.png'}},
  'handle remapping': {'version': 1, 'map': []},
  'bounds': {'version': 1, 'acceptsHWFocus': 'No', 'showWhenDataModelInvalid': 'Show',
   'whenVisible': 'Always', 'boundsType': 'Absolute', 'bounds': '0 0 175 60'}}]}}
# Grid cells select their position and expose the shared probability value to
# the hardware data wheel when the cell itself receives focus.
markov_cell_definition = {'key':'MarkovCellFocus','value':{'version':2,
 'actions':[{'version':1,'onAction':'Mouse Down','handler':'Toggle Switch','handleName':'Select','additionalData':''},
            {'version':1,'onAction':'Mouse Down','handler':'Q-Link','handleName':'Data','additionalData':''}],
 'backgroundData':{'version':1,'focussed':{'version':1,'colour':'0','image':''},'unfocussed':{'version':1,'colour':'0','image':''}},
 'ignoreMousePresses':False,'disableCoarseDataWheel':False,
 'componentsData':[{'version':2,'componentData':{'version':1,'name':'Cell probability','type':'Knob',
  'data':{'version':2,'knobType':'FilmStrip','filmStrip':'markov-transparent.png','numFrames':1,'invert':False,'handleName':'Data'}},
  'handle remapping':{'version':1,'map':[]},
  'bounds':{'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Hide','whenVisible':'Always',
            'boundsType':'Absolute','bounds':'0 0 1 1'}}]}}
defs_marker = '"localComponentDefinitions": ['
if raw.count(defs_marker) != 1: sys.exit('Local definitions missing or ambiguous.')

defs_pos = raw.index(defs_marker)+len(defs_marker)
raw = raw[:defs_pos] + '\n'+json.dumps(yes_definition)+','+json.dumps(markov_cell_definition)+',' + raw[defs_pos:]
# Add the probability grid: bars are driven by saved matrix parameters,
# transparent buttons select a cell, and a frame marks the current selection.
markov_start = raw.index('"tabName": "MARKOV"')
markov_end = raw.index('"qlinkBoundsData"', markov_start)
section = raw[markov_start:markov_end]
pos = section.index('"componentsData": [') + len('"componentsData": [')
for index in (354,355):
 section=section.replace('"value": "Parameter %d"'%index, '"value": "ResetOnGestureEnd/Parameter %d"'%index)
entries = [{'version':2,'componentData':{'version':1,'name':'Matrix labels','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'markov-labels.png'}},
 'handle remapping':{'version':1,'map':[]},'bounds':{'version':1,'acceptsHWFocus':'No',
 'showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':'324 0 610 580'}}]
entries.append({'version':2,'componentData':{'version':1,'name':'Markov explanation','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'markov-explanation.png'}},
 'handle remapping':{'version':1,'map':[]},'bounds':{'version':1,'acceptsHWFocus':'No',
 'showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':'985 170 270 280'}})
entries.append({'version':2,'componentData':{'version':1,'name':'Recent Grains','type':'knobUni',
 'data':{'version':1,'handleName':'Data'}},
 'handle remapping':{'version':1,'map':[{'key':'Data','value':'Parameter 5'}]},
 'bounds':{'version':1,'acceptsHWFocus':'Yes','showWhenDataModelInvalid':'Hide',
 'whenVisible':'Always','boundsType':'Absolute','bounds':'983 480 278 107'}})
from PIL import Image, ImageDraw, ImageFont
explanation = Image.new('RGBA', (270, 280), (0,0,0,0))
draw = ImageDraw.Draw(explanation)
font = ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc', 17)
draw.multiline_text((0,0), 'Patterns use a probability\nmatrix called a Markov chain.', font=font, fill='#dfd6c1', spacing=3)
existing = Image.open(project/'assets'/'markov-explanation.png').convert('RGBA')
explanation.alpha_composite(existing, (0,76))
explanation.save(skins/'markov-explanation.png')
front_entries = []
for row in range(9):
 for col in range(9):
  cell = row*9+col
  box = '%d %d 52 52' % (392+col*55, 63+row*55)
  def bounds(): return {'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Hide','whenVisible':'Always','boundsType':'Absolute','bounds':box}
  entries.append({'version':2,'componentData':{'version':1,'name':'Probability %d %d'%(row+1,col+1),'type':'Image',
   'data':{'version':2,'imageType':'FilmStrip','colour':'0','image':'markov-bar-strip.png','numFrames':101,'handleName':'Data'}},
   'handle remapping':{'version':1,'map':[{'key':'Data','value':'Parameter %d'%(369+cell)}]},'bounds':bounds()})
  playing=bounds(); playing['version']=2; playing['additionalInvalidatingHandles']=['IndexedEnabling/%d/82/Parameter 357'%(1+cell)]
  front_entries.append({'version':2,'componentData':{'version':1,'name':'Next transition %d %d'%(row+1,col+1),'type':'Image',
   'data':{'version':2,'imageType':'Regular','colour':'0','image':'markov-playing.png'}},
   'handle remapping':{'version':1,'map':[]},'bounds':playing})
  selected=bounds(); selected['version']=2; selected['additionalInvalidatingHandles']=['IndexedEnabling/%d/9/Parameter 351'%row,'IndexedEnabling/%d/9/Parameter 352'%col]
  front_entries.append({'version':2,'componentData':{'version':1,'name':'Selected %d %d'%(row+1,col+1),'type':'Image',
   'data':{'version':2,'imageType':'Regular','colour':'0','image':'markov-selected.png'}},
   'handle remapping':{'version':1,'map':[]},'bounds':selected})
  cell_bounds=bounds(); cell_bounds['acceptsHWFocus']='Yes'
  front_entries.append({'version':2,'componentData':{'version':1,'name':'Select %d %d'%(row+1,col+1),'type':'MarkovCellFocus',
   'data':{'version':1,'handleName':'Data'}},
   'handle remapping':{'version':1,'map':[{'key':'Select','value':'ResetOnGestureEnd/Parameter %d'%(270+cell)},
                                         {'key':'Data','value':'Parameter 353'}]},'bounds':cell_bounds})
# Shade unavailable cells for either a small pool or a lower Recent Grains setting.
for axis in ('row','column'):
 for index in range(9):
  geometry = ('368 %d 516 52' % (63+index*55) if axis=='row' else '%d 35 52 520' % (392+index*55))
  for parameter, maximum, steps in ((27,index,10),(5,index-1,9)):
   if maximum<0: continue
   entries.append({'version':2,'componentData':{'version':1,'name':'Dim %s %d by %d'%(axis,index+1,parameter),'type':'Image',
    'data':{'version':2,'imageType':'Regular','colour':'0','image':'markov-dim-%s.png'%axis}},
    'handle remapping':{'version':1,'map':[]},
    'bounds':{'version':2,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show','whenVisible':'Always',
      'boundsType':'Absolute','bounds':geometry,
      'additionalInvalidatingHandles':['RangedEnabling/0/%d/%d/Parameter %d'%(maximum,steps,parameter)]}})
entries.extend(front_entries)
section = section[:pos]+''.join('\n'+json.dumps(e)+',' for e in entries)+section[pos:]
raw = raw[:markov_start]+section+raw[markov_end:]
for name in ('markov-bar-strip.png','markov-selected.png','markov-transparent.png','markov-labels.png','markov-playing.png','markov-dim-row.png','markov-dim-column.png'):
 shutil.copy2(project/'assets'/name,skins/name)

# Main page layout and rhythm display.
main_anchor = '"tabName": "MAIN"'
if raw.count(main_anchor) != 1: sys.exit('Main tab missing or ambiguous.')
start = raw.index(main_anchor)
end = raw.index('"qlinkBoundsData"', start)
section = raw[start:end]
# Recent Grains and Mix use the same compact control, with Mix on the right.
recent_start=section.index('"name": "Recent Grains"')
recent_end=section.index('"handle remapping"',recent_start)
part=section[recent_start:recent_end]
assert part.count('"type": "knobUni"')==1
section=section[:recent_start]+part.replace('"type": "knobUni"','"type": "compactMainMix"')+section[recent_end:]
recent_bounds=section.index('"bounds": "983 196 278 107"',recent_start)
section=section[:recent_bounds]+section[recent_bounds:].replace('"bounds": "983 196 278 107"','"bounds": "750 196 275 107"',1)
marker = '"componentsData": ['
pos = section.index(marker) + len(marker)
main_clear = {'version': 2,
 'componentData': {'version': 1, 'name': 'Clear Pool', 'type': 'Button',
  'data': {'version': 2, 'onImage': 'clear-pool-on.png', 'offImage': 'clear-pool-off.png',
           'buttonId': 1, 'numButtonsInGroup': 1, 'handleName': 'Data', 'gestureBehaviour': 'Instant'}},
 'handle remapping': {'version': 1, 'map': [{'key': 'Data', 'value': 'Local/2/clearConfirm'}]},
 'bounds': {'version': 1, 'acceptsHWFocus': 'No', 'showWhenDataModelInvalid': 'Show',
  'whenVisible': 'Always', 'boundsType': 'Absolute', 'bounds': '983 535 175 70'}}
# One of these two buttons is visible according to the saved confirmation setting.
main_clear['bounds']['version'] = 2
main_clear['bounds']['additionalInvalidatingHandles'] = ['IndexedEnabling/1/2/Parameter 161']
immediate_clear = json.loads(json.dumps(main_clear))
immediate_clear['componentData']['name'] = 'Clear Pool Immediately'
immediate_clear['handle remapping']['map'][0]['value'] = 'ResetOnGestureEnd/Parameter 12'
immediate_clear['bounds']['additionalInvalidatingHandles'] = ['IndexedEnabling/0/2/Parameter 161']
entries = [main_clear, immediate_clear]
# A compact Mix control sits between the rhythm circle and Recent Grains.
entries.append({'version':2, 'componentData':{'version':1,'name':'Mix','type':'compactMainMix',
 'data':{'version':1,'handleName':'Data'}},
 'handle remapping':{'version':1,'map':[{'key':'Data','value':'Parameter 10'}]},
 'bounds':{'version':1,'acceptsHWFocus':'Yes','showWhenDataModelInvalid':'Hide',
 'whenVisible':'Always','boundsType':'Absolute','bounds':'1026 196 245 107'}})
remove_newest = {'version':2,'componentData':{'version':1,'name':'Remove newest grain','type':'Button',
 'data':{'version':2,'onImage':'remove-newest-on.png','offImage':'remove-newest-off.png',
 'buttonId':1,'numButtonsInGroup':1,'handleName':'Data','gestureBehaviour':'Instant'}},
 'handle remapping':{'version':1,'map':[{'key':'Data','value':'ResetOnGestureEnd/Parameter 187'}]},
 'bounds':{'version':1,'acceptsHWFocus':'Yes','showWhenDataModelInvalid':'Hide',
 'whenVisible':'Always','boundsType':'Absolute','bounds':'1170 535 91 70'}}
entries.append(remove_newest)
for state, conditions in [('off', []), ('flash', ['IndexedEnabling/1/2/Parameter 188'])]:
    entries.append({'version':2,'componentData':{'version':1,'name':'Input detection '+state,'type':'Image',
     'data':{'version':2,'imageType':'Regular','colour':'0','image':'capture-bar-'+state+'.png'}},
     'handle remapping':{'version':1,'map':[]},'bounds':{'version':2,'acceptsHWFocus':'No',
     'showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute',
     'bounds':'983 507 278 8','additionalInvalidatingHandles':conditions}})
for name in ('capture-bar-off.png', 'capture-bar-flash.png'):
 shutil.copy2(project/'assets'/name, skins/name)
# Nine touch pads show occupied grains and trigger their audition.
for pad in range(9):
    x = 778 + (pad % 3) * 65
    y = 545 - (pad // 3) * 65
    box = '%d %d 60 60' % (x,y)
    occupied = ('IndexedEnabling/9/10/Parameter 27' if pad == 8 else
                'RangedEnabling/%d/9/10/Parameter 27' % (pad+1))
    glow_states = [('glow-%d' % level, ['IndexedEnabling/%d/46/Parameter 368' % (1+pad*5+(level-1))]) for level in range(1,6)]
    for state, conditions in [('off', []), ('on', [occupied])] + glow_states + [('flash', ['IndexedEnabling/%d/10/Parameter 186' % (pad+1)])]:
        name='pool-pad-%d-%s.png' % (pad+1,state)
        shutil.copy2(project/'assets'/name, skins/name)
        entries.append({'version':2,'componentData':{'version':1,'name':'Grain pad %d %s'%(pad+1,state),
         'type':'Image','data':{'version':2,'imageType':'Regular','colour':'0','image':name}},
         'handle remapping':{'version':1,'map':[]},
         'bounds':{'version':2,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show',
                   'whenVisible':'Always','boundsType':'Absolute','bounds':box,
                   'additionalInvalidatingHandles':conditions}})
    active_count = ('IndexedEnabling/8/9/Parameter 5' if pad == 8 else
                    'RangedEnabling/%d/8/9/Parameter 5' % pad)
    entries.append({'version':2,'componentData':{'version':1,'name':'Active grain outline %d'%(pad+1),
      'type':'Image','data':{'version':2,'imageType':'Regular','colour':'0','image':'pool-pad-active-outline.png'}},
      'handle remapping':{'version':1,'map':[]},'bounds':{'version':2,'acceptsHWFocus':'No',
       'showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':box,
       'additionalInvalidatingHandles':[occupied,active_count]}})
    entries.append({'version':2,'componentData':{'version':1,'name':'Play grain %d'%(pad+1),'type':'Button',
      'data':{'version':2,'onImage':'pool-pad-touch-on.png','offImage':'pool-pad-touch.png',
              'buttonId':1,'numButtonsInGroup':1,'handleName':'Data','gestureBehaviour':'Instant'}},
      'handle remapping':{'version':1,'map':[{'key':'Data','value':'ResetOnGestureEnd/Parameter %d'%(358+pad)}]},
      'bounds':{'version':2,'acceptsHWFocus':'Yes','showWhenDataModelInvalid':'Hide','whenVisible':'Always',
                'boundsType':'Absolute','bounds':box,'additionalInvalidatingHandles':[occupied]}})
for name in ('pool-pad-touch.png','pool-pad-touch-on.png','pool-pad-active-outline.png'):
 shutil.copy2(project/'assets'/name, skins/name)

# Subtle instrument face behind the existing rhythm graphics.
shutil.copy2(project/'assets'/'rhythm-instrument-face.png', skins/'rhythm-instrument-face.png')
entries.append({'version':2,'componentData':{'version':1,'name':'Rhythm instrument face','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'rhythm-instrument-face.png'}},
 'handle remapping':{'version':1,'map':[]},'bounds':{'version':1,'acceptsHWFocus':'No',
 'showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':'305 155 420 420'}})
for segment in range(64):
    angle = 2.0 * math.pi * segment / 64 - math.pi / 2.0
    x = round(515 + (75 * 175 / 130) * math.cos(angle) - 43.0)
    y = round(365 + (75 * 175 / 130) * math.sin(angle) - 43.0)
    entries.append({'version': 2,
      'componentData': {'version': 1, 'name': 'Rhythm sector %d' % segment, 'type': 'Image',
       'data': {'version': 2, 'imageType': 'FilmStrip', 'colour': '0', 'image': 'rhythm-large-sector-%02d.png' % segment,
                'numFrames': 24, 'handleName': 'Data'}},
      'handle remapping': {'version': 1, 'map': [{'key': 'Data', 'value': 'Parameter %d' % (93+segment)}]},
      'bounds': {'version': 1, 'acceptsHWFocus': 'No', 'showWhenDataModelInvalid': 'Hide',
                 'whenVisible': 'Always', 'boundsType': 'Absolute', 'bounds': '%d %d 86 86' % (x,y)}})
# Share identical pixel positions across all rhythm lengths.
def rhythm_position(count, step):
 angle=2.0*math.pi*step/count-math.pi/2.0
 return (round(515+175*math.cos(angle)-15), round(365+175*math.sin(angle)-15), round(step*64/count)%64)
shared_positions=sorted({rhythm_position(n,i) for n in range(1,33) for i in range(n)})
if len(shared_positions)!=325: sys.exit('Unexpected shared rhythm position count')
step_source=Image.open(project/'assets'/'rhythm-large-step-strip.png').convert('RGBA')
step_strip=Image.new('RGBA',(30,150))
for frame,src in ((1,0),(2,1),(3,0),(4,1)):
 step_strip.alpha_composite(step_source.crop((0,src*30,30,(src+1)*30)),(0,frame*30))
step_strip.save(skins/'rhythm-shared-steps.png')
for turn in range(64):
 source=Image.open(project/'assets'/('rhythm-trail-%02d.png'%turn)).convert('RGBA')
 strip=Image.new('RGBA',(70,350))
 for frame in (3,4): strip.alpha_composite(source.crop((0,70,70,140)),(0,frame*70))
 strip.save(skins/('rhythm-shared-trail-%02d.png'%turn))
for index,(x,y,turn) in enumerate(shared_positions):
 entries.append({'version':2,'componentData':{'version':1,'name':'Shared rhythm %d'%index,'type':'Image',
  'data':{'version':2,'imageType':'FilmStrip','colour':'0','image':'rhythm-shared-steps.png','numFrames':5,'handleName':'Data'}},
  'handle remapping':{'version':1,'map':[{'key':'Data','value':'Parameter %d'%(450+index)}]},
  'bounds':{'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Hide','whenVisible':'Always','boundsType':'Absolute','bounds':'%d %d 30 30'%(x,y)}})
# Styled pulse/step values, displayed as a fraction inside the ring.
for name, param, frames, y in [('Pulses in ring', 7, 33, 315), ('Steps in ring', 6, 32, 370)]:
 entries.append({'version':2,'componentData':{'version':1,'name':name,'type':'Image',
  'data':{'version':2,'imageType':'FilmStrip','colour':'0','image':'rhythm-fraction-%s.png'%('pulses' if param==7 else 'steps'),'numFrames':frames,'handleName':'Data'}},
  'handle remapping':{'version':1,'map':[{'key':'Data','value':'Parameter %d'%param}]},
  'bounds':{'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Hide','whenVisible':'Always','boundsType':'Absolute','bounds':'480 %d 70 45'%y}})
entries.append({'version':2,'componentData':{'version':1,'name':'Rhythm fraction divider','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'rhythm-fraction-divider.png'}},
 'handle remapping':{'version':1,'map':[]},'bounds':{'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':'488 363 54 3'}})
for name in ['rhythm-fraction-pulses.png','rhythm-fraction-steps.png','rhythm-fraction-divider.png'] + ['rhythm-trail-%02d.png'%i for i in range(64)]:
 shutil.copy2(project/'assets'/name, skins/name)
# Draw playhead overlays after all step lights, as in the original layout.
for index,(x,y,turn) in enumerate(shared_positions):
 entries.append({'version':2,'componentData':{'version':1,'name':'Shared playhead %d'%index,'type':'Image',
  'data':{'version':2,'imageType':'FilmStrip','colour':'0','image':'rhythm-shared-trail-%02d.png'%turn,'numFrames':5,'handleName':'Data'}},
  'handle remapping':{'version':1,'map':[{'key':'Data','value':'Parameter %d'%(450+index)}]},
  'bounds':{'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Hide','whenVisible':'Always','boundsType':'Absolute','bounds':'%d %d 70 70'%(x-20,y-20)}})
section = section[:pos] + ''.join('\n' + ' '*24 + json.dumps(e) + ',' for e in entries) + section[pos:]
# Append the confirmation panel after all other controls so it is on top.
confirm_visible = ['IndexedEnabling/1/2/Local/2/clearConfirm']
def confirm_bounds(bounds):
 return {'version': 2, 'acceptsHWFocus': 'No', 'showWhenDataModelInvalid': 'Show',
  'whenVisible': 'Always', 'boundsType': 'Absolute', 'bounds': bounds,
  'additionalInvalidatingHandles': confirm_visible}
panel = {'version': 2, 'componentData': {'version': 1, 'name': 'Clear confirmation', 'type': 'Image',
 'data': {'version': 2, 'imageType': 'Regular', 'colour': '0', 'image': 'clear-confirm-panel.png'}},
 'handle remapping': {'version': 1, 'map': []}, 'bounds': confirm_bounds('390 190 500 230')}
yes = {'version': 2, 'componentData': {'version': 1, 'name': 'Confirm clear', 'type': 'ClearConfirmYes',
 'data': {'version': 1, 'handleName': 'Data'}},
 'handle remapping': {'version': 1, 'map': [{'key': 'Data', 'value': 'Local/2/clearConfirm'}]},
 'bounds': confirm_bounds('445 327 175 60')}
cancel = {'version': 2, 'componentData': {'version': 1, 'name': 'Cancel clear', 'type': 'Button',
 'data': {'version': 2, 'onImage': 'clear-confirm-cancel-on.png', 'offImage': 'clear-confirm-cancel.png',
          'buttonId': 1, 'numButtonsInGroup': 1, 'handleName': 'Data', 'gestureBehaviour': 'Instant'}},
 'handle remapping': {'version': 1, 'map': [{'key': 'Data', 'value': 'Local/2/clearConfirm'}]},
 'bounds': confirm_bounds('660 327 175 60')}
last = section.rfind(']')
if last < 0: sys.exit('Main components end missing.')
section = section[:last].rstrip() + ',' + ''.join('\n'+' '*24+json.dumps(e)+',' for e in [panel,yes,cancel])[:-1] + '\n                    ' + section[last:]
raw = raw[:start] + section + raw[end:]
# Dim the Sensitivity control whenever Auto Sens is active. The plugin also
# rejects hardware edits in that state.
grains_start=raw.index('"tabName": "GRAINS"')
grains_end=raw.index('"qlinkBoundsData"', grains_start)
section=raw[grains_start:grains_end]
frame={'version':2,'componentData':{'version':1,'name':'Capture sensitivity group','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'capture-sensitivity-frame.png'}},
 'handle remapping':{'version':1,'map':[]},
 'bounds':{'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show',
  'whenVisible':'Always','boundsType':'Absolute','bounds':'6 20 338 310'}}
frame_pos=section.index('"componentsData": [')+len('"componentsData": [')
section=section[:frame_pos]+json.dumps(frame)+','+section[frame_pos:]
shutil.copy2(project/'assets'/'capture-sensitivity-frame.png',skins/'capture-sensitivity-frame.png')
grain_frame=json.loads(json.dumps(frame))
grain_frame['componentData']['name']='Grain settings group'
grain_frame['componentData']['data']['image']='grain-settings-frame.png'
grain_frame['bounds']['bounds']='350 20 300 310'
frame_pos=section.index('"componentsData": [')+len('"componentsData": [')
section=section[:frame_pos]+json.dumps(grain_frame)+','+section[frame_pos:]
shutil.copy2(project/'assets'/'grain-settings-frame.png',skins/'grain-settings-frame.png')
veil={'version':2,'componentData':{'version':1,'name':'Auto sensitivity lock','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'sensitivity-disabled.png'}},
 'handle remapping':{'version':1,'map':[]},
 'bounds':{'version':2,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show',
  'whenVisible':'Always','boundsType':'Absolute','bounds':'23 45 278 107',
  'additionalInvalidatingHandles':['IndexedEnabling/1/2/Parameter 1']}}
last=section.rfind(']')
section=section[:last].rstrip()+','+json.dumps(veil)+'\n'+section[last:]
raw=raw[:grains_start]+section+raw[grains_end:]
shutil.copy2(project/'assets'/'sensitivity-disabled.png', skins/'sensitivity-disabled.png')
gs=raw.index('"tabName": "GRAINS"'); ge=raw.index('"qlinkBoundsData"',gs)
section=raw[gs:ge]; key='"componentsData": '
start=section.index(key)+len(key)
controls, length=json.JSONDecoder().raw_decode(section[start:])
# Give the two controls beside the sensitivity frame more breathing room.
for control in controls:
 if control.get('componentData', {}).get('name') in ('Attack', 'Grain Start'):
  bounds = control['bounds']['bounds'].split()
  bounds[0] = str(int(bounds[0]) + 20)
  control['bounds']['bounds'] = ' '.join(bounds)
# Mirror the Main page's input-detection light beside Sensitivity.
for state, conditions in [('off', []), ('flash', ['IndexedEnabling/1/2/Parameter 188'])]:
 controls.append({'version':2,'componentData':{'version':1,'name':'Grains detection '+state,'type':'Image',
  'data':{'version':2,'imageType':'Regular','colour':'0','image':'pool-led-'+state+'.png'}},
  'handle remapping':{'version':1,'map':[]},'bounds':{'version':2,'acceptsHWFocus':'No',
  'showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute',
  'bounds':'307 86 24 24','additionalInvalidatingHandles':conditions}})
section=section[:start]+json.dumps(controls)+section[start+length:]
raw=raw[:gs]+section+raw[ge:]
# Nine horizontal pan sliders in one vertical list, plus latching modes.
stereo_start=raw.index('"tabName": "MIX"')
stereo_end=raw.index('"qlinkBoundsData"', stereo_start)
section=raw[stereo_start:stereo_end]
components_start=section.index('"componentsData": [')+len('"componentsData": [')
components_end=section.rfind(']')
entries=[]
def stereo_entry(name, kind, data, parameter, bounds, focus='No'):
 return {'version':2, 'componentData':{'version':1,'name':name,'type':kind,'data':data},
  'handle remapping':{'version':1,'map':[{'key':'Data','value':'Parameter %d'%parameter}]},
  'bounds':{'version':1,'acceptsHWFocus':focus,'showWhenDataModelInvalid':'Hide',
    'whenVisible':'Always','boundsType':'Absolute','bounds':bounds}}
def stereo_label(name, kind, parameter, bounds):
 return stereo_entry(name,'Label',{'version':1,'textStyle':{'version':1,
  'font':{'version':1,'name':'Roboto','style':'Regular','height':19.0},
  'colour':'ffdfcdb1','justification':'left verticallyCentred','case':'Original'},
  'type':kind,'handleName':'Data'},parameter,bounds)
def when_pool_count(entry, minimum, maximum):
 entry['bounds']['version']=2
 entry['bounds']['additionalInvalidatingHandles']=['RangedEnabling/%d/%d/10/Parameter 27'%(minimum,maximum)]
 return entry
for i in range(9):
 y=15+i*55; param=15+i
 active='RangedEnabling/%d/9/10/Parameter 27'%(i+1)
 entries.append(when_pool_count(stereo_label('Pan label %d'%i,'Name',param,'42 %d 195 45'%y),i+1,9))
 muted=stereo_label('Empty grain %d'%i,'Name',param,'42 %d 195 45'%y)
 muted['componentData']['data']['textStyle']['colour']='ff686868'
 entries.append(when_pool_count(muted,0,i))
 # Read-only image under precise tap zones; these disappear when a mode is active.
 entries.append(when_pool_count(stereo_entry('Pan display %d'%i,'Image',{'version':2,'imageType':'FilmStrip',
  'colour':'0','image':'stereo-pan-strip.png','numFrames':127,'handleName':'Data'},
  param,'245 %d 650 45'%y),i+1,9))
 empty_display=stereo_entry('Empty pan %d'%i,'Image',{'version':2,'imageType':'Regular',
  'colour':'0','image':'stereo-disabled.png'},param,'245 %d 650 45'%y)
 empty_display['bounds']['showWhenDataModelInvalid']='Show'
 entries.append(when_pool_count(empty_display,0,i))
 # A transparent native slider retains the existing film-strip artwork
 # while replacing 33 separate touch zones with one control.
 touch=stereo_entry('Pan %d touch'%i,'Slider',{'version':2,'sliderType':'ColourBar',
  'direction':'Horizontal','backgroundColour':'00000000','outlineColour':'00000000',
  'valueColour':'00000000','isBipolar':True,'handleName':'Data'},
  param,'245 %d 650 45'%y,'Yes')
 touch['bounds']['version']=2
 touch['bounds']['additionalInvalidatingHandles']=[active]+['IndexedEnabling/0/2/Parameter %d'%j for j in range(157,161)]
 entries.append(touch)
 entries.append(when_pool_count(stereo_label('Pan value %d'%i,'Value',param,'905 %d 95 45'%y),i+1,9))
for i,(slug,title) in enumerate([('center','Center'),('left-right','Left to Right'),
                                ('right-left','Right to Left'),('spread','Spread')]):
 entries.append(stereo_entry(title,'Button',{'version':2,'onImage':'stereo-%s-on.png'%slug,
  'offImage':'stereo-%s-off.png'%slug,'buttonId':1,'numButtonsInGroup':1,
  'handleName':'Data','gestureBehaviour':'Instant'},157+i,'1065 %d 180 56'%(15+i*110),'Yes'))
entries.append(stereo_entry('Mix','knobUni',{'version':1,'handleName':'Data'},10,'1040 430 230 107','Yes'))
section=section[:components_start]+'\n'+',\n'.join(json.dumps(e) for e in entries)+'\n'+section[components_end:]
raw=raw[:stereo_start]+section+raw[stereo_end:]
shutil.copy2(project/'assets'/'stereo-touch.png', skins/'stereo-touch.png')
shutil.copy2(project/'assets'/'stereo-disabled.png', skins/'stereo-disabled.png')
subprocess.run(['sips','-z','5715','650',str(skins/'fader_h_bi.png'),'--out',str(skins/'stereo-pan-strip.png')],check=True,stdout=subprocess.DEVNULL)
# Move the loop controls and a larger Mix knob to Settings.
defs_start=raw.index('"localComponentDefinitions": [')+len('"localComponentDefinitions": ')
defs, defs_len=json.JSONDecoder().raw_decode(raw[defs_start:])
large=next(json.loads(json.dumps(d)) for d in defs if d.get('key')=='knobUni')
large['key']='largeMixKnob'
for component in large['value']['componentsData']:
 name=component['componentData']['name']
 if name=='focus': component['bounds']['bounds']='0 0 300 145'
 elif name=='knob': component['bounds']['bounds']='8 8 125 125'
 elif name=='name': component['bounds']['bounds']='145 18 150 36'
 elif name=='value': component['bounds']['bounds']='145 67 150 36'
defs.append(large)
compact=json.loads(json.dumps(next(d for d in defs if d.get('key')=='knobUni')))
compact['key']='compactMainMix'
for component in compact['value']['componentsData']:
 name=component['componentData']['name']
 if name=='focus': component['bounds']['bounds']='0 0 245 107'
 elif name=='knob': component['bounds']['bounds']='8 8 90 90'
 elif name=='name': component['bounds']['bounds']='110 12 156 36'
 elif name=='value': component['bounds']['bounds']='110 52 135 42'
defs.append(compact)
raw=raw[:defs_start]+json.dumps(defs)+raw[defs_start+defs_len:]
gs=raw.index('"tabName": "GRAINS"'); ge=raw.index('"qlinkBoundsData"',gs)
section=raw[gs:ge]; start=section.index('"componentsData": [')+len('"componentsData": [')
loop_frame={'version':2,'componentData':{'version':1,'name':'Loop settings group','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'loop-settings-frame.png'}},
 'handle remapping':{'version':1,'map':[]},'bounds':{'version':1,'acceptsHWFocus':'No',
 'showWhenDataModelInvalid':'Show','whenVisible':'Always','boundsType':'Absolute','bounds':'655 20 315 310'}}
section=section[:start]+json.dumps(loop_frame)+','+section[start:]
controls=[stereo_entry('Loop Feedback','knobUni',{'version':1,'handleName':'Data'},9,'685 45 278 107','Yes'),
 stereo_entry('Loop Time','knobUniMenu',{'version':1,'handleName':'Data'},25,'685 196 278 107','Yes')]
last=section.rfind(']');section=section[:last].rstrip()+','+','.join(json.dumps(c) for c in controls)+'\n'+section[last:]
raw=raw[:gs]+section+raw[ge:]
shutil.copy2(project/'assets'/'loop-settings-frame.png',skins/'loop-settings-frame.png')
for slug in ('center','left-right','right-left','spread'):
 for state in ('on','off'):
  name='stereo-%s-%s.png'%(slug,state)
  shutil.copy2(project/'assets'/name,skins/name)
for name in ('clear-pool-off.png', 'clear-pool-on.png', 'capture-button-off.png', 'capture-button-on.png', 'order-played-off.png', 'order-played-on.png', 'order-random-off.png', 'order-random-on.png', 'order-weave-off.png', 'order-weave-on.png', 'rhythm-step-off.png', 'rhythm-step-on.png', 'rhythm-step-strip.png', 'rhythm-ring.png', 'playhead-strip.png', 'clear-confirm-panel.png', 'clear-confirm-yes.png', 'clear-confirm-cancel.png', 'clear-confirm-cancel-on.png'):
    shutil.copy2(project / 'assets' / name, skins / name)
# Draw the Info text as an image, using the same display method as other artwork.
info_start = raw.index('"tabName": "INFO"')
info_end = raw.index('"qlinkBoundsData"', info_start)
section = raw[info_start:info_end]
pos = section.index('"componentsData": [') + len('"componentsData": [')
entry = {'version':2,'componentData':{'version':1,'name':'Info text','type':'Image',
 'data':{'version':2,'imageType':'Regular','colour':'0','image':'info-text.png'}},
 'handle remapping':{'version':1,'map':[]},
 'bounds':{'version':1,'acceptsHWFocus':'No','showWhenDataModelInvalid':'Show',
 'whenVisible':'Always','boundsType':'Absolute','bounds':'0 0 1280 624'}}
section = section[:pos] + json.dumps(entry) + section[pos:]
raw = raw[:info_start] + section + raw[info_end:]
shutil.copy2(project/'assets'/'info-text.png', skins/'info-text.png')
raw = raw.replace('"tabName": "GRAINS"', '"tabName": "SETTINGS"')
raw = raw.replace('"tabName": "MARKOV"', '"tabName": "PATTERN"')
from info_merge import combine_info, update_qlinks
raw = combine_info(raw, skins, json.loads((project / "plugin.json").read_text())["version"])
update_qlinks(qlink_path)
path.write_text(raw)
print('Added shared artwork and Main controls.')

for segment in range(64):
    shutil.copy2(project / 'assets' / ('rhythm-large-sector-%02d.png' % segment), skins / ('rhythm-large-sector-%02d.png' % segment))
for name in ('rhythm-large-step-strip.png','rhythm-large-playhead-strip.png'):
    shutil.copy2(project/'assets'/name,skins/name)

# The SDK and artwork generators may produce images not used by this skin.
# Keep the checked-in skin and packaged plugin limited to referenced images.
referenced_images = set()
def collect_images(value):
    if isinstance(value, dict):
        for child in value.values(): collect_images(child)
    elif isinstance(value, list):
        for child in value: collect_images(child)
    elif isinstance(value, str) and value.lower().endswith('.png'):
        referenced_images.add(Path(value).name)
collect_images(json.loads(path.read_text()))
for image_path in skins.glob('*.png'):
    if image_path.name not in referenced_images:
        image_path.unlink()

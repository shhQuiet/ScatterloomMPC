#!/usr/bin/env python3
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont, ImageFilter
out=Path(__file__).resolve().parents[1]/'assets'
try: font=ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc',22)
except OSError: font=ImageFont.load_default()
for n in range(1,10):
 for state,background,border,text in [
  ('off','#172221','#3b514c','#6c7770'),
  ('on','#624a2a','#d7a758','#fff0cf'),
  ('flash','#f5d286','#fff0bd','#29302a')]:
  im=Image.new('RGBA',(60,60),(0,0,0,0));d=ImageDraw.Draw(im)
  d.rounded_rectangle((1,1,58,58),radius=7,fill=background,outline=border,width=2)
  d.text((30,31),str(n),font=font,fill=text,anchor='mm')
  im.save(out/f'pool-pad-{n}-{state}.png')
# Playback glow is pre-rendered so fading needs only occasional image changes.
for n in range(1,10):
 for level in range(1,6):
  im=Image.open(out/f'pool-pad-{n}-on.png').convert('RGBA')
  light=Image.new('RGBA',(60,60),(0,0,0,0)); d=ImageDraw.Draw(light)
  d.ellipse((11,11,49,49),fill=(255,209,110,round(32*level)))
  light=light.filter(ImageFilter.GaussianBlur(8)); im=Image.alpha_composite(im,light)
  d=ImageDraw.Draw(im);d.text((30,31),str(n),font=font,fill='#fff4d7',anchor='mm')
  im.save(out/f'pool-pad-{n}-glow-{level}.png')
active=Image.new('RGBA',(60,60),(0,0,0,0))
ImageDraw.Draw(active).rounded_rectangle((1,1,58,58),radius=5,outline='#a4d5c4',width=3)
active.save(out/'pool-pad-active-outline.png')
Image.new('RGBA',(60,60),(0,0,0,0)).save(out/'pool-pad-touch.png')

pressed=Image.new('RGBA',(60,60),(0,0,0,0))
ImageDraw.Draw(pressed).rounded_rectangle((1,1,58,58),radius=7,outline='#fff5ce',width=3)
pressed.save(out/'pool-pad-touch-on.png')

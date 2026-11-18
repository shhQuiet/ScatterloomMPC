#!/usr/bin/env python3
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
p=Path(__file__).resolve().parents[1]/'assets'/'loop-settings-frame.png'
im=Image.new('RGBA',(315,310),(0,0,0,0));d=ImageDraw.Draw(im)
d.rounded_rectangle((1,10,313,308),radius=9,fill=(12,22,22,105),outline=(119,164,151,170),width=1)
f=ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc',15);label='LOOP SETTINGS';b=d.textbbox((15,2),label,font=f)
d.rectangle((b[0]-4,0,b[2]+4,22),fill=(13,21,22,245));d.text((15,2),label,font=f,fill=(172,207,192,255));im.save(p)

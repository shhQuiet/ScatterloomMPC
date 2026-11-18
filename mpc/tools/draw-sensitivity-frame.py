#!/usr/bin/env python3
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
p=Path(__file__).resolve().parents[1]/'assets'/'capture-sensitivity-frame.png'
im=Image.new('RGBA',(338,310),(0,0,0,0));d=ImageDraw.Draw(im)
d.rounded_rectangle((1,10,336,308),radius=9,fill=(12,22,22,105),outline=(119,164,151,170),width=1)
try: font=ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc',15)
except OSError: font=ImageFont.load_default()
label='CAPTURE SENSITIVITY'
b=d.textbbox((15,2),label,font=font)
d.rectangle((b[0]-4,0,b[2]+4,22),fill=(13,21,22,245))
d.text((15,2),label,font=font,fill=(172,207,192,255))
im.save(p)

#!/usr/bin/env python3
"""Draw the MPC license removal confirmation artwork."""
import sys
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
out=Path(sys.argv[1])
font='/System/Library/Fonts/Helvetica.ttc'
image=Image.new('RGBA',(500,230),(22,25,26,255))
d=ImageDraw.Draw(image)
d.rounded_rectangle((1,1,498,228),radius=14,fill='#16191a',outline='#efad4d',width=3)
d.text((250,48),'REMOVE LICENSE?',font=ImageFont.truetype(font,24),fill='#ffca7e',anchor='mm')
d.text((250,91),'You can register again later.',font=ImageFont.truetype(font,20),fill='#ffffff',anchor='mm')
image.save(out/'license-confirm-panel.png')
button=Image.new('RGBA',(175,60),(0,0,0,0))
d=ImageDraw.Draw(button)
d.rounded_rectangle((1,1,173,58),radius=8,fill='#332f29',outline='#efad4d',width=2)
d.text((87,30),'REMOVE',font=ImageFont.truetype(font,22),fill='#ffca7e',anchor='mm')
button.save(out/'license-confirm-remove.png')

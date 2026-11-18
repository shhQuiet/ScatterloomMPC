#!/usr/bin/env python3
from PIL import Image, ImageDraw
from pathlib import Path
p=Path(__file__).resolve().parents[1]/'assets'
w=h=52
from PIL import ImageFont
try: percent_font=ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc',13)
except OSError: percent_font=ImageFont.load_default()
im=Image.new('RGBA',(w,h*101),(0,0,0,0))
for i in range(101):
 d=ImageDraw.Draw(im); y=i*h
 d.rounded_rectangle((1,y+1,50,y+50),radius=4,fill='#111c1c',outline='#52706a',width=1)
 if i: d.rounded_rectangle((5,y+47-max(1,round(i*.4)),46,y+46),radius=2,fill='#b8813d')
im.save(p/'markov-bar-strip.png')
im=Image.new('RGBA',(w,h),(0,0,0,0)); ImageDraw.Draw(im).rounded_rectangle((1,1,50,50),radius=4,outline='#f4db99',width=3);im.save(p/'markov-selected.png')
Image.new('RGBA',(w,h),(0,0,0,0)).save(p/'markov-transparent.png')

labels=Image.new('RGBA',(610,580),(0,0,0,0)); d=ImageDraw.Draw(labels)
try:
 from PIL import ImageFont
 font=ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc',15)
except OSError:
 font=None
for i in range(9):
 d.text((91+i*55,39),str(i+1),fill='#dfd6c1',font=font,anchor='mm')
 d.text((50,89+i*55),str(i+1),fill='#dfd6c1',font=font,anchor='mm')
d.text((315,15),'NEXT GRAIN',fill='#a8cbc0',font=font,anchor='mm')
axis=Image.new('RGBA',(180,24),(0,0,0,0))
ImageDraw.Draw(axis).text((90,12),'CURRENT GRAIN',fill='#a8cbc0',font=font,anchor='mm')
axis=axis.rotate(90,expand=True)
labels.alpha_composite(axis,(3,219))
labels.save(p/'markov-labels.png')

playing=Image.new('RGBA',(w,h),(0,0,0,0))
ImageDraw.Draw(playing).rounded_rectangle((3,3,48,48),radius=4,fill=(115,205,181,48),outline=(145,220,198,135),width=2)
playing.save(p/'markov-playing.png')

Image.new('RGBA',(516,52),(4,10,10,185)).save(p/'markov-dim-row.png')
Image.new('RGBA',(52,520),(4,10,10,185)).save(p/'markov-dim-column.png')

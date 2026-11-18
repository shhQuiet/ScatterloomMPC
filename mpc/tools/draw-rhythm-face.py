#!/usr/bin/env python3
"""Draw the opaque, softly shaded instrument face for the rhythm display."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFilter
import math
n=420; c=(n-1)/2
im=Image.new('RGBA',(n,n)); px=im.load()
for y in range(n):
 for x in range(n):
  dx=x-c;dy=y-c;r=math.hypot(dx,dy)
  if r>209: continue
  light=max(-1,min(1,(-dx-dy)/275))
  if r>=200:
   k=0.5+0.5*light
   color=(int(69+25*k),int(75+24*k),int(65+20*k))
  elif r>=195:
   color=(26,37,34)
  else:
   k=0.5+0.5*light
   # Interlaced, low-contrast threads recall the plugin's woven background.
   warp = math.exp(-((math.sin((x+y)*0.115)/0.18)**2))
   weft = math.exp(-((math.sin((x-y)*0.11)/0.18)**2))
   thread = 3.3*warp + 2.5*weft
   color=(int(22+5*k+thread),int(34+7*k+thread),int(31+6*k+thread))
  px[x,y]=(*color,255)
d=ImageDraw.Draw(im)
d.ellipse((1,1,418,418),outline=(139,126,94,230),width=2)
d.ellipse((9,9,410,410),outline=(157,137,97,135),width=2)
d.ellipse((14,14,405,405),outline=(12,24,22,200),width=2)
im.save(Path(__file__).resolve().parents[1]/'assets'/'rhythm-instrument-face.png',optimize=True)

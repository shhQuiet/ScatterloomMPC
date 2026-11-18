#!/usr/bin/env python3
"""Create larger, frame-preserving copies of the existing rhythm artwork."""
from pathlib import Path
from PIL import Image
p=Path(__file__).resolve().parents[1]/'assets'
def scale_strip(src,dst,width,frame_height,frames):
    im=Image.open(p/src).convert('RGBA')
    assert im.height % frames == 0
    old_h=im.height//frames
    out=Image.new('RGBA',(width,frame_height*frames),(0,0,0,0))
    for n in range(frames):
        frame=im.crop((0,n*old_h,im.width,(n+1)*old_h))
        out.paste(frame.resize((width,frame_height),Image.Resampling.LANCZOS),(0,n*frame_height))
    out.save(p/dst,optimize=True)
for n in range(64):
    scale_strip(f'rhythm-sector-{n:02d}.png',f'rhythm-large-sector-{n:02d}.png',86,86,24)
scale_strip('rhythm-step-strip.png','rhythm-large-step-strip.png',30,30,2)
scale_strip('playhead-strip.png','rhythm-large-playhead-strip.png',30,30,2)

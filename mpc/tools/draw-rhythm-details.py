#!/usr/bin/env python3
"""Render the rhythm fraction and playhead trail at skin pixel resolution."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont, ImageFilter
assets = Path(__file__).resolve().parents[1] / 'assets'
font = ImageFont.truetype('/System/Library/Fonts/Supplemental/Georgia Bold.ttf', 35)
for name, numbers in [('pulses', range(33)), ('steps', range(1, 33))]:
    strip = Image.new('RGBA', (70, 45 * len(numbers)))
    for i, value in enumerate(numbers):
        frame = Image.new('RGBA', (70, 45))
        draw = ImageDraw.Draw(frame)
        text = str(value)
        box = draw.textbbox((0, 0), text, font=font, stroke_width=0)
        x = (70 - (box[2] - box[0])) / 2 - box[0]
        y = (45 - (box[3] - box[1])) / 2 - box[1]
        draw.text((x+1, y+2), text, font=font, fill='#352d26')
        draw.text((x, y), text, font=font, fill='#e8d3a2', stroke_width=1, stroke_fill='#8d7654')
        strip.paste(frame, (0, i * 45))
    strip.save(assets / f'rhythm-fraction-{name}.png', optimize=True)
line = Image.new('RGBA', (54, 3))
ImageDraw.Draw(line).rounded_rectangle((0, 0, 53, 2), radius=1, fill='#a68c62')
line.save(assets / 'rhythm-fraction-divider.png')
source = Image.open(assets / 'rhythm-large-playhead-strip.png').convert('RGBA')
head = source.crop((0, 30, 30, 60))
for i in range(64):
    # At the top of the circle, clockwise movement comes from the left.
    glow = Image.new('RGBA', (70,70))
    d = ImageDraw.Draw(glow)
    for x, a in [(8,25),(12,38),(16,54),(20,70),(24,92),(28,110)]:
        d.ellipse((x-5, 30, x+5, 40), fill=(232,179,97,a))
    glow = glow.filter(ImageFilter.GaussianBlur(3))
    glow = glow.rotate(-i*360/64, resample=Image.Resampling.BICUBIC)
    glow.alpha_composite(head, (20,20))
    strip=Image.new('RGBA',(70,140));strip.alpha_composite(glow,(0,70))
    strip.save(assets / f'rhythm-trail-{i:02d}.png', optimize=True)

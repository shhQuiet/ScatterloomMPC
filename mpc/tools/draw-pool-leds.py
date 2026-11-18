#!/usr/bin/env python3
"""Draw the pool indicators used by the MPC skin."""
from pathlib import Path
from PIL import Image, ImageDraw

target = Path(__file__).resolve().parents[1] / 'assets'
for name, fill, border in [
    ('off', '#222c2b', '#59645c'),
    ('on', '#e4a33e', '#f7cf83'),
    ('flash', '#fff2b2', '#ffffff'),
]:
    image = Image.new('RGBA', (24, 24), (0, 0, 0, 0))
    ImageDraw.Draw(image).ellipse((2, 2, 21, 21), fill=fill, outline=border, width=2)
    image.save(target / ('pool-led-' + name + '.png'))

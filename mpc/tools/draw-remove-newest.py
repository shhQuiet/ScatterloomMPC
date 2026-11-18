#!/usr/bin/env python3
"""Draw a compact remove-newest button."""
from pathlib import Path
from PIL import Image, ImageDraw

target = Path(__file__).resolve().parents[1] / 'assets'
for state, fill in [('off', '#26302e'), ('on', '#526464')]:
    image = Image.new('RGBA', (91, 70), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    draw.rounded_rectangle((1, 1, 89, 68), radius=9, fill=fill, outline='#9aae9d', width=2)
    draw.arc((26, 15, 64, 54), start=230, end=535, fill='#f0e6d6', width=4)
    draw.polygon([(25, 22), (39, 22), (26, 35)], fill='#f0e6d6')
    image.save(target / ('remove-newest-' + state + '.png'))

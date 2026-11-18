#!/usr/bin/env python3
"""Draw the temporary demo-silence notice for the MPC skin."""
import sys
from PIL import Image, ImageDraw, ImageFont
image = Image.new('RGBA', (1280, 624), (7, 15, 16, 172))
draw = ImageDraw.Draw(image)
font = ImageFont.truetype('/System/Library/Fonts/Helvetica.ttc', 72)
draw.text((640, 312), 'UNREGISTERED', font=font, fill=(242, 233, 215, 255), anchor='mm')
image.save(sys.argv[1])

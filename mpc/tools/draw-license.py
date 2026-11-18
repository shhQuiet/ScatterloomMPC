#!/usr/bin/env python3
"""Create the fixed license-page artwork (requires Pillow and qrcode)."""
import sys
from pathlib import Path
import qrcode
from PIL import Image, ImageDraw, ImageFont

url = 'https://elsewave.pages.dev/mpc/scatterloom/register'
image = Image.new('RGBA', (1280, 624), (0, 0, 0, 0))
qr = qrcode.QRCode(error_correction=qrcode.constants.ERROR_CORRECT_H, box_size=6, border=4)
qr.add_data(url)
qr.make(fit=True)
qr_image = qr.make_image(fill_color='#102a2c', back_color='#d6e5db').convert('RGBA')
# Keep a clear quiet zone and a small centered emblem; high error correction
# allows for the covered modules while preserving scan reliability.
logo_path = Path(__file__).resolve().parents[2] / 'assets' / 'elsewave-scatterloom-lockup.png'
logo = Image.open(logo_path).convert('RGBA').crop((60, 125, 560, 650))
logo.thumbnail((50, 50), Image.Resampling.LANCZOS)
qr_draw = ImageDraw.Draw(qr_image)
cx, cy = qr_image.width // 2, qr_image.height // 2
qr_draw.rounded_rectangle((cx - 32, cy - 32, cx + 32, cy + 32), radius=8, fill='#d6e5db')
qr_image.alpha_composite(logo, (cx - logo.width // 2, cy - logo.height // 2))
image.alpha_composite(qr_image, (240, 115))
draw = ImageDraw.Draw(image)
font = '/System/Library/Fonts/Helvetica.ttc'
draw.text((640, 210), 'Scan the QR or visit:', font=ImageFont.truetype(font, 25), fill='#f0e6d6')
link_text = 'elsewave.pages.dev/mpc/scatterloom/register'
link_font = ImageFont.truetype(font, 24)
draw.text((640, 255), link_text, font=link_font, fill='#f0e6d6')
draw.text((640, 315), 'Open the page on your phone or computer.', font=ImageFont.truetype(font, 23), fill='#f0e6d6')
image.save(sys.argv[1])

for name, title in [('start', 'Get code'), ('refresh', 'Refresh code')]:
 for state, color in [('off', '#394848'), ('on', '#526464')]:
    button = Image.new('RGBA', (210, 48), (0, 0, 0, 0))
    d = ImageDraw.Draw(button)
    d.rounded_rectangle((1, 1, 208, 46), radius=9, fill=color, outline='#8eaaa0', width=2)
    d.text((105, 24), title, anchor='mm', font=ImageFont.truetype(font, 22), fill='#f0e6d6')
    button.save(str(Path(sys.argv[1]).parent / ('license-' + name + '-' + state + '.png')))
Image.new('RGBA', (355, 4), '#f0e6d6').save(str(Path(sys.argv[1]).parent / 'license-expired-line.png'))

# Certificate artwork is static; the verified email is supplied by the plugin.
certificate = Image.new('RGBA', (1280, 624), (0, 0, 0, 0))
d = ImageDraw.Draw(certificate)
d.rounded_rectangle((272, 55, 1008, 438), radius=18, fill='#1d2929', outline='#819f91', width=3)
d.rounded_rectangle((286, 69, 994, 424), radius=12, outline='#506b60', width=1)
wordmark = Image.open(logo_path).convert('RGBA').crop((575, 350, 1950, 610))
wordmark.thumbnail((310, 58), Image.Resampling.LANCZOS)
certificate.alpha_composite(wordmark, (640 - wordmark.width // 2, 108 - wordmark.height // 2))
d.text((640, 190), 'Registered to', anchor='mm', font=ImageFont.truetype(font, 22), fill='#a9c4b6')
seal = Image.open(Path(__file__).resolve().parents[1] / 'assets' / 'license-seal.png').convert('RGBA')
seal.thumbnail((86, 86), Image.Resampling.LANCZOS)
# A low-opacity impression supports the certificate without competing with text.
seal.putalpha(seal.getchannel('A').point(lambda value: int(value * 0.32)))
certificate.alpha_composite(seal, (885, 329))
certificate.save(str(Path(sys.argv[1]).parent / 'license-certificate.png'))
for key, title in [('reregister', 'Re-register'), ('remove', 'Remove license')]:
 for state, color in [('off', '#394848'), ('on', '#526464')]:
    button = Image.new('RGBA', (190, 44), (0, 0, 0, 0))
    d = ImageDraw.Draw(button)
    d.rounded_rectangle((1, 1, 188, 42), radius=7, fill=color, outline='#78968a', width=1)
    d.text((95, 22), title, anchor='mm', font=ImageFont.truetype(font, 18), fill='#d8e4d8')
    button.save(str(Path(sys.argv[1]).parent / ('license-' + key + '-' + state + '.png')))

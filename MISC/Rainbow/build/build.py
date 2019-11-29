#!/usr/bin/env python
from PIL import Image, ImageDraw, ImageFont
from time import time
import random

random.seed(int(time()))

flag = '1011chAs3_1He_raInb0w!!1227'

RGB = [0, 8, 16]
x = 20
y = 25
width  = 25
heigth = 80 

font_file = '/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf'
font_size = 60
fnt = ImageFont.truetype(font_file, font_size)

img = Image.new('RGB', (len(flag) * width + 250, 130), 'white')
draw = ImageDraw.Draw(img)

draw.text((x, heigth * 3 / 7), "flag{", font=fnt, fill='black')
x += draw.textsize('flag{', font=fnt)[0]

# Gerenate colors
prev = -1
colors = []
for c in flag:
    bit = random.choice(RGB)
    while bit == prev:
        bit = random.choice(RGB)
    prev = bit
    colors.append(ord(c) << bit)

# Draw squares
for clr in colors:
    pos = ((x, y), (x + width, y), (x + width, y + heigth), (x, y + heigth))
    draw.polygon(pos, fill=clr)
    x += width

draw.text((x, heigth * 3 / 7), '}', font=fnt, fill='black')

with open('flag.png', 'wb') as fp:
    img.save(fp, 'PNG')

img.show()


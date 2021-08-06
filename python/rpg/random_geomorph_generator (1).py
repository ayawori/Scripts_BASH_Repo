from __future__ import print_function
# Random Geomorph Map Generator
# Developer (code only): Warren, https://www.patreon.com/rpgpython
# Inspired by Sidekicks: Beyond the Essentials by Paul Metzger
# User of script responsible for following Community Content Agreement and Copyright
# Script Version Number: v1.0
# Date: 29 March 2021

# If script errors, you may need to install the random package
# pip install random2
# pip install os
# pip install PIL
# Installing packages: https://packaging.python.org/tutorials/installing-packages/
from PIL import Image
import random
import os

# CHANGE THIS TO A PATH OF YOUR CHOICE ON YOUR COMPUTER
# THIS IS THE DIRECTORY THAT HOLDS ALL OF YOUR RANDOM GEOMORPH TILE IMAGES
path = "/users/warren/documents/geomorph_tiles/"

files = [path + random.choice(os.listdir(path)),
         path + random.choice(os.listdir(path)),
         path + random.choice(os.listdir(path)),
         path + random.choice(os.listdir(path)),]

result = Image.new("RGB", (1600, 1600))

for index, file in enumerate(files):
  path = os.path.expanduser(file)
  img = Image.open(path)
  img.thumbnail((800, 800), Image.ANTIALIAS)
  x = index // 2 * 800
  y = index % 2 * 800
  w, h = img.size
  #print('pos {0},{1} size {2},{3}'.format(x, y, w, h))
  result.paste(img, (x, y, x + w, y + h))

img_name = random.randrange(1,100000001,1)
# CHANGE THIS TO A PATH OF YOUR CHOICE ON YOUR COMPUTER
# THIS IS WHERE THE CREATED RANDOM FILE WILL BE WRITTEN TO ON YOUR COMPUTER
result.save(os.path.expanduser('~/Documents/geomorph_generated/image_' + str(img_name) + '.jpg'))

print("Done.")
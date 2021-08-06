# remnants.py

# Remnants, Auto-Generation
# Developer (code only): Warren, https://www.patreon.com/rpgpython
# Script Version Number: v1.0
# Date: 03 Apr 2021

# If script errors, you may need to install the random package
# https://pypi.org/project/random2/
# pip install random2
# Installing packages: https://packaging.python.org/tutorials/installing-packages/
import random

remnants = random.choice (['road','tombstone','signpost','channel','masonry','bridge','wall',
                           'edifice','works','structure'])
r_choice=''
if(remnants == 'road'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'a track'
    if(r==2): r_choice = 'a trail'
    if(r==3): r_choice = 'which is made of gravel'
    if(r==4): r_choice = 'which is very muddy'
    if(r==5): r_choice = 'which is very bumpy'
    if(r==6): r_choice = 'which has deep grooves'
        
if(remnants == 'tombstone'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'a plaque'
    if(r==2): r_choice = 'a cairn'
    if(r==3): r_choice = 'a staff'
    if(r==4): r_choice = 'a beacon'
    if(r==5): r_choice = 'a pyre'
    if(r==6): r_choice = 'a stone pile'
        
if(remnants == 'signpost'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'a guide'
    if(r==2): r_choice = 'an omen'
    if(r==3): r_choice = 'a trade'
    if(r==4): r_choice = 'a warning'
    if(r==5): r_choice = 'an emblem'
    if(r==6): r_choice = 'a boundry stone'
                
if(remnants == 'channel'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'a tunnel'
    if(r==2): r_choice = 'a pipe'
    if(r==3): r_choice = 'a well'
    if(r==4): r_choice = 'a passage'
    if(r==5): r_choice = 'a canal'
    if(r==6): r_choice = 'an aqueduct'
        
if(remnants == 'masonry'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'mud bricks'
    if(r==2): r_choice = 'stone bricks'
    if(r==3): r_choice = 'marble bricks'
    if(r==4): r_choice = 'plaster'
    if(r==5): r_choice = 'wattle'
    if(r==6): r_choice = 'stone blocks'
             
if(remnants == 'bridge'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'made of rope'
    if(r==2): r_choice = 'made of wood'
    if(r==3): r_choice = 'made of stone'
    if(r==4): r_choice = 'made of earth'
    if(r==5): r_choice = 'naturally made'
    if(r==6): r_choice = 'made of brick'
        
if(remnants == 'wall'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'a stockade'
    if(r==2): r_choice = 'a barricade'
    if(r==3): r_choice = 'a fence'
    if(r==4): r_choice = 'a rampart'
    if(r==5): r_choice = 'a dike'
    if(r==6): r_choice = 'a partition'


if(remnants == 'edifice'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'a carved cliff'
    if(r==2): r_choice = 'a sculptured mound'
    if(r==3): r_choice = 'a colossal statue'
    if(r==4): r_choice = 'a palace'
    if(r==5): r_choice = 'a mill'
    if(r==6): r_choice = 'a calendar stone'
        
        
if(remnants == 'works'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'an arsenal'
    if(r==2): r_choice = 'a granary'
    if(r==3): r_choice = 'a paved plaza'
    if(r==4): r_choice = 'a viaduct'
    if(r==5): r_choice = 'a reservoir'
    if(r==6): r_choice = 'a cistern'
        
        
if(remnants == 'structure'):
    r = random.randrange(1,7,1)
    if(r==1): r_choice = 'a stairway'
    if(r==2): r_choice = 'a ramp'
    if(r==3): r_choice = 'a shaft'
    if(r==4): r_choice = 'a spire'
    if(r==5): r_choice = 'a roof'
    if(r==6): r_choice = 'a tunnel'
    
print('You have come across the small remains of a ' + remnants + ', ' + r_choice + '.' )
# remnants.py
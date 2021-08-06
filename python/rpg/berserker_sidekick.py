# Random Berserker Sidekick, Auto-Generation
# Developer (code only): Warren, https://www.patreon.com/rpgpython
# Inspired by Sidekicks: Beyond the Essentials by Paul Metzger
# User of script responsible for following Community Content Agreement and Copyright
# Script Version Number: v1.0
# Date: 06 April 2021

# If script errors, you may need to install the random package
# https://pypi.org/project/random2/
# pip install random2
# Installing packages: https://packaging.python.org/tutorials/installing-packages/
import random

level = input('What level do you want your Berserker Sidekick to be (1-20)? ')

def modifiers(score):
    if(score == 1): return -5
    if(score >=2 and score <=3): return '-4'
    if(score >=4 and score <=5): return '-3'
    if(score >=6 and score <=7): return '-2'
    if(score >=8 and score <=9): return '-1'
    if(score >=10 and score <=11): return '+0'
    if(score >=12 and score <=13): return '+1'
    if(score >=14 and score <=15): return '+2'
    if(score >=16 and score <=17): return '+3'
    if(score >=18 and score <=19): return '+4'
    if(score >=20 and score <=21): return '+5'
    if(score >=22 and score <=23): return '+6'
    if(score >=24 and score <=25): return '+7'
    if(score >=26 and score <=27): return '+8'
    if(score >=28 and score <=29): return '+9'
    if(score >=30): return '+10'
    

armor = (['Unarmored Defense', '13', 'Stealth: Normal'])


# Character Ability Scores - uses 4d6 and drops lowest
a_scores = []
for x in range (0,6):
    s = random.choices(range(1, 7), k=4) # pick 4 random between 1-6, allow them to be similar
    s.remove(min(s)) # drop lowest 1d6 from the 4 randoms
    a = sum(s)  # add them together
    a_scores.append(a)
    a_scores.sort(reverse = True)

# set ability scores and modifiers from high to low
sth = a_scores[0]; sth_mod = modifiers(sth)
con = a_scores[1]; con_mod = modifiers(con)
dex = a_scores[2]; dex_mod = modifiers(dex)
cha = a_scores[3]; cha_mod = modifiers(cha)
intel = a_scores[4]; intel_mod = modifiers(intel)
wis = a_scores[5]; wis_mod = modifiers(wis)

# other abilities
prof_bonus = 2
hp = 0
print("\n\nBESERKER SIDEKICK (Medium Humanoid)")
print("\nLevel:\t\t\t{}".format(level))
level_dice = int(level)+1
for x in range(0,level_dice):
    hp = hp + (random.randrange(1,13,1))
hp += (int(level)*2) + 2
print("Hit Points:\t\t" + str(hp))
print("Armor Class:\t\t{} ({}, {})".format((int(armor[1]) + int(dex_mod)),armor[0],armor[2]))
print("\nStrength:\t\t{}({})".format(sth,sth_mod))
print("Dexterity:\t\t{}({})".format(dex,dex_mod))
print("Constitution:\t\t{}({})".format(con,con_mod))
print("Intelligence:\t\t{}({})".format(intel,intel_mod))
print("Wisdom:\t\t\t{}({})".format(wis,wis_mod))
print("Charisma:\t\t{}({})".format(cha,cha_mod))
print("\nProficency Bonus:\t+{}".format(prof_bonus))
print("Proficiencies:\t\tSimple Melee, Martial Melee")
print("Languages:\t\tCommon, +1 (you pick)")
print("Saving Throws:\t\tDex(+{}), Con(+{})".format(int(sth_mod) + int(prof_bonus),
                                              (int(con_mod) + int(prof_bonus))))
print("Skills:\t\t\tAthletics +{}, Intimidation +{}, Survival +{}".format((int(prof_bonus)+int(dex_mod)),
                                                                 (int(prof_bonus)+int(cha_mod)),
                                                                 (int(prof_bonus)+int(wis_mod))))
print("Senses:\t\t\tpassive Perception {}".format(10 + (int(prof_bonus)+int(wis_mod))))
print("Bonus Action: 2nd one-handed handaxe attack, if not used two-handed.")
print("Weapons:\t\tpick 1 Martial Melee, and 1 Simple Melee")

# Feel free to adjust these features or add more as you see fit!
features = (['Rage as a bonus action. Ends until end of combat. +2 melee damage. Resistance to bludgeoning, piercing, and slashing damage. Once per long rest.',
             'First attack can be reckless, granting advantage on all melee attack rolls during this turn. All attack rolls against Berserker have advantage until start of their next turn.',
             'Strength score increases +1.',
             'Proficency bonus increases to +1',
             'Extra Attack',
             'Ability score improvement, add +1',
             'Advantage on initiative rolls, next combat.',
             'Cannot be surprised next attempt by an enemy.',
             'While in rage, enemy had disadvantage on opportunity attacks. Can dash as a bonus action.',
             'Advantage on Strength Checks made to push, pull, or lift objects.',
             'Cannot be charmed or frightened while raging.',
             'While raging, Gain 10 temporary it points.',
             'Add 1 additional damage die for a critical hit with a melee weapon attack.',
             'Forego an attack to intimidate a creature within 30ft. Enemy must succeed DC 14 Wisdom saving throw.',
             '+1 bonus to AC for duration of rage.',
             'While raging, 0hp does not knock unconcious, drops only to 1hp. Falls unconcious when raging ends.',
             'Use strength attribute score in place of strength check if roll is lower.',
             'Embodiment of rage, when raging, Strength is 24(+7) and Constitution is 18(+4). One level of exhaustion when rage ends.'])

print("\nFeatures (Use only one per turn):")
f = 0
if(1 <= int(level) <= 4): f = 1   
if(5 <= int(level) <= 10): f = 3   
if(11 <= int(level) <= 16): f = 5   
if(17 <= int(level) <= 20): f = 7
    
for x in range(0,f):
    feature = random.choice(features)
    features.remove(feature)
    print(str(x+1) + ". " + feature)
    
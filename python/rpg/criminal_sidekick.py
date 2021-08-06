# Random Criminal Sidekick, Auto-Generation
# Developer (code only): Warren, https://www.patreon.com/rpgpython
# Inspired by Sidekicks: Beyond the Essentials by Paul Metzger
# User of script responsible for following Community Content Agreement and Copyright
# Script Version Number: v1.0
# Date: 09 April 2021

# If script errors, you may need to install the random package
# https://pypi.org/project/random2/
# pip install random2
# Installing packages: https://packaging.python.org/tutorials/installing-packages/
import random

level = input('What level do you want your Criminal Sidekick to be (1-20)? ')

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
    

armor = (['Studded Leather', '14', 'Stealth: Normal'])


# Character Ability Scores - uses 4d6 and drops lowest
a_scores = []
for x in range (0,6):
    s = random.choices(range(1, 7), k=4) # pick 4 random between 1-6, allow them to be similar
    s.remove(min(s)) # drop lowest 1d6 from the 4 randoms
    a = sum(s)  # add them together
    a_scores.append(a)
    a_scores.sort(reverse = True)

# set ability scores and modifiers from high to low
dex = a_scores[0]; dex_mod = modifiers(dex)
cha = a_scores[1]; cha_mod = modifiers(cha)
intel = a_scores[2]; intel_mod = modifiers(intel)
con = a_scores[3]; con_mod = modifiers(con)
sth = a_scores[4]; sth_mod = modifiers(sth)
wis = a_scores[5]; wis_mod = modifiers(wis)



# other abilities
prof_bonus = 2
hp = 0
print("\n\nCRIMINAL SIDEKICK (Medium Humanoid)")
print("\nLevel:\t\t\t{}".format(level))
level_dice = int(level)+1
for x in range(0,level_dice):
    hp = hp + (random.randrange(1,9,1))
hp += int(level) + 1
print("Hit Points:\t\t" + str(hp))
print("Armor Class:\t\t{} ({}, {})".format((int(armor[1]) + int(dex_mod)),armor[0],armor[2]))
print("\nStrength:\t\t{}({})".format(sth,sth_mod))
print("Dexterity:\t\t{}({})".format(dex,dex_mod))
print("Constitution:\t\t{}({})".format(con,con_mod))
print("Intelligence:\t\t{}({})".format(intel,intel_mod))
print("Wisdom:\t\t\t{}({})".format(wis,wis_mod))
print("Charisma:\t\t{}({})".format(cha,cha_mod))
print("\nProficency Bonus:\t+{}".format(prof_bonus))
print("Proficiencies:\t\tSimple Melee")
print("Languages:\t\tCommon, +1 (you pick)")
print("Saving Throws:\t\tDex(+{}), Int(+{})".format(int(dex_mod) + int(prof_bonus),
                                              (int(intel_mod) + int(prof_bonus))))
print("Skills:\t\t\tAcrobatics +{}, Intimidation +{}, Deception +{}".format((int(prof_bonus)+int(dex_mod)),
                                                                 (int(prof_bonus)+int(cha_mod)),
                                                                 (int(prof_bonus)+int(cha_mod))))
print("Senses:\t\t\tpassive Perception {}".format(10 + (int(prof_bonus)+int(wis_mod))))
print("Bonus Action: 2nd dagger, melee or thrown, one target, when 1st action to attack is with a dagger.")
print("Weapons:\t\t2 daggers and pick 1 Simple Melee")

# Feel free to adjust these features or add more as you see fit!
base_features = 'Base Features: Double Daggers, Criminal Contact, Disguise Kit, Forgery Kit, Gaming Set, Poisoners Kit, Theives Tools.'
features = (['Bonus action to make a dexterity (slight of hand) check, use theives tools to disarm at trap, or take the use object action.',
             'Climbling no longer cost extra movement.',
             'Dexterity increases +1',
             'Proficiency bonus increases +1',
             'Half attackers damage as a reaction when he/she can see their attacker.',
             'Attempt to hide when they are lightly obscured. Enemy attack that misses does not reveal position.',
             'Social Situations: Add Wisdom modifier to Charisma (Deception) checks.',
             'Advantage on Dexterity (Stealth) checks if they move more than half their speed on the same turn.',
             'Take on a new identity after spending 25GP and 7 days establishing history, profession, affiliations.',
             'When picking mundane/magical locks, treat all rolls as a 20 and suppress arcane lock spell for 10 minutes. Once per long rest.',
             'Makes a check that uses their proficiency bonus, treat d20 rolls of 9 or lower as a 10.',
             'Ignore all class, race, and level requirements on the use of magic items.',
             'Spend 3 hours studying another persons speech and mannerisms, can assume the identity of that person. Has advantage on Charisma (Desception) checks.',
             'AC gains a +2 and can use their reaction when missed by a melee weapon attack to disengage and move up to half their speed without provoking opportunity attack',
             'When anyone in party recover treasure worth at least 200gp, criminal discovers addtional treasure (roll on treasure hoard 0-4 table, pg. 137 DMG).',
             'Can understand all spoken languages, but cannot speak those they are not proficient.',
             'Can present false thoughts telepathically, succeeds on a Charisma (Desception) check contested by the targets Wisdom (Insight) check.',
             'Gains truesight 60ft.'])

print("\nFeatures (Use only one per turn):")
f = 0
if(1 <= int(level) <= 4): f = 1   
if(5 <= int(level) <= 10): f = 3   
if(11 <= int(level) <= 16): f = 5   
if(17 <= int(level) <= 20): f = 7
    
print(base_features)
for x in range(0,f):
    feature = random.choice(features)
    features.remove(feature)
    print(str(x+1) + ". " + feature)
    
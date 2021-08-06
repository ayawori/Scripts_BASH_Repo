# Random Boss Mechanics, Auto-Generation
# Developer (code only): Warren, https://www.patreon.com/rpgpython
# Script Version Number: v1.0
# Date: 19 April 2021

# If script errors, you may need to install the random package
# https://pypi.org/project/random2/
# pip install random2
# Installing packages: https://packaging.python.org/tutorials/installing-packages/
import random


boss = random.choice(["This battle takes place in front of a massive furnace. As the battle goes on, the furnace gets hotter and hotter, to near unbearable levels. Someone needs to tend to the huge furnace while the others battle to keep from melting!",
"The boss will summon enemies that will distract the players from the fact that the boss is healing themselves.",
"The room in which the boss is designed like a long hallway. As the boss grows weaker, they will run further down the long room. Traps cover the room.",
"The boss cannot be close to an object or another boss, or else it will rapidly restore health; keeping it away will make it easier to take down.",
"The boss is blind and takes damage when hit by natural light. Adventurers need to use the boss’s Tremorsense/Echolocation to lead it into beams of light.",
"The boss fuses with slimes to become bigger and stronger, but it can only get so big before it explodes.",
"There are ongoing rituals around the area that must each be disrupted in a specific way within the next few minutes. Each completed ritual empowers the boss with negative energy, escalating the fight and drawing the end times closer.",
"Players must fight from the rafters above a stage while trying to stop the villain from sabotaging a performance going on below.",
"The boss is in a sewer and monsters were placed in the sewer to deal with waste, but they end up attacking both the players and the boss.",
"There is a massive minefield that has a bloodthirsty invisible stalker roaming around it. Mines deal heavy damage to both players and the elemental, and groups that can’t find the stalker have to activate the mines to either kill it or scare it away.",
"The villain casts a spell on the players that makes them speak and describe their actions in iambic pentameter. When the villain dies they cry out saying “I am slain!”",
"The party fights a creature that can turn people into lobsters for a turn if it hits them.",
"The boss is a lich who’s phylactery is a bomb that would destroy the dungeon and everything within a three mile radius. Someone has to disarm the bomb while the other pcs keep the lich busy.",
"The boss is in a gladiator style WWE ring. Through some hints during the fight, the players realize that the boss isnt actually trying to hurt them, and is instead trying to make the fight look as flashy as possible so that they can all survive another day in the arena.",
"The players enter a room with a button and a locked door. If they press it, they are all knocked unconscious and dream about fighting a boss 4-5 cr higher than them. If they die in the dream they wake up in the real world, and the door to the next room is open. They can re-enter the dream to help whittle away at the boss or kill their friends to help speed up the process of them getting completing the dungeon.",
"The boss can only be killed by mortal hands. Weapons, magic spells, and any damage type besides fists/natural weapons cannot damage the boss. Immortals and gods cannot damage it.",
"The boss is a glass golem that can hide and heal inside of mirrors. Players can see the golem in the mirror, but must break the glass to force it to come out.",
"The boss is stationary in the center of the room. When it receives enough damage from one if the cardinal directions it becomes invulnerable to damage from that side, forcing the players manuver around the room and minions to continue damaging it.",
"While walking through a cave they have PCs have accidentally walked into the open mouth of the boss. Tremors felt during random fights of slimes and cubes or small parasites eventually lead to acid pools. Party can flee or fight their way out. Possible risk of digestion if slow.",
"Boss is a wall, slowly shrinking the room and pushing the party to a pit or wall of spikes.",
"Boss is a keg golem. Body is mostly full kegs. Some are filled with beer some are wine. Players can target weak points like corks or bungs to drain alcohol and wound the boss. Once limbs and parts are drained can be burned.",
"A village has a pit of ghouls/zombies. When a love one is dying they toss them in to be turned. You have been tossed in as food.",
"Boss contains a howling void. No verbal commands or spells work. See if the PCS can work with out speaking or writing to each other.",
"Glued together: The boss is two deadly bosses inseparably glued back to back. Their movement is halved/thirded. They are not cooperating with one another. Only one of the individuals is dominant at a time, the other is dragged along. On their turn, roll a d4. On a 1, the bosses bicker amongst themselves and fail to take meaningful action (flip a coin to see if the dominant individual changes). On a 2 or 3, both bosses may attempt to attack a target they are facing but do so with disadvantage. On a four, the dominant boss may make an attack as normal, and the subordinate one attacks with disadvantage. If one individual dies or becomes otherwise incapacitated, the other is permanently dominant and attacks as normal, but its speed remains the same.",
"Bratty halfpint tossing: The arrogant yet naive boss is being carried on a light palanquin by their strongest and fastest minions. The boss refuses to touch the the ground, as it is demeaning … somehow more demeaning than the minions tossing the palanquin between them or using it as a blunt weapon when convenient. The boss is a powerful ranged attacker but spends half their turns shouting confusing orders instead of taking appropriate action. If the boss touches the ground, they have a temper tantrum and launch a very strong AoE spell at the party.",
"Farty Fight: The boss is afflicted with horrible magical indigestion. Roll 1d4, on a 4 the boss, instead of acting, groans and releases a stinking cloud per the spell. They are unaffected by their own stinking cloud.",
"The boss is a support character. Most of their goons are on the tanky side. Whenever their goons drop low, the boss heals them back up. The tanks protect the boss as well.",
"Stand in the Fire! – Boss takes extra damage from opponents who stand in a flow of Necrotic/Negative Energy. This causes the player to be damaged too.",
"Keep him out of the Fire! – There are flows of energy around the room that heal the Boss if he stands in it. You must knock him out of the flows to defeat him.",
"Not-Zs, I hate these guys… – The bosses are a group of evil warrior-sorcerers that are exceedingly powerful, however they become pained and stunned whenever someone uses the letter “z” in conversation.",
"Stone fishing: The boss is hiding in the mouth of a giant stone fish who can swim in the earth like water. The fish can’t go outside a sphere of a certain radius, but it allows the boss to appear from the walls and ceilings and try to smash people.",
"Shadow Tag: The boss can hold a person with advantage by simply standing on that person’s shadow. The boss has multiple spotlights they can move around the battlefield. Although the boss cannot hold people on a dark battlefield, the boss has keen darkvision.",
"Adaptivity Type A) The boss can only be damaged the first time by each attack, after that the boss becomes invulnerable to it until a they have a long rest. The party must come up with new ways to damage the boss. (Switch weapons, new spells, etc.) Adaptivity Type B) The boss is protected by a shield that reflects damage of the type last used to hit the boss.",
"Bug Off! The boss tries to flood the battlefield with an effectively infinite number of tiny, weak, annoying baddies (bats, imps, mosquitoes). They will simply keep coming even if the whole cloud is killed. The sheer number would be lethal if they weren’t driven off by (light, fire, sound, etc) Someone has to keep the antagonistic stimulus going during the boss fight and the boss targets the blocker preferentially.",
"Armor Ecdysis: The boss is wearing powerful heavy armor that takes damage instead of the boss, but makes the boss slow. As the armor is attacked, it breaks off and leaves the boss vulnerable, but the boss gets faster and more maneuverable as a consequence. For each stage of armor that is destroyed, the boss takes more damage, the boss’s heavy attacks get weaker/fewer, they become able to perform light attacks, Movement Speed +, Initiative order +, etc.",
"The boss alternates between attacking and devensive modes. During attacking turns, it gains +10 to all damage but has -5 to attack rolls, can attack 3 times per turn but takes 2x damage from all physical attacks. After a certain amount of hp has been depleted (up to the DM) it switches to defensive mode. In this mode it can’t attack or move, however it takes 1/4 damage from all physical attacks, has a 1 in 6 chance to reflect all damge back to the attacker and heals for Xd4 points (where X is the number of players it faces) at the start of its turn. The defensive mode lasts until it loses enough hp (again, up to the DM) or it recovers back to full health. It then returns to attack mode. The golem had five stages, each denoted by it losing a peice of armour after each defensive stage was ended by it taking damage rather than healing. Each time if returned to attack mode after losing armour, it’s AC was reduced by 1 and its max hp by 20 but it gained an extra +1 to attack rolls.",
"Meta-witch The boss asks the players campaign trivia questions during the battle. If the players answer correctly, the boss loses some hitpoints. Answer wrong and the boss gets to take an extra turn.",
"Every round the boss auto-counters one type of attack at random ever round until the start of ot’s next turn.. Roll a d3- 1: Melee 2: Magic 3: Ranged. If the boss is attacked via melee, it will counter with a melee strike, if the boss is attacked with a ranged strike, it counters with a ranged strike, etc.",
"Alas poor Yorick – The skeleton boss has no head of its own. Instead it uses the skulls of others as a substitute. When it wears someone else’s skull, the boss gets all of their abilities and their appearance. Taking enough damage causes the boss’s current skull to explode. The boss should cycle through several different classes, helped by minions bringing hidden skulls. Eventually it runs out of skulls and attempts to flee, but like the proverbial chicken with its head cut off, can’t tell where it is going.",
"The boss gains resistance to a random damage type for one round, every round.",
"The boss is controlled by a card-based computer and the PCs can remove and insert various punch cards to change the boss’ strategy or disable some of its abilities.",
"The boss is hauled to the center of the courtyard by 3 henchmen. When unloaded, the boss is literally a pile of sentient cinder blocks. His AC is high, but has no movement speed. He can speak and cast magic or use his trusty short sword. If the adventurers investigate his corpse, they find that it just becomes a pile of cinder blocks",
"Pocketcursed: In the lair of the boss, everyone’s pockets, bags, binders, satchels, cases, backpacks, suitcases, luggage, etc become bitey monster jaws. Attempting to retrieve an item or spell component results in (1d4) of damage with a risk of failure.",
"A massive pendulum in the lair reveals the invisible boss when the weight is at its height. The PC’s can attempt using magic or physical means to hold the weight up and keep the enemy visible. The weight can also crash into the PC’s or boss.",
"The boss is a swarm of insects, nanomachines, magic particles, or something else similar. It has a large pool of total hitpoints, representing the amount of mass it has, although this mass can be split over multiple bodies. At the top of the initiative round, the swarm can split into smaller bodies or fuse with adjacent bodies to form larger bodies. For example, for one round they may be a horde of smaller, weaker creatures, and on the next round they may fuse together to become a larger and stronger creature. The DM has a number of stat blocks prepared for creatures this boss can form, each of which has a minimum HP requirement to form. To make things more interesting, there may be stores of additional mass hidden around the battlefield, which the boss will attempt to reach to regenerate hit points and mass. If they want to keep the boss down, the players will have to stop any part of the boss from reaching those stores of HP.",
"A baddie that gains new biological growths every two turns. Starts at like a CR4 with a bunch of health and eventually could be over CR 20. Work fast or PERISH.",
"The boss is being healed by a certain amount, let’s say 5dx per round (x going up depending on how high level the group is) because of healing crystals that are on platforms that need to be climbed in order to break. They each have a certain HP, and after being destroyed they stop healing.",
"The boss is completely invulnerable. But that doesn’t mean they are either physically strong or able to avoid, say, being locked up or captured. They just can’t be physically hurt. Don’t give them spells or fighting ability more than a commoner- just make them impervious to damage.",
"The bosses are a dark mirror of the adventuring party from another plane. One of the main questgivers actually travelled from that plane to the adventurer’s plane and gathered them together because he knew they had great power potential- since he knew of their evil might. Make them twisted versions of the characters, and have the player’s aid come from good versions of baddies the characters fought on their home plane. For example- A gnome cleric was a warlock, the fighter was a death knight, the wizard was an enchanter, etc.",
"The Cult of Six- The Big Bad has powerful hexatic powers. Every sixth attack heals her for twice the damage dealt. The catch-it is any attack, including a poke in the nose. Make sure the characters can catch on to this one.",
"Lights turn off on rounds 2, 6, 10, etcetera and lights flare on in a blinding burst on rounds 4, 8, 12, etcetera and must make a Constitution save to avoid being blinded. Players can close their eyes to avoid the blinding but make their attacks with disadvantage that round.",
"BBEG has a lair full of deadly traps and powerful minions, and always remains one step ahead of the PCs. During the final confrontation, the BBEG is revealed to simply be a clever and well-connected commoner, completely unable to fight head-on with the party.",
"Overcharged- A Half-dragon that gets an increasingly powerful and large aoe attack at the end of each turn, but loses his stacks when knocked prone.",
"Whilst the party is adventuring at sea, their ship is beset by a dragon turtle of legend named Kiirn. An intelligent and greedy sonofabitch, Kiirn sinks ships for their cargo which he then takes to his nest in a cove on a nearby island. The first stage of the fight takes place in the sea with players on a ship, which Kiirn is attempting to sink. The captain of the ship deems la d the only safe haven and heads for the nearest landmass, Kiirn’s island. Along the way Kiirn may become damaged enough to retreat, but the Captain insists on landing and repairing the damage. Otherwise, the ship becomes damaged enough and sets off on a crash course for the beach. The second stage of the fight is a scramble up the beach as an angered Kiirn attempts to kill the party and sailors. Players may stand and fight, attempt to rescue the sailors or flee. Kiirn is less concerned with the cargo than the people at this point. The third stage follows the retreat up the beach, a chase through the rainforest on the island. The players may chase Kiirn to finish him off as he leads them to his cove, or Kiirn may chase the players, angered by their defiance and the damage they’ve done, or perhaps angered that they escaped him at the beach. The fourth stage is a fight in a large cave that leads to the cove. This is the point at which players and Kiirn alike are likely be exhausted and close to death. FINISH HIM. At each stage, Kiirn has a different objective which can vary based on the player’s actions. You can also spice it up with Kiirn having something akin to lair actions in each of the stages as well as environmental opportunities.",
"Each time you hit the boss, and it doesn’t have temporary hit points, it gains 5 temporary hit point. Each time its temporary hit points are depleted, the amount of temporary hit points it gains from being hit increases by 1. A hit that depletes the temporary hit points grants a new set of temporary hit points after the remaining damage has been subtracted from the boss’s regular hit points. You want to use as few and strong attacks as possible against this boss.",
"Torvin the Backbiter – He is a Dwarf warrior who excels at disarming and using his enemies’ weapons against them. He starts unarmed and tries to take the player’s weapons. If he succeeds and makes a successful attack roll with their own weapon, he deals automatic max damage (or more, or less, depending how you want to play it).",
"The Midget Cultists of Oun-Bashon: A group of gnomes or halflings who worship a vile fire deity. The party catches up to them in a live caldera or volcano. Each one is relatively easy to beat, but they less attack and more attempt to grapple and drag themselves and the party into the live volcano, seeking glorious martyrdom in the heat.",
"The boss has a stone that allows him to polymorph at will. If the players steal the stone, the boss loses the ability, but whoever holds the stone is polymorphed randomly every other turn. The Boss tries to get the stone back.",
"The Boss is warded against blades and anything with an edge does half damage. Bludgeoning works as normal. Attacks with wood items do double damage.",
"The boss isn’t targeting the players, but an NPC the players have to protect. Any damage done to the NPC is passed on to the nearest player.",
"The boss is a ghost, with a council of 3 individuals. The boss takes turns possessing each council member every few turns, giving them new class specific spells.",
"Every turn, the boss teleports as a bonus action. Everytime the boss takes damage, it teleports to a random spot in the arena.",
"A necromancer that rips the hearts out of his acolytes, using them to a.) push thru players, dealing dmg for each heart sent and blooding the hearts b.) pull the hearts thru himself to heal for the amount they blooded c.) push/pull himself into position by using the hearts as anchors.",
"Every time the boss kills something, he gains half its max hitpoints. He has a lot of minions and will not hesitate to kill them for a boost.",
"Daughx the Mothtouched- boss can fly and do cool stuff, but is completely mesmerized by the dancing lights spell.",
"A miniboss found in The Woods, a layer of the Abyss run by Granny Gooseflesh, a powerful Night Hag Sorcerer (the whole plane is a dark and forbidding woods, populated by dark versions of various nursery rhymes and fairy tales): The Piper is a powerful bard who summons rat swarms and sends them at the party. When they finally catch up to him, he has stolen and enchanted the children of a village, and uses them as shields/has them attack the party. The children don’t do tons of damage, but they muck up the battlefield and are difficult to fight (because they are little kids).",
"There are three bosses and each one starts with an AC of 15. If the party kills one of them, one round later the other two’s AC jumps up to 25. If the party kills a second one, one round later the last one’s AC jumps to 30. The goal for the party is to kill all three in one round by paying attention to three glyphs on a wall that display how close to death each boss is by how brightly they are glowing.",
"The Necro-dancer. When confronted in his dark lair, the lights suddenly go on, revealing the room to be a massive dace floor. At the start of each turn, “zone of irresistible dance” is cast through speakers that line the walls, which the Necro-dancer has the remote to. Each turn, the Necro dancer summons ‘backup dancer’ skeletons, or something that would be comparatively weak for the party’s level. This goes on until the song ends, at which point a giant disco ball is dropped from the ceiling with the intent to crush the players, taking advantage of the disadvantage dex throws and lowered movement. After that, the dancers stop being summoned, the zone of irresistible dance does not get cast again, and the Necro-dancer is left all alone. The song could also stop by breaking the speakers or remote, or escaping the dance floor.",
"Boss is a low level mage with prototype clones surrounding you. Whenever you kill him, one of the clones wakes up, but gives the mage unique abilities. One clone might lower your AC for the fight, one may have a sneak attack and invisibility, another may cast hunters Mark, and gain the scout reaction to run when an enemy gets too close, all while retaining most of his spells.",
"A pair of sorcerers who are madly in love. When the first one is knocked out, the other sorcerer, as a reaction, casts an incredibly powerful spell at whoever took them out.",
"A boss duo, with a big enemy who hits hard and has a lot of HP, and a little enemy who can hold his own, but mostly assists the big enemy with healing/whatever. Whenever the little enemy is attacked, the big enemy goes crazy as a reaction, dealing a ton of damage, so the party has to try and focus on the big one without harming his buddy.",
"A boss that is vulnerable only if you can’t see it. If someone is looking at it, it can move around and can’t be harmed. However, if no one is looking at it, its movement speed slows to a crawl and it is vulnerable. Cue everyone with their eyes closed, swinging blindly around the room!",
"The One Who Is Many- Boss has 99 copies of himself. A mob attacks the party, all identical. Roll d100 every time the party attacks. The boss shares a portion of his life force with each copy- when his copies are attacked, he takes damage with resistance. When he is attacked, he takes damage with vulnerability. When he has lost a third of his HP, and again when he has lost 2/3, a third becomes illusory looking.",
"A mob boss that starts as several weak combatants, but when one is killed the survivors become stronger.",
"The boss has a mirror hidden somewhere in the room. Anyone reflected in the mirror takes half of the damage inflicted on the boss. If the mirror is shattered, the boss gains vulnerability to all damage.",
"The boss is a corrupted holy artifact with lots of HP. The artifact’s environmental effect causes the party to regenerate HP and it also fires healing beams. Healing beyond a creature’s natural HP cap is added as temporary hitpoints. If any creature gains more than twice their HP in temporary hitpoints they die. Important detail: the boss cannot benefit from the regenerative environmental effect.",
"Initially weak boss with lots of minions, but as the minions die, buff up the boss bit by bit. Either the players press through enemies to quickly kill them or they cut through an army and fight a big old baddy.",
"A powerful knight is bound to the Bad Guy’s service. He has to obey anyone who says “please” to him first. The Bad Guy has deafened him so he can’t hear, but if you cure that…",
"A nearly impenetrable (if you dont take him out to dinner first) demon in a human shell, covered in runic tattoos- but if you land an arrow in the circle tattoo on his neck it allows damage to hit the target for the next 10 rounds or maybe however long the arrow is on target. Possible difficulty up- he’s able to remove the arrows by passing a strength save.",
"The Oracle had managed to somehow imprison their (God/Angel), piercing their immortal skin and chaining it up, leaving the weeping deity of rebirth constantly dripping blood. This Oracle uses magic to manipulate this holy blood to instantly heal any injury that they might sustain. The secret to defeating her, however, is to heal the Deity’s injuries, robbing The Oracle of their crude immortality.",
"A Bugbear with armor covered in worthless jewels he has glued and embedded in his armor, knocking them out can be used as a bargaining chip to pacify him from attacking.",
"A towering, ominous obelisk made of steel is guarded by 3-6 Animated Armors, 3-6 Flying Swords, and 1-3 Helmed Horrors. The obelisk is covered in glowing arcane sigils and scribbles that shine brighter when the player’s step forward to confront it, at which point the assorted defenders move to attack. The obelisk manifests a eye-like sigil which moves around its surface each turn to channel a beam that repairs and reanimates fallen defenders. This beam causes the target to regain 3d8 hit points as the components are magically regrown and imbued once more with magical energy, and is fired one time on each of the obelisk’s turns. Any destroyed constructs hit with the beam come back to life at 0 hit points and regain the amount rolled for the beam, though they cannot take their turn until the following round. To beat the obelisk boss, the invaders may attempt to attack a construct targeted by the eye beam while the ray is being channeled, which causes the amount of damage dealt to it to also go through to the arcane entity within the obelisk. The boss also takes 10 damage every time one of the arcane sigils or a significant part of a particular scribble is erased or damaged in some way, whether the marks are gashed deeply with a blade or blotted out with a destructive spell. The arcane entity within the obelisk has a total of 80 hit points, while the obelisk and the magical markings on it have an AC of 15. Destroying the obelisk entity makes it dissipate into the surrounding area without a trace, causing the arcane markings to go dark and all the constructs to fall apart, thereby ending the boss fight.",
"Some amorphous creature that is under the permanent effect of a mirror image spell that refreshes after all images are dispersed (which could be flavored as overlapping images of the same figure, or many different figures, like nightmares, occupying the same space). The trick is to use area of effect spells, or somehow marking the real creature on a successful hit. For instance, striking the creature with a dagger tied to an immovable rod will pin down the real creature and prevent it from shifting around, rendering the mirror mages useless.",
"A troll from Chult that was infused with firenewt blood that gives it resistance to fire damage. Acid does normal damage but no longer disables it’s regeneration, only necrotic damage will stop it’s regen.",
"Two humanoids (Gladiators, Assassins or Githyanki, for example, depending on the CR you want) whose secret dream is to be an animal. If you polymorph one of them they stop being hostile, and the one you didn’t polymorph will kindly ask you if you can do the same to them. Then they’ll both leave peacefully.",
"A massive Clockwork Golem that needs to wind itself up every so often using the wind-up key on it’s back. If it cannot, it powers down and goes dormant until wound back up again.",
"A magic user fights with his pet wyvern. The man is difficult to hit due to a variety of defensive and knockback spells such as Wind Wall and Gust of Wind, while the wyvern has naturally tough defenses and resistances. However, when one moves (including reactions), the other doesn’t. They also share the same HP pool.",
"A tall thin monk wanders a forest moving with the sounds of nature and attacks with capoeira. He gets +7 to dexterity unless music with no rhythm is being played. Then he gets -7 to dexterity.",
"A tall suit of enchanted armor that roams the countryside, gathering corpses for its necromancer master. It has an obscene amount of health and CON and cannot take damage from an attack that does less than 10 damage. A called attack to the head that does more than 30 damage or a grapple check followed by a DC 15 STR check will remove the armor’s helm from its shoulders, causing it to collapse. An arcana check will reveal that the armor is powered by a small gem on the inside of its forehead. A DC 19 slight of hand can remove the gem.",
"An artificer that uses a set pool of arcane energy (let’s say 100 mana) to power his magical armor and wand. He uses various spells, each of which take away mana. His magical armor prevents damage to himself at the cost of mana. However, he can spend a turn draining mana from other lifeforms (namely players), so the trick with him is to either break his gear directly, disable the magical effect somehow or run him out of mana.",
"A crystal golem vulnerable to thunder damage fights in a cathedral or other temple. Nearby is a large bell or gong. Attacking the gong converts incoming bludgeoning damage to Thunder area damage. Lure the golem into the area, strike the gong – bingo.",
"The Regenerating Water Elemental – A water elemental that heals to full health after each round of combat from the lake in which it resides. Deals AOE damage equal to amount of health regenerated (no other forms of damage output). Must be burst to 0 HP in one turn or somehow disconnected from the lake. (Maybe it’s taunted or charmed into leaving the lake. Maybe the water is frozen or evaporated. Maybe a bubble of air/wind surrounds the elemental.)",
"A singular Flesh Golem that’s body size towers over any medium size creature. The Flesh Golem’s skin has seen a number of brutal battles, and has caused it to become torn which a poor slave has had to stitch up repeatedly after each battle. The Golem often bleeds from the stitches in combat ex-specially when the beast takes fire damage causing the creature to take disadvantage on attack rolls and ability checks until the end of its next turn. The creature often leaves out a loud roar when burned by any source of fire damage. Whenever the Golem’s hit points fall below 50% (207/18D12+90), any fire damage that the Golem is dealt is also half and dealt to the Golem’s creator who is within 90 feet of the battle.",
"A drow beastmaster uses an owlbear to destroy the group. The only problem is that the creature is easily persuaded by food.",
"A goblin boss owns an army of 2D12 clay golems. There is a large crack on the back of each one.",
"A beholder that tries to argue that the group will lose no matter what they do. If a player argues with it enough, it enters a fit of rage. This makes strength rise, but every other stat lower.",
"Strong fighter type character with a great sword that emanates magic power. Turns out that he’s being possessed by the weapon. When disarmed he won’t know where he is or what is going on and surrender immediately. Just make sure that no one else picks up the sword.",
"A cyclops that teleports 15ft back every time it’s hit by an attack. The only way to damage it is by using spells/ bombs that affect both spaces at once, stealth attack it, or coordinate multiple attacks, so there are players waiting to strike as the cyclops teleports. Approximate CR is 7, one more than a normal cyclops, even though it’s stats are the same.",
"A gargoyle with a big scratch on it’s neck. The gargoyle’s skin is tough rock, making it immune to all but psychic damage, unless the damage is applied to the tissue under the scratch. A character can make a CR 13 STR (athletics) check to keep it open the bruise for one turn, which becomes a CR 18 check if the gargoyle is airborne. Another character can step in to help, giving the strongest character advantage in the check. Approximate CR is 5, two more than a normal gargoyle.",
"Blind sorceress uses bird familiar to see. When the bird is blinded, or taken out of commission she will use AOE attacks in an attempt to attack the party. If she has allies, they may be caught in the crossfire. If any of her allies are near her, they can help direct her attacks but she won’t be as accurate."])


print(boss)
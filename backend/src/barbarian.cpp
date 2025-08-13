/* Ben Rohman, benrohman3@gmail.com
 * 
 * Implementations of the barbarian class's member functions. 
 *
 */

#include "user.h"
#include "flow_control.h"

//default constructor
barbarian::barbarian() : delegate()
{
	CONSTRUCT
}

//Returns the name of the character
std::string barbarian::get_name() const
{
	return std::string("Rory");
}

//Adds weapons, armor, and abilities as the character levels up
void barbarian::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
	
		abilities.push_back(new ability("Blood Fury Instinct", 0, nullptr, 0, 2, 
						   abil_target::ENEMY, abil_scaler::STR));
	else if (get_lvl() == 2)
	{
		item * gre = manager::create_armor("Ragecarved Greaves", core(3, 0, 2, 2, 2),
						   ARMORSLOT::ARMS);
		manager::equip(gre, this);
	}
	else if (get_lvl() == 3)
	{
		item * wo = manager::create_weapon("Woundbreaker", core(2, 0, 3, 2, 1), WEAPONSLOT::MELEE, 4, 7);
		manager::equip(wo, this);
	}
	else if (get_lvl() == 4)
		abilities.push_back(new ability("Savage Reprisal", 0, nullptr, 0, 2, abil_target::ENEMY, 
						   abil_scaler::NONE));
	else if (get_lvl() == 5)
	{
		item * he = manager::create_armor("Helm of the Beast", core(1, 0, 3, 3, 1), ARMORSLOT::HELMET);
		manager::equip(he, this);
	}
	else if (get_lvl() == 6)
	{
		item * iron = manager::create_armor("Ironhowl Breastplate", core(1, 0, 1, 4, 3), 
						    ARMORSLOT::CHEST);
		manager::equip(iron, this);
	}
	else if (get_lvl() == 7)
		abilities.push_back(new ability("Abyssroar", 0, nullptr, 0, 4, abil_target::ENEMY,
						   abil_scaler::NONE));
	else if (get_lvl() == 8)
	{
		item * chain = manager::create_armor("Chains of Control", core(3, 4, 0, 2, 1), ARMORSLOT::ARMS);
		manager::equip(chain, this);
	}
}

/*Levels up the character. LEVEL_UP;
void barbarian::level_up() noexcept
{
        LEVEL_UP;
	if (get_lvl() == 2)
                abilities.emplace_back(new ability("Bloodlust", 1u, nullptr, 1u, 2u,
                                       abil_target::ENEMY, abil_scaler::AGI));
}
*/

//Display Rory's preview
void barbarian::intro() const
{

	std::string header = 
		"\nName: Rory \nClass: Barbarian; Berserker \n\n--------- BASE STATS ---------\n "
                "\nHP: " + std::to_string(barbarian::base_hp) +  "\nMP: " +
		std::to_string(barbarian::base_mp) + "\nStrength: " + std::to_string(barbarian::base_str) + 
		"\nIntellect: " + std::to_string(barbarian::base_int) + "\nAgility: " +
		std::to_string(barbarian::base_agi) + "\n--------- Preview --------- \n\n";

	std::string preview = 
		"\tBorn to a a fearsome Barbarian Legacy, Rory was raised for battle but never fit "
		"the mold. Their strength surfaced only through uncontrollable fury, feared by both "
		"enemy and kin. \n\tWhen a strange Arcane wave swept over their homeland, it "
		"shattered minds and left their parents dead by their own hands. Rory blacked out in "
		"a haze of blood and screams... and woke up alone. \n\tBranded a curse, they fled "
		"into exile. But the voices of the dead still follow, fractured, vengeful, whispering "
		"of a growing power. \n\tNow Rory hunts the source of the magic that broke them. "
		+ BOLD + "\n\tThey will find whoever is responsible. \n\tAnd tear them apart with "
		"their bare hands. " + RESET + "\n\n";

	slow_print(header);

	slow_print(preview);
}

//Displays Rory's backstory
void barbarian::disp_backstory() const
{
	std::string backstory =
		"\tRory was born into a nomadic tribe of Barbarians, with a bloodline steeped in violence "
		"and pride. Their mother ruled as chieftain, fierce and wise, while their father stood at "
		"her side as her most trusted war general. \n\tFrom the time they could walk, Rory was "
		"trained in the art of battle. Yet unlike their parents, both skilled warriors in their "
		"own right, Rory showed little natural aptitude for combat. The only time they "
		"overpowered an opponent was during a moment of blind fury as the boy they were sparring "
		"mocked their awkward attempt at wielding an axe. \n\tRory's fury knew neither discipine nor "
		"tradition, only manifesting in sudden terrifying outbursts. Rage would seize them "
		"like a storm, unpredictable and uncontrolled. It made them dangerous and feared. Even by "
		"their own kin. Even by Rory. \n\tOn the eve of Rory's twenty second birthday a wave of "
		"Arcane energy swept over the tribe as they laughed and cheered in celebration. It struck "
		"without sound or light, just a ripple across the world, like the gods exhaling all at "
		"once. Rory felt it before the others. A burning behind their eyes. A twisting of thoughts. "
		"Their pulse surged as their fury broke loose. \n\tTheir red tinged vision began to narrow as "
		"their gaze fell on their parents through the crowd. \n\tRory's father dropped his horn of "
		"mead and began screaming, clawing at invisible enemies. Their mother fell to her knees, "
		"eyes glassy, lips trembling prayers to gods she'd never worshiped. Others convulsed, "
		"whispered names that weren't their own, or slumped to the grown, eyes staring blankly, "
		"unmoving. \n\tRory struggled to the head table where their parents had sat, only to find "
		"they were already dead. Their mother had driven a blade into her chest. Their father's head "
		"open on the obsidian war stone. \n\tAs their vision faded and rage consumed them they "
		"screamed. And others screamed with them. \nRory came to a little ways away from the "
		"encampment after the chaos had settled. When they stumbled back into camp the surviving "
		"warriors stared in silence. \n\tThen one voice rang out: 'What did you do?' \n\tConfused, Rory "
		"looked down at themselves to find their clothes covered in blood. They tried to explain. "
		"They didn't know. But their rage had erupted the moment the magic hit, and now their parents "
		"were dead along with so many others. And Rory had lived. \n\tSome called it a curse. Others "
		"called it treason. All of them looked at Rory with suspicion and fear. \n\tThat night, as the "
		"tribe buried the dead in ash and grief, Rory fled. No trial or farewell. Just the open "
		"wilderness and the sound of voices that wouldn't stop whispering their name. \n\tThey wandered "
		"for days, then weeks, months. Their mind began to fracture, disjointed. One moment they "
		"remembered lifting their father's body, another they remembered laughing as he died. They "
		"began to see visions of their parents, alive but wrong, urging them towards vengeance. "
		"Their whispers grew louder, demanding, calling them to the Wizard City. Telling them that "
		"was where the source of the Arcane energy was. " + ITALIC + "\nIt caused the wave... "
		"\nIt killed us... \n\tSomeone... " + BOLD + "someone made " + RESET + ITALIC + "it happen..."
		+ RESET + "\n\tThey began raiding villages not for plunder, but for chaoe. To make one of the "
		"voices quiet. \n\tThe only thing anchoring them to reality is the vow the voices of their "
		"parents made them repeat nightly: " + ITALIC + BOLD + "\n\tThey will reach the Wizard City. "
		"\n\tThey will find the one responsible. \n\tAnd they will tear them apart with their bare hands. "
		+ RESET + "\n\n";

//	slow_print(backstory, 0);
	slow_print(backstory);

}

//Sets starter weapon/ability
bool barbarian::set_starters() 
{
	item * lab = manager::create_weapon("Labrys", core(3, 0, 1, 1, 1), WEAPONSLOT::MELEE, 2, 5);
	if (!lab)
		return false;
	manager::equip(lab, this);
	return true;
}

//Displays Rory and Ben's dialogue when they join the party/quest
void barbarian::join_party() const
{
	std::string party =
		"\tRory stood alone on the outskirts of the Wizard City, just beyond the border between "
		"wildland and stone. The city buzzed with distant voices and flickering lights, but none "
		"reached them. They sat besides a fireless pit, hands resting on their knees, breath "
		"steady, teeth. Visions and voices, urgent and cruel, had led them here. They'd been "
		"silent that night. Rory didn't know whether to be relieved or terrified. \n\tA twig "
		"snapped behind them. \n\t'You here to die?' Rory growled without turning. \n\t'Uh, no.' "
		"a voice replied quickly. Definitely not. \n\tThey turned their head slightly. A young "
		"man stood several feet back, clearly uncomfortable, bundled in scholar's robes that "
		"didn't quite fit. His fidgeting hands revealed ink stains on his sleeves. \n\t'My "
		"name's Ben,' he said. 'I... was hoping you'd be willing to talk.' \n\t'What gave you "
		"that impression?' Rory asked, slowly rising to their feet. \n\t'Nothing, or no one, I "
		"mean, you were clearly thinking of something important and I just thought-' \n\t'Get to "
		"the point.' Rory snapped. \n\t'Right. I need to get something back, a device, called the "
		"NeuroArchive. It was stolen from the keep and caused that wave that... affected a lot of "
		"people.' Ben stammered. \n\tMention of the magical wave alone sent heat flashing behind "
		"Rory's eyes. \n\t'That " + ITALIC + "wave killed my parents. " + RESET + "\n\tBen flinched. "
		"'I'm sorry,' he said, voice low. 'I made it. I didn't mean for any of this to happen...' "
		"\n\t'Didn't " + ITALIC + "mean" + RESET + "? That thing tore through my tribe like it our "
		"minds, twisted them until they couldn't tell what was real and what wasn't.' \n\t'I know,' "
		"Ben said. 'I think whoever stole it has manipulated it's design, weaponized it. And I think "
		"I can stop it. Maybe even fix whatever it touched, memories, thoughts.' \n\tRory stepped "
		"closer. 'You think?' \n\t'Yes. I wouldn't be here if I didn't believe so.' Ben met their "
		"gaze, visibly shaking, but didn't back dowon. 'I need help getting it back. And if what "
		"you've seen, what you've " + ITALIC + "felt " + RESET + "can help me track it down, then... "
		"I'm asking you to come with me.' \n\tFor a long moment, Rory said nothing. The flames inside "
		"them stirred. Visions flickered at the edges of their mind, their mother's cold eyes, their "
		"father's bloodied face. Both whispering the same thing, over and over: " + ITALIC + "Find "
		"them. Make them pay. " + RESET + "\n\t'If I go with you,' Rory said slowly, 'it's not to "
		"help. It's to kill the asshole that let that thing loose.' \n\t'Fair enough,' Ben said. "
		"'As long as we get it back.' \n\tRory nodded once. 'Then lead the way, little nerd. Let's go "
		"dig up your mistake.'\n\n";

//	slow_print(party, 0);
	slow_print(party);

}

//Displays Rory's good ending
void barbarian::good_ending() const
{

}

//Displays Rory's bad ending
void barbarian::bad_ending() const
{

}

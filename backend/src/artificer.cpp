/* Ben Rohman, benrohman3@gmail.com
 *
 * These are the implementations of the artificer class's member functions. 
 *
 */

#include "user.h"
#include "flow_control.h"

//default constructor

artificer::artificer() : delegate()
{
	CONSTRUCT
}

//returns the character's name
std::string artificer::get_name() const
{
	return std::string("Ben");
}

//levels up the character
void artificer::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
		abilities.push_back(new ability("Mnemonic Extractor", 0, nullptr, 1, 2, 
				       abil_target::ENEMY, abil_scaler::STR));
	else if (get_lvl() == 2)
		abilities.push_back(new ability("Cognitive Overload", 4, nullptr, 2, 2, 
				       abil_target::ENEMY, abil_scaler::AGI));
	else if (get_lvl() == 3)
	{
		item * slip = manager::create_armor("Slipthread Matrix", core(0, 2, 3, 1, 2), 
						    ARMORSLOT::CHEST);
		manager::equip(slip, this);
	}
	else if (get_lvl() == 4)
	{
		item * dag = manager::create_weapon("Quantum Shardknife", core(0, 1, 2, 0, 0), 
						    WEAPONSLOT::MELEE, 5, 9);
		manager::equip(dag, this);
	}
	else if (get_lvl() == 5)
		abilities.push_back(new ability("Etheric Lagfield", 0, nullptr, 1, 4, abil_target::ALLY, 
				        abil_scaler::AGI));
	else if (get_lvl() == 6)
		abilities.push_back(new ability("Mindfracture Grenade", 5, nullptr, 3, 2, 
					abil_target::ENEMY, abil_scaler::NONE));
	else if (get_lvl() == 7)
	{
		item * am = manager::create_armor("Mindglass Amulet", core(0, 2, 1, 1, 1), ARMORSLOT::NECK);
		manager::equip(am, this);
	}
	else if (get_lvl() == 8)
		abilities.push_back(new ability("NeuroCore Implant", 0, nullptr, 7, 10, abil_target::SELF,
				       abil_scaler::INT));
}

//Displays Ben's preview
void artificer::intro() const
{
	std::string header = 
		"\nName: Ben\nClass: Artificer; Archivist \n--------- BASE STATS ---------\n\nHP: " +
		std::to_string(artificer::base_hp) + "\nMP: " + std::to_string(artificer::base_mp) +
		"\nStrength: " + std::to_string(artificer::base_str) + "\nIntellect: " +
		std::to_string(artificer::base_int) + "\nAgility: " + std::to_string(artificer::base_agi) +
		"\n\n--------- Preview ---------\n\n";
	std::string preview = 
		"A prodigy in Arcane Sciences, Ben is a gifted inventor known for his "
                "curiosity, ingenuity, and quiet determination. As a student at the capital's "
                "Academy of Magic, he discovers an ancient magical system and \ndeveloped the "
                "NeuroArchive, a device capable of storing and accessing memories. When a "
                "tragic test of the prototype ends in the death of a close friend, Ben is "
                "chosen to escort the NeuroArchive to the Wizard \nCity for dismantling. "
                "Burdened by guilt and haunted by his creation, Ben begins his journey unaware "
                "that his invention has already changed more than just himself.\n\n";

	slow_print(header);
	slow_print(preview);
}

//Displays Ben's backstory
void artificer::disp_backstory() const
{
	const std::string part1 =
		"\n\nBen's biological parents are unknown. He was found by an Artisan couple "
		"in the woods outside the capital, no indication of who he was or or who left "
		"him. At an unusually young age, he was admitted to the Capital's Academy of "
		"magic, where he was quickly labeled a prodigy in the Arcane Sciences. Ben "
		"possessed a unique fascination with not only the use of magical systems, "
		"but decoding them, finding loopholes, and unraveling their inner logic. It "
		"wasn't long before he figured out how to break into the restricted section of "
		"the library and began conducting his own independent (and illegal) studies. "
		"\nOver the years, Ben became close friends with two classmates: Velian and Hayuma. "
		"Eventually, the Academy, rather than continuously fighting Ben's curiosity, "
		"granted him full access to the library, a privilege he shared with Velian and "
		"Hayuma. By the time he was nearing the end of his studies, Ben had nearly read "
		"the entire archive. \nOne day, deep within the library's forgotten shelves, Ben "
		"discovered a stack of dusty, long forgotten tomes. He selected a particularly "
		"strange looking volume and broke its magical seal with practiced ease. At first "
		"glance, the contents appeared to be outdated spells, but as Ben read more closely "
		"he noticed footnotes, magically encrypted ones. \nDesperate for a new project, "
		"Ben took the tome. His excitement grew as he decoded the notes. They described "
		"an ancient, unused form of magical intelligence: a system for encrypted "
		"compression of magical memory, something unlike anything in modern spell craft. "
		"Ideas flooded his mind and he quickly abandoned the tome, leaving the last few "
		"pages of footnotes unread, and threw himself into designing a prototype. \nIn "
		"the cluttered space he called a workshop (really just a glorified shack), Ben "
		"worked continuously. When Velian and Hayuma found him, he was hunched over a chaotic "
		"assembly of crystal lattices made from etherite, woven with dreamgold filaments. "
		"Nearby sat a circular pane of silver whisperglass and alloys of both starsteel and "
		"obsidian. \nVelian asked about the strange combination of materials in front of Ben, "
		"who went on to explained the tome, the encrypted footnotes, and what he had "
		"uncovered. Ben turned back to the mechanical mess on his desk and laid out his "
		"vision. Velian and Hayuma, both intrigued and impressed, joined him in the completion "
		"of the prototype, which sat before them within a few months later. It had been "
		"named (by Velian) and was finalized with a polished design patent that read: "
		"\nThe NeuroArchive: \n\tDescription: A compact, enchanted device capable of "
		"storing vast amounts of memory. \n\tUses: Long-term knowledge preservation, "
		"espionage prevention, portable eduation. \nWith the NeuroArchive complete, the "
		"trio brought it to the Headmaster for review. The Headmaster studied the boys, "
		"the prototype, the documents, and back again. After a long silence, he declared "
		"device too dangerous to continue. Its potential for misuse was immense. He "
		"apologized before ordering them to surrender all related materials, including the "
		"NeuroArchive, by morning. \nBack at their workshop, the three debated how to "
		"change the Headmaster's mind. Eventually, Velian convinced them to test the device, "
		"to prove its worth beyond question. Hayuma volunteered to be the test subject. ";
	
	const std::string pause = ("\n\n..............................................\n\n");
	
	const std::string part2 =
		"What happened next remains unclear, only that Hayuma suffered some kind of "
		"breakdown. While Velian ran for help, Ben stayed, desperately trying to bring his "
		"friend back to reality. When Velian returned with several professors, it was already "
		"too late. Hayuma took his life in front of them, leaving behind a horrific scene. "
		"\nThe next day, Ben and Velian were summoned to the Headmaster's office. The "
		"NeuroArchive and all related documents were confiscated. The meeting was cold, "
		"bureaucratic with no space for grief. The Headmaster informed them that Hayuma's "
		"death would be announced as a suicide. There would be no mention of the "
		"NeuroArchive. \n'You're going to bury him,' Velian said, his voice bitter. 'Hide "
		"we built. \nWhat YOU built killed him, The Headmaster replied, 'I'm not going '"
		"to lose more students to reckless ambition. \nVelian turned to Ben for support, but "
		"he was staring blankly at the desk. Defeated, Velian slumped in silence. \nThe "
		"Headmaster then issued orders: The NeoroArcvive would be transported to the Wizard "
		"City where it will be disenchanted, dismanteled, and sealed. Ben, having created "
		"its core system, was to ovresee the process. He accepted the punishment without "
		"protest, hoping that it may serve as penance. \nVelian was ordered to remain at "
		"the Academy. \nBen packed in a fog of grief and regret. Leaving Velian deepened "
		"his guilt, but he believed, or assumed, that Velian undertood why he had to go. ";

/*	slow_print(part1, 0);
	slow_print(pause, 0);
	slow_print(part2, 0);
*/	
	slow_print(part1);
	slow_print(pause, 55);
	slow_print(part2);

}

//Sets starter weapon/ability
bool artificer::set_starters() 
{
	item * coil = manager::create_weapon("Runic Coilblade", core(1, 3, 2, 0, 0), WEAPONSLOT::MELEE, 3, 9);
	if (!coil)
		return false;
	manager::equip(coil, this);
	return true;
}

//Displays something about Ben forming the party, maybe big group speech who knows
void artificer::join_party() const
{
	std::string party = 
		"\tAin't written yet... \n\n";
	slow_print(party, 0);
}

//Displays Ben's good ending
void artificer::good_ending() const
{

}

//Displays Ben's bad ending
void artificer::bad_ending() const
{

}

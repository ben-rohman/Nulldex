/* Ben Rohman, benrohman3@gmail.com
 *
 *These are the sorcerer member functions implementations
 *
 */

#include "user.h"
#include "flow_control.h"


//default constructor
sorcerer::sorcerer() : delegate()
{
	CONSTRUCT
}

//returns the name of the character
std::string sorcerer::get_name() const
{
	return std::string("Sky");
}

//levels up the character
void sorcerer::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
	{
		item * man = manager::create_armor("Mantle of Aetherion", core(2, 0, 1, 2, 3), 
						    ARMORSLOT::CHEST);
		manager::equip(man, this);
	}
	else if (get_lvl() == 2)
		abilities.push_back(new ability("Lightborne", 8, nullptr, 3, 4, 
				       abil_target::SELF, abil_scaler::NONE));
	else if (get_lvl() == 3)
	{
		item * heav = manager::create_armor("Heavenglass Bracers", core(1, 0, 0, 1, 4), 
						     ARMORSLOT::ARMS);
		manager::equip(heav, this);
	}
	else if (get_lvl() == 4)
		abilities.push_back(new ability("Skyflare Bolt", 6, nullptr, 3, 3, abil_target::ENEMY,
						   abil_scaler::STR));
	else if (get_lvl() == 5)
		abilities.push_back(new ability("Nimbus Veil", 0, nullptr, 1, 2, abil_target::SELF,
						   abil_scaler::NONE));
	else if (get_lvl() == 6)
		abilities.push_back(new ability("Celestial Echo", 0, nullptr, 4, 5, abil_target::SELF,
						   abil_scaler::NONE));
	else if (get_lvl() == 7)
	{
		item * lan = manager::create_weapon("Dawnlance", core(3, 0, 1, 0, 0), WEAPONSLOT::RANGED, 4, 6);
		manager::equip(lan, this);
	}
	else if (get_lvl() == 8)
		abilities.push_back(new ability("Avatar of Aether", 12, nullptr, 4, 6, abil_target::ENEMY,
						   abil_scaler::AGI));
}

//Displays Sky's preview
void sorcerer::intro() const
{
	std::string header =
		"\n\tName: Sky \n\tClass: Sorcerer; Divine Soul \n\n\t\t--------- BASE STATS ---------\n"
                "\n\tHP: " + std::to_string(sorcerer::base_hp) +  "\n\tMP: " + 
		std::to_string(sorcerer::base_mp) + "\n\tStrength: " + std::to_string(sorcerer::base_str) +
		"\n\tIntellect: " + std::to_string(sorcerer::base_int) + "\n\tAgility: " +
		std::to_string(sorcerer::base_agi) +"\n\n\t\t--------- Preview --------\n\n";

	std::string preview =
		"\tSky was raised in a lively city tavern by her mother and "
		"devoted stepfather, known for her fiery charm and quick wit. "
		"\nBut behind her radiant presence lies a secret, she is the daughter of Aether, "
		"the sky and radiant light, and the subject of a \nprophecy foretelling a battle "
		"against a soul thief who could unmake the world. Taught to keep her divine " 
		"heritage hidden, Sky \nfinds comfort in the familiar rhythms of tavern life, until a "
		"grieving stranger shares a story of death, betrayal, and a magical \ninvention "
		"erased from history. Her bold response sets something in motion she won't " 
		"understand until years later. Sky walks the \nline between warmth and reckoning. "
		"her fate is written in flame.\n\n";

	slow_print(header, 0);
	slow_print(preview, 0);
//	slow_print(header);
//	slow_print(preview);

}

//Displays Sky's backstory
void sorcerer::disp_backstory() const
{
	std::string backstory =
		"\tSky was raised in a lively city tavern by her mother and stepfather. Loved by all, "
		"she had a natural charm that drew people to her. Her stepfather treated her as his own, "
		"and Sky never thought of him as anything but her father. \n\tWhen asked about her "
		"biological father, her mother would simply smile and describe him as distant but kind, "
		"someone who didn't not belong to this world. \n\tOnce Sky reached adulthood, her mother "
		"grew ill. On her deathbed, she finally confessed: \n\t'Your father was Aether, god of "
		"the sky and radiant light. Before you were born, a prophecy was spoken, that his daughter "
		"would would rise to confront a soul thief, a being who could unravel life and death itself. "
		"If she failed, his power would weaken the gods thesmselves, leaving them helpless, and the "
		"world would descend into chaos. The gods became angry at Aether, blaming him for the threat "
		"they now faced, and forced him to return to the Heavens.' \n\tHer mother ended the story "
		"with a warning: some would fear her if they knew the truth. She made Sky to guard her "
		"secret carefully, sharing it only when absolutely necessary. \n\tYears passed. One night, "
		"a quiet stranger sat at the abr. He spoke of a dead friend, a buried magical experiment, "
		"and betrayal by someone he trusted. \n\t'If that's true,' Sky said, 'then the truth should "
		"come out, before something worse is created.' \n\tThe man studied her for a long moment, "
		"then paid her for his drinks and left. \n\tWeeks later, when the encounter with the man "
		"long forgotten and his face an empty, soulless void in her memory, a sudden wave of strange "
		"magic sweapt across the land. It rippled through the city, warpint memories, twisting minds, "
		"and shattering realities. \n\tSky felt the change immediately as a burning mark, glowing with "
		"radiant light appeared on her skin in the middle of the busy tavern. \n\tWord spread quickly. "
		"Whispers reached the nearby clergies, and soon they came, hunter her as both a threat and a "
		"key to the unfolding chaos. \n\tHer mother's final words rang in her ears, of Aether, the "
		"prophecy, and the soulless thief threatening the balance of life and death. \n\tSky fled "
		"her home, enemies at her door, and into the night. Carrying nothing but the weight of her "
		"divine heritage, she snuck onto a vehicle bound for the Wizard City. Following the whispers "
		"of the source of magical energy had originated there and filled with an uncertain hope that "
		"confronting her destiny might save the world... or doom it.\n\n";

	slow_print(backstory, 0);
//	slow_print(backstory);
}

//Sets starater abilities/weapons
bool sorcerer::set_starters() 
{
	abilities.push_back(new ability("Radiant Pulse", 6, nullptr, 1, 0, abil_target::ENEMY, 
					   abil_scaler::STR));
	return true;
}

//Displays Sky and Ben's dialogue when she agrees to join the party/quest
void sorcerer::join_party() const
{
	std::string party =
		"\nSky kept her cloak pulled low, shadows from the brim hiding her golden eyes. The back "
		"alley café on the city's edge was barely more than a hole in the wall, quiet, private, "
		"and blessedly devoid of cloaked inquisitors or whispering pilgrims. \nShe stirred her tea "
		"absently, gaze flickering to the doorway at every creak. After about an hour her nervous "
		"glancing fell on a figure standing in the doorway. Panic rose in her throat as escape "
		"routes raced through her head. \nUntil the door swung shut behind the figure, revealing not "
		"one of the faithful nor a hunter but an awkward-looking young man with a journal too big "
		"for one pocket and a nervous, crooked smile. \nHe slid into the seat across from her "
		"without asking. \nSky's fingers tightened around her cup. 'You know people don't usually "
		"invite themselves to sit down without asking.' \n'Right. Sorry,' the man said quickly, "
		"adjusting the journal as if it were a shielf. 'I'm Ben.' Sky stared at him blankly in "
		"response. \n'I heard about what happened, what they're saying about you. The murderous "
		"Sorceress made of fire. Seeing as I'm not on fire right now, seems to be bullshit. "
		"Although your hair color is a bit unusual.' \nSky's stare somehow became more empty, "
		"'You know the murderous Sorceress part is true. Daughter of a god, burned a man's soul "
		"out that commented on my hair color.' Ben shifted in his seat nervously as Sky sipped her "
		"tea, her hollow eyes still fixed on him. '\nWell, I was kind of hoping that part was true. "
		"There's something happening to people, they're losing their memories or have unfamiliar "
		"ones. Some have gone catatonic and others have died.' \nSky's unnerving stare finally broke "
		"as she tilted her head at him. 'And what the fuck does that have to do with me? You want me "
		"to purify it with divine fire?' She mocked. '\nHe almost laughed. 'Honestly? I'm not even "
		"really sure what I'm asking. Just trying to get a group together that might be able to help "
		"stop what's coming. Maybe fix a few things in the process.' \nSky studied him more carefully "
		"now. There was a stubborn undertone in his weary voice. His hands were ink stained and unable "
		"to sit still. His eyes were sharp despite the dark circles under them. \n'You don't know me,' "
		"Sky said slowly. 'You dont know what I might do if something ancient and ugly tries to crawl "
		"into my head.' \nBen smiled slightly. 'That makes two of us.' \n'Sky leaned back and let out "
		"a dry chuckle. 'You're lucky I'm bored and have nowhere else to go.' \n'Ben's smile widened. "
		"'I'll take it.'\n\n";

	slow_print(party, 0);
//	slow_print(party);
}

//Displays Sky's good ending
void sorcerer::good_ending() const
{

}

//Displays Sky's bad ending
void sorcerer::bad_ending() const
{

}

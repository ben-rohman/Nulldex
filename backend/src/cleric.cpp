/* Ben Rohman, benrohman3@gmail.com
 * 
 * These are all of the cleric class's member function implementations. 
 */

#include "user.h"
#include "flow_control.h"

//default constructor
cleric::cleric() : delegate()
{
	CONSTRUCT
}

//returns the name of the character
std::string cleric::get_name() const
{
	return std::string("Annie");
}

//levels up the character
void cleric::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
	{
		item * aeg = manager::create_armor("Moonlit Aegis", core(0, 1, 1, 1, 3), ARMORSLOT::CHEST);
		manager::equip(aeg, this);
	}
	else if (get_lvl() == 2)
		abilities.push_back(new ability("Sleepfire", 3, nullptr,  2, 1, abil_target::ENEMY, 
				       abil_scaler::NONE));
	else if (get_lvl() == 3)
		abilities.push_back(new ability("Breksta's Lullaby", 8, nullptr, 3, 6, abil_target::ALLY,
						   abil_scaler::NONE));
	else if (get_lvl() == 4)
	{
		item * mace = manager::create_weapon("Moonwake Mace", core(2, 0, 1, 0, 0), WEAPONSLOT::MELEE,
						     2, 4);
		manager::equip(mace, this);
	}
	else if (get_lvl() == 5)
		abilities.push_back(new ability("Moonveil", 0, nullptr, 2, 3, abil_target::ENEMY, 
						   abil_scaler::STR));
	else if (get_lvl() == 6)
		abilities.push_back(new ability("Dreamcarver", 4, nullptr, 2, 2, abil_target::ENEMY,
						   abil_scaler::AGI));
	else if (get_lvl() == 7)
	{
		item * tal = manager::create_armor("Twilight Talisman", core(0, 2, 2, 0, 1), ARMORSLOT::NECK);
		manager::equip(tal, this);
	}
	else if (get_lvl() == 8)
		abilities.push_back(new ability("Omen of Dreamfall", 3, nullptr, 4, 6, abil_target::ENEMY,
						   abil_scaler::AGI));
}

//Displays Annie's preview
void cleric::intro() const
{
	std::string header = 
		"\nName: Annie \nClass: Cleric; Twilight Domain \n\n--------- BASE STATS "
                "-------- \n\nHP: " + std::to_string(cleric::base_hp) + "\nMP: " +
		std::to_string(cleric::base_mp) + "\nStrength: " + std::to_string(cleric::base_str) +
		"\nIntellect: " + std::to_string(cleric::base_int) + "\nAgility: " +
		std::to_string(cleric::base_agi) + "\n\n-------- Preview --------\n\n";
	
	std::string preview = 
		"Once a gentle farm girl with an unusual affinity for death, Annie found "
		"herself drawn by unseen forces to a city church devoted to the Twilight "
		"gods. There, her lifelong compassion for the suffering and \ndying "
		"transformed into a divine calling. As a Cleric of Hestia, Ilmater, Hermes, "
		"and Morpheus, Sister Annie now guides lost souls to rest and comfort those "
		"burdened by grief. \nBut Annie's path is far from peaceful. After years of "
		"service, news of souls trapped inside a magical invention reach the doors "
		"of her church. Annie's faith is tested as she confronts forces beyond even "
		"\ndivine understanding, a growing sense that something, or someone, has "
		"slipped through the veil between life and death... and is still watching.\n\n";

	slow_print(header);
	slow_print(preview);
		
}

//Display Annie's backstory
void cleric::disp_backstory() const
{
	std::string backstory = 
		"\tAnnie was raised in a quiet farming village, where her fascination with death made "
		"her an outsider. While other children played, she lingered in the twilight, tending "
		"to sick animals and listening to the stillness between heartbeats. \n\tAs she grew, "
		"Annie began to have dreams of people she'd never met, lost souls calling out, "
		"surrounded by shadown. Her dreams reminded her how thin the veil between worlds could "
		"be. \n\tDuring a visit to the city, Annie followed a whispering voice down empty "
		"alleys to a forgotten chapel. There a priestess welcomed her into the Church of "
		"Twilight, devoted to Breksta, goddess of dreams and dusk. The moment Annie stepped "
		"inside, the air shifted. It was quiet, not empty, but full of a presence. The same "
		"one she'd felt in her dreams. \n\tWhen the priestess spoke of their calling, to "
		"guide souls and guard the passage between life and death, Annie felt something in "
		"her settle. As if she'd been searching for this place all her life. She heard a "
		"familiar voice whisper 'Welcome home.' \n\tYears passed. Annie studied rites of "
		"comfort and rest, grew into a healer and protector, found Breksta's power flowing "
		"through her: light in her hands, names in her dreams, and visions that blurred the "
		"lines between the living and the lost. \n\tOne afternoon, a stranger arrived, quiet "
		"and grieving. He spoke of a magical object that had taken his friend's life, trapping "
		"his soul inside. Annie offered comfort and guidance, but before she could explain how "
		"to free his soul, the man, reassured that his friend was not lost forever, left. "
		"\n\tLater, Annie realized she couldn't recall his face. His voice was gone from memory. "
		"Only static remained in place of his head. \n\tAnnie began having dreams of metal room "
		"blanketed in fog with a crystal lattice at it's center. Voices of people Annie could "
		"never reach called from the shadows, begging for help. Then, one night, a figure "
		"cloaked in starlight appeared on the other side of the crystal. Annie questioned "
		"the figure, who were they? What were they doing there? The figure simply pointed. "
		"Through the lattice, Annie saw eight strangers standing before the Wizard City. "
		"\n\tThen came a whisper: " + ITALIC + "Go. Find them. " + RESET + "\n\tAnnie awoke, "
		"her heart certain that someone was disturbing the natural order of life and death. "
		"And the gods were calling her to stop it.\n\n";

	slow_print(backstory, 0);
}

//Sets starter ability/weapon
bool cleric::set_starters() 
{
	abilities.push_back(new ability("Dreampierce", 4, nullptr, 1, 0, abil_target::ENEMY, 
					   abil_scaler::NONE));
	return true;
}

//Displays Annie and Ben's dialogue when she joins the party/quest
void cleric::join_party() const
{
	std::string party =
		"\nAnnie wasn't hiding. Not really. She was just... sitting in a collapsed belltower, "
		"legs swinging out into the empty air, watching the sunset try to outshine the glow of "
		"the Wizard City's enchantments. The light was prettier out here anyway, wild rather "
		"than controlled. \nShe heard someone approaching, quiet, careful footsteps that implied "
		"whoever it was wasn't fond of heights. \n'You know,' she said, 'I can tell when "
		"someone's watching me. Kind of feels like... pressure. Behind the eyes. Or maybe the "
		"ears?' \nThe stranger cleared his throat. 'Sorry. I didn't mean to startle you.' \nYou "
		"didn't,' she said brightly. 'You just hesitated too long. People do that when they "
		"think the other is going to be weird.' \nAn awkward pause hung in the air. \n'... And "
		"are you? Going to be weird I mean?' he asked. \n'Oh, absolutely,' Annie grinned, finally "
		"twisting around to see him. 'You're the Artificer boy, right?' \n'Yeah, Ben,' he said. "
		"'Wait, how did you know?' \nAnnie shrugged, 'I'm a Cleric. My patron deity is Breksta, "
		"the goddess of twilight and dreams. Naturally, mine tend to be a bit strange... but I "
		"get to meet a lot of new people.' She paused to study Ben for a moment, noting the "
		"dark circles under his eyes. \n'You looked less tired in my dream. Rough night?' "
		"\n'Yeah, something like that,' he hesitated. 'There's something coming, or... unraveling. "
		"The NeuroArchive, a magical item I designed, was stolen last night. It was the source of "
		"the wave of magical energy and is affecting people. Memores are bleeding, changing. Some "
		"are losing their memories, others have ones that aren't theirs. In the worst cases "
		"people fall into a catatonic state or are driven to insanity and kill themselves.' "
		"\nAnnie blinked. 'Oh... Is it going to affect more people?' \n'It already has.' "
		"\nAnnie turned back to face the city again. 'I've been dreaming more often than usual "
		"lately. They're almost all the same. I'm standing in a foggy metal room with this weird "
		"lattice of crystal in the middle. I can hear people in the fog, crying, calling for "
		"help, but I never find them. The night before I left my chapel I saw someone in the "
		"dream. A silhouette. I asked them who they were, what was going on.' \nShe looked back "
		"at Ben, her lips curving into a smile. \n'They didn't answer. Just pointed at the "
		"crystal. And when I looked, I saw 8 poeple in front of the Wizard City gates. One of "
		"them was you.' Her grin widened. 'Whoever it was told me: 'Go. Find them.' \nBen stared, "
		"silent for a moment. 'Well. I guess I should be flattered I made the cut.' \n'I don't "
		"know if it's a cut exactly,' Annie said. 'I think it's more like... fate. Or "
		"propability. Or...' \n'A cosmic dream scavenger hunt?' \n'Exactly!' she laughed. "
		"\nBen exhaled as his faint smile faded. 'I have to get the NeuroArchive back. Try and "
		"fix the damage it's caused before it can't be reversed. You seem to know more than "
		"most, maybe you could help me find the others?' \n'I mean, that's flattering,' she said, "
		"swinging her legs once more. 'Also mildly terrifying.' \n'You in?' \n'Annie stared out "
		"at the fading skyline one last time. 'I'll come with you.' She stood, brushing dust from "
		"her robes and hopping lightly down from the ledge. 'I mean, no offense, but you seem "
		"like a disaster,' she said cheerfully. 'But I like helping people, keeping them safe. "
		"especially in the dark. That's what I do.' She offered her hand, 'I'm Annie, by the "
		"way.' \nBen shook her hand, 'Nice to meet you, Annie, ready for an adventure?' "
		"\n'Always.'";

	slow_print(party, 0); 
}

//Displays Annie's good ending
void cleric::good_ending() const
{

}

//Displays Annie's bad ending
void cleric::bad_ending() const
{

}

/* Ben Rohman, benrohman3@gmail.com
 *
 * These are the member functions of the wizard class
 */

#include "user.h"
#include "flow_control.h"

//default constructor
wizard::wizard() : delegate() 
{
	CONSTRUCT
}

//returns the name of the character
std::string wizard::get_name() const
{
	return std::string("Aurora");
}

//levels up the character
void wizard::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
		abilities.push_back(new ability("Ether Lance", 5, nullptr, 2, 1, abil_target::ENEMY,
						   abil_scaler::STR));
	else if (get_lvl() == 2)
	{
		item * mir = manager::create_weapon("Mirror Blade", core(1, 2, 1, 0, 0), WEAPONSLOT::MELEE,
						    2, 6);
		manager::equip(mir, this);
	}
	else if (get_lvl() == 3)
		abilities.push_back(new ability("Mirrorskin", 0, nullptr, 3, 5, abil_target::SELF,
						   abil_scaler::INT));
	else if (get_lvl() == 4)
		abilities.push_back(new ability("Warp Anchor", 0, nullptr, 3, 2, abil_target::ENEMY,
						   abil_scaler::AGI));
	else if (get_lvl() == 5)
	{
		item * cloak = manager::create_armor("Cloak of Splintered Space", core(2, 0, 2, 4, 3),
						     ARMORSLOT::CHEST);
		manager::equip(cloak, this);
	}
	else if (get_lvl() == 6)
		abilities.push_back(new ability("Temporal Echo", 0, nullptr, 3, 5, abil_target::ENEMY,
						   abil_scaler::INT));
	else if (get_lvl() == 7)
		abilities.push_back(new ability("Arcane Vow", 0, nullptr, 4, 9, abil_target::SELF,
						   abil_scaler::STR));
	else if (get_lvl() == 8)
	{
		item * sov = manager::create_armor("Crown of the Conjurer Sovereign", core(6, 6, 6, 6, 6),
						   ARMORSLOT::HELMET);
		manager::equip(sov, this);
	}
}
//Displays Aurora's preview
void wizard::intro() const
{
	std::string header = 
		"\n\tName: Aurora \n\tClass: Wizard; Evocation \n\n\t\t--------- BASE STATS --------- \n"
                "\n\tHP: " + std::to_string(wizard::base_hp) + "\n\tMP: " + 
		std::to_string(wizard::base_mp) + "\n\tStrength: " + std::to_string(wizard::base_str) +
		"\n\tIntellect: " + std::to_string(wizard::base_int) + "\n\tAgility: " +
		std::to_string(wizard::base_agi) + "\n\n\t\t--------- Preview ---------\n\n";
	
	std::string preview = 
		"\tA former street thief turned reluctant Wizard, Aurora was once known only for her sharp "
		"mind and quicker fingers. \nRaised alongside her close friend, Gray, the two "
		"beame infamous as a clever and efficient criminal duo, one powered by psionic "
		"\ntalents, the other by sheer determination. But everything changed the night they "
		"accepted a dangerous job to steal a magical \nartifact from the heart of the Wizard "
		"City. In the depths of the keep, something ancient and hidden is redirected to "
		"Aurora, \nthe result of a magical force momentarily binding her to a terrified "
		"Wizard Guard. What was supposed to be a simple heist \nturned into a nightmare of "
		"betrayal, death, and Arcane forces tearing their world apart. Aurora barely "
		"escapes with her life, \nand something else entirely. Now marked with the remnants "
		"of her bounds and changed by a mysterious power she never sought, \nAurora grapples "
		"with the memory that reshaped her life. The magic that surged through her was sudden "
		"and terrifying, hers now, \nwhether she liked it or not. She never asked for this power, "
		"but she'll use it if it means protecting her friend.\n\n";
	
	slow_print(header, 0);
	slow_print(preview, 0);
//	slow_print(header);
//	slow_print(preview);

}
		  
//Displays Aurora's backstory
void wizard::disp_backstory() const
{
	std::string backstory =
		"\tAurora left her hometown young, accompanied by her closest friend, Gray. She had no "
		"magic gifts, only sharp instincts and loyalty. Together, they became skilled thieves, "
		"eventually hired for high risk jobs by wealthy clients. As they grew older, Aurora "
		"recognized Gray's gifts as " + ITALIC + "unusual " + RESET + "despite their friends "
		"insistence that they were nothing more than instincts. \n\tOne night, a cloaked man "
		"approached them with a single offer: break into the Wizard City's keep and retrieve "
		"a magical artifact. The pay was larger than they'd ever been offered but the risk, "
		"greater. Gray hesitated, unable to read him like they usually could. That alone should "
		"have been reason enough to refuse. But the reward was too high. They took the job. "
		"\n\tEverything went smoothly at first, until they reached the artifact: a plain looking "
		"metal box etched with runes. The moment Gray touched it, Aurora saw their body tense. "
		"Before she could react, she felt a massive hand close around her wrist. \n\tShe struggled "
		"against the guard's grip when it suddenly became white hot as threads of glowing light "
		"surged from his arm into hers. After a few moments the light faded and the guard's hand "
		"dropped her wrist. She raised her arm and stared, mesmerized by the faint lines still "
		"etched in her skin, her trance only breaking at the sound of the guard's sudden screams. "
		"The two fled, followed by the abrupt end to the terrified shrieks after a loud crash. "
		"\n\tThey met their employer in the woods beyond the city. When they refused to give the "
		"box to the man, fearing it's power, he summoned shadowy figures to take it by force. "
		"\n\tAurora watched as the man took the box from Gray who began to cry out in confusion. "
		"Her panic erupted into something unfamiliar, ancient. When Gray fell silent, Aurora "
		"screamed into the Earth. " + ITALIC + "\n\tThe Earth responded. " + RESET + "\n\tCreatures "
		"of bark and stone rose from the forest, forcing the man to retreat. Aurora collapsed, "
		"drained. The conjured beasts crumbled to dust. \n\tShe woke beside Gray and stared at the "
		"scattered remains of what she'd summoned. The lines on her arm barely visible. The "
		"artifact had changed her and she couldn't stop thinking about it. A small voice in the "
		"back of her head wondered: " + ITALIC + "if the object were destroyed, would her powers "
		"vanish with it? " + RESET + "\n\tShe was determined to find the man who hired them, "
		"to help Gray break the artifact's hold... and maybe protect the magic that was finally "
		"hers.\n\n";

	slow_print(backstory, 0);
//	slow_print(backstory);

}

//Sets the starter abilities/weapons
bool wizard::set_starters() 
{
	abilities.push_back(new ability("Earthen Uprising", 4, nullptr, 1, 0, abil_target::ENEMY, 
			       abil_scaler::STR));
	return true;
}

//Displays Aurora and Ben's dialogue when she joins the party/quest
void wizard::join_party() const
{
	std::string party =
		"\nAurora walked along the Wizard City's eastern promenade, enjoying the sharp, clean "
		"wind that cut through the spires like a blade. It reminded her of nights running across "
		"tiled rooftops, breathless and laughing, Gray's voice teasing from behind her. She snapped "
		"a small twig from a nearby bush and twirled it between her fingers. It bent and splintered "
		"into 3 wooden birds suspended midair. \n'Sorry to bother you,' an awkward voice said. 'Are "
		"you Aurora?' \nThe tiny birds fell to the ground as she turned slightly. A young man "
		"stood a few paces away. He wore the uniform of the Arcane scientists that worked within "
		"the city's keep, though his looked as if it had been slept in. His wringing hands revealed "
		"blotchy ink stains on the cuffs of his sleeves. \n'Depends on who's asking.' Aurora said, "
		"an undertone of suspicion in her light voice. \n'I'm Ben, I work, well " + ITALIC + "used "
		"to work " + RESET + "at the keep. It was robbed recently, by a pair of well-known thieves, "
		"from what I've heard.' He said. \nAurora felt her stomach drop as he spoke. 'First I've "
		"heard of it.' She replied, managing to hold his gaze evenly and voice calm. \n'That makes "
		"sense, the Wizard Officials wanted to keep it quiet. The two suspects, though, are pretty "
		"famous. One is well-known for their psychic abilities while the other for being an excellent "
		"spy as well as thief.' \n'Huh, they sound cool.' Aurora's voice grew nervous. \nBen "
		"continued,'They're believed to be the only ones with a chance of breaking in let alone "
		"manage to escape.' Ben paused, studying Aurora's expression. 'Another rumor claims that "
		"something happened to them while inside the keep. The one with psychic abilities went "
		"insane and now hears constant voices in their head and can see the voices' memories. The "
		"other formed a connection to the Arcane somehow. That they can now conjure creatures made "
		"of Earth, stone, and even trees.' Ben's gaze dropped to the 3 wooden birds that lay at "
		"Aurora's feet then back to meet hers. \n'Shit,' she thought, her stomach now a nauseous "
		"mess. 'What do you care what happened? It's not like you work there anymore.' Aurora managed "
		"to say out loud. \n'I designed the device, the NeuroArchive, that was stolen.' \n'You're "
		"the one that made something that can affect people like that? The one that drove a man to "
		"kill himself after it was used on him? What kind of-' Aurora broke off, realizing Ben "
		"hadn't mentioned the death of the Wizard Guard earlier. Their wide, terrified eyes met "
		"his, heavy with remorse and grief, not the smugness they had expected. \n'It was supposed "
		"to record copies of knowledge, of memories. For long-term memory preservation and portable "
		"education. It wasn't ever meant to hurt anyone.' Ben said quietly. \n'Intention doesn't "
		"matter anymore, does it?' Aurora snorted. 'You're little metal box left a " + ITALIC + 
		"parasite " + RESET + "in Gray. Voices that constantly compete to be the loudest. Visions "
		"of other people's lives they can't shut off. They say it's getting better, but I see what "
		"it's doing to them.' \n'I'm sorry. It wasn't supposed to be able to do anything like that.' "
		"\n'Too late for that. God, we never should have taken that job.' Aurora slumped over a "
		"railing with her head in her hands. \n'I'm going to get it back and stop it from affecting "
		"anyone else.' Ben hesitated. 'If I can get it back, I think I could fix the damage it's "
		"done to people. To Gray. I want to make it right' \nAurora's head raised, 'If you get it "
		"back, you'll be able to reverse it's affects? All of them?' \n'Yeah, I think so.' \n'Then "
		"I'm coming.' Aurora said without hesitation. \nBen blinked. 'You are?' \n'If there's even "
		"a chance that I can help Gray, cut whatever tie they have to that stupid thing, I'm in.' "
		"\n'Thank you.' Ben exhaled, sounding as if he'd been holding his breath. \n'Thank me "
		"after we get your NeuroArchive back. Now come on, we've got a scavenger hunt to go on.'\n\n";
	
	slow_print(party, 0);
//	slow_print(party);
}

//Displays Aurora's good ending
void wizard::good_ending() const
{

}

//Displays Aurora's bad ending
void wizard::bad_ending() const
{

}

/* Ben Rohman, benrohman3@gmail.com
 *
 * man idek
 */

#include "user.h"
#include "flow_control.h"

//default constructor
rogue::rogue() : delegate()
{
	CONSTRUCT
}

//returns the name of the character
std::string rogue::get_name() const
{
	return std::string("Gray");
}

//levels up the character
void rogue::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
	{
		item * shroud = manager::create_armor("Shroud of Splintered Minds", core(0, 0, 3, 2, 2),
						      ARMORSLOT::HELMET);
		manager::equip(shroud, this);
	}
	else if (get_lvl() == 2)
		abilities.push_back(new ability("Reverberate", 4, nullptr, 2, 4, abil_target::ENEMY,
						   abil_scaler::NONE));
	else if (get_lvl() == 3)
		abilities.push_back(new ability("Neurostatic", 0, nullptr, 1, 3, abil_target::ENEMY,
						   abil_scaler::NONE));
	else if (get_lvl() == 4)
	{
		item * soul = manager::create_weapon("Soul Blades", core(3, 1, 3, 2, 1), WEAPONSLOT::MELEE,
						     3, 10);
		manager::equip(soul, this);
	}
	else if (get_lvl() == 5)
		abilities.push_back(new ability("Shrimp", 6, nullptr, 3, 4, abil_target::ENEMY, 
						   abil_scaler::AGI));
	else if (get_lvl() == 6)
	{
		item * skin = manager::create_armor("Secondskin", core(6, 0, 2, 8, 8), ARMORSLOT::CHEST);
		manager::equip(skin, this);
	}
	else if (get_lvl() == 7)
		abilities.push_back(new ability("Rend Mind", 8, nullptr, 4, 6, abil_target::ENEMY,
						   abil_scaler::STR));
	else if (get_lvl() == 8)
		abilities.push_back(new ability("Wailing Crown", 12, nullptr, 5, 6, abil_target::ENEMY,
						   abil_scaler::NONE));
}

//displays Gray's preview
void rogue::intro() const
{
	std::string header = 
		"\nName: Gray \nClass: Rogue; Soulknife \n\n--------- BASE STATS --------\n "
                "\nHP: " + std::to_string(rogue::base_hp) + "\nMP: " + std::to_string(rogue::base_mp) +
		"\nStrength: " + std::to_string(rogue::base_str) + "\nIntellect: " + 
		std::to_string(rogue::base_int) + "\nAgility: " + std::to_string(rogue::base_agi) + 
		"\n\n--------- Preview ---------\n\n";
	
	std::string preview =
		"An enigma with a past steeped in shadow, Gray is more than a talented thief. With "
		"a sharp instinct they always dismissed as a 'gut feeling', Gray has spent a lifetime "
		"unknowingly wielding supernatural \nforesight. Gray and their childhood best friend, "
		"Aurora, become an infamous duo in the criminal underworld, no longer stealing just "
		"for survival, but for the thrill of the challenge. \nBut everything changed the night "
		"they touched a strange, rune-etched box deep in the Wizard City's keep. Something "
		"ancient and overwhelming was awakened within Gray. Now burdened with fragmented "
		"memories and \nvoices that didn't belong to them, Gray has no choice but to unravel the "
		"truth of the box and power that cultivated in side them. Gray didn't ask to become "
		"become a vessel for forgotten magic, but might be \nthe only one who can survive it.\n\n";

	slow_print(header);
	slow_print(preview);

}

//displays Gray's backstory
void rogue::disp_backstory() const
{
	std::string backstory = 
		"\tGray left their small hometown young, accompanied by their closest friend, Aurora. "
		"Even as a child, Gray sensed things before they happened, instincts they never quite "
		"understood. \n\tOver time, the two became expert thieves, working their way from "
		"street cons to high paying contracts. By adulthood, Gray's instincts had sharpened "
		"into something more, glimpses of possible futures and the faint thoughts of others. "
		"They refused to call it magic. Merely intuition. \n\tOne day, a cloaked man approached "
		"them with a job: steal a magical item from the Wizard City's keep. The vault was one of "
		"the most heavily protected in the kingdom, but the reward was too great to ignore. The "
		"man offered blueprints, guard rotations, everything they'd need. The only strange thing "
		"was, Gray couldn't read him. At all in fact. His thoughts hidden behind static. \n\tOn "
		"the night of the heist, Gray and Aurora slipped past the keep's defenses and found the "
		"artifact: a small, metal box with runes carved into it's shell. The moment Gray touched "
		"it, it latched onto their mind. Gray felt as it read their thoughts, memories, as it " +
		ITALIC + "understood them. " + RESET + "\n\tA guard burst into the room and grabbed hold "
		"of Aurora's wrist. The box reacted before Gray, pulsing in their hand like a heartbeat. "
		"The guard bellowed as glowing threads of light unraveled beneath his sleeve and traveled "
		"from his hand to Aurora's wrist, binding them. Moments later he staggered, dazed, before "
		"turning his attention to Gray. He muttered a spell and when nothing happened he tried "
		"again to no avail. His confused expression turned angry as he began advancing towards "
		"Gray. \n\tGray's hand holding the box raised between them as if controlled by it and "
		"felt it vibrate again, stronger this time. The guard, screamed before he collapsed, his "
		"mind unraveling. \n\tThe two fled, the echoing screams coming to an abrupt end after a "
		"loud crash. \n\tIn the woods outside the city, they met the man who'd hired them. "
		"\n\t'What the fuck is this?' Gray demanded, 'It made a guard go crazy and now he's "
		"fucking dead!' \n\tThe man's face clouded and Gray instinctively searched his thoughts. "
		"A single image flooded their mind: a younger version of the man next to a smiling boy "
		"and a third nearby, his head surrounded by angry red static. \n\tThe small box was "
		"ripped from their hands after the two had refused to give it to the man. The second "
		"it left their grasp, the voices began. Unfamiliar memories, foregin thoughts, voices, "
		"screaming inside their mind. Gray cried out in confusion as pressure built behind their "
		"eyes before their consciousness slipped away. \n\tGray woke at dawn next to Aurora, who "
		"seemed... " + ITALIC + "different " + RESET + "the keep. The voices in their head had "
		"quieted to a dull murmur. \n\tThey found that they couldn't remember their former "
		"employer's face, a cloud of gray static obscuring his features. \n\tEver since, the "
		"artifact's presence has lingered in their head, hundreds of lives whispering all at "
		"once. \n\tGray became determined to find the man and the box, whatever it was. That "
		"destroying it would severe whatever tie now bonded them to it and end the voices that "
		"haunted their thoughts.\n\n";

	slow_print(backstory, 0);
}

//Sets starter abilities/weapons
bool rogue::set_starters() 
{
	item * psy = manager::create_weapon("Psychic Blades", core(2, 1, 2, 1, 0), WEAPONSLOT::MELEE, 4, 6);
	if (!psy)
		return false;
	manager::equip(psy, this);
	return true;
}

//Displays Gray and Ben's dialogue when they agree to join party/quest
void rogue::join_party() const
{
	std::string party =
		"\nGray sat alone at quiet table in a low lit tavern on the outskirts of the Wizard City. "
		"Their eyes flicking toward the door every few moments. Slow footsteps began to approach "
		"An unfamiliar and awkward looking young man slid into the seat across from Gray, "
		"He spoke quietly, 'You've been watching the door like you expect someone worse than me. "
		"Am I interupting a stakeout?' \nGray raised an eyebrow, unimpressed. 'Depends. Are you "
		"here to looking to hire a thief, or to stab me and take my boots?' \n'Not today,' Ben "
		"replied dryly. 'My name's Ben by the way. I work, or worked, at the keep until recently.' "
		"\n'Uh huh,' Gray mumbled, not paying attention. \n'I heard about a pair of thieves who "
		"broke into the Wizard City keep and came out a bit... different. One of them has been known "
		"to terrorize the fine folk of this pub. You I assume.' \n'Quite the theory,' Gray said, "
		"leaning forward slightly, voice low. \n'Yeah, not my strangest though.' Ben smiled faintly. "
		"He paused for a moment before asking 'You don't remember who hired you, do you?' \nGray "
		"visibly tensed. 'What do you know about that?' \nBen's eyes fell down to his wringing hands "
		"resting on the table. 'I know the artifact you stole was something you should never have "
		"touched. Not your fault.' He paused, then added quietly, 'I designed it.' \nGray's eyes "
		"narrowed. 'That box? The one that stuffed my head with all these fuck ass people and made "
		"a guy commit suicide, screaming?' \n'The NeuroArchive. I built it to preserve memory... "
		"portable, more accessible education... His voice sounded wistful as he trailed off for a "
		"heartbeat before continuing, 'It wasn't meant to destroy minds. But I was naive maybe a "
		"little blind. But I want to fix it. That's why I'm here. I need your help getting it back' "
		"\nGray cackled. 'You want me to go within 1000 leagues of the cookie tin that renovated my "
		"brain into a half way house and rented a room to some guy that cannot fucking sing whose "
		"stuck on a nonstop loop of Life is a Highway? So you can what, study it? Finish what you "
		"started?' \nBen's tone grew serious. I want to make sure no one else suffers like you did. "
		"Like... Hayuma did.' \nGray stiffened at the name, the memory echoing faintly. \nBen "
		"continued, 'There's something wrong with the device, it's doing things we didn't "
		"understand. Memories bleeding, shifting. It's... spreading. I don't need you for your "
		"thieving. I need someone who's already survived it.' \nAfter a long silence, Gray finally "
		"said, 'And what makes you think I'd help you?' \nBen met Gray's gaze. 'I just thought you'd "
		"want answers, maybe a cure, as much as I do. And I have hunch that if we make it through, "
		"you'll never have to hear Life is a Highway ever again. \nGray studied Ben with a strange "
		"sense of déjá vu when they were unable to get anything of use, his thoughts looked strange, "
		"warped, as if under water. They took a long breath and leaned back. 'One job. That's all I'm "
		"agreeing to. If I don't like what I find, I'm gone.' \n'Fair,' Ben said. 'Let's go on a "
		"quest. It'll be a long road but life's like a road that you travel on if you think about it. "
		"Sometimes you bend, sometimes you stand-' \n'Ben I'm going to fucking murder you if you "
		"don't shut the fuck up.'\n\n";

	slow_print(party, 0);
}

//Displays Gray's good ending
void rogue::good_ending() const
{

}

//Displays Gray's bad ending
void rogue::bad_ending() const
{

}

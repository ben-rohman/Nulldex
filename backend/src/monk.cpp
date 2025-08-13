/* Ben Rohman, benrohman3@gmail.com
 *
 * These are the implementations of the monk class's member functions. 
 *
 */

#include "user.h"
#include "flow_control.h"

//default constructor
monk::monk() : delegate()
{
	CONSTRUCT
}

//returns the name of the character
std::string monk::get_name() const
{
	return std::string("Ivy");
}

//levels up the character
void monk::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
		abilities.push_back(new ability("Still Palm", 0, nullptr, 0, 2, abil_target::ENEMY,
						   abil_scaler::AGI));
	else if (get_lvl() == 2)
	{
		item * san = manager::create_armor("Windstep Sandals", core(0, 1, 2, 1, 1), ARMORSLOT::BOOTS);
		manager::equip(san, this);
	}
	else if (get_lvl() == 3)
		abilities.push_back(new ability("Internal Tide", 0, nullptr, 1, 4, abil_target::SELF,
						   abil_scaler::NONE));
	else if (get_lvl() == 4)
	{
		item * br = manager::create_armor("Four Order Bracers", core(3, 1, 2, 1, 2), ARMORSLOT::ARMS);
		manager::equip(br, this);
	}
	else if (get_lvl() == 5)
		abilities.push_back(new ability("Elemental Stances", 0, nullptr, 3, 6, abil_target::SELF,
						   abil_scaler::AGI));
	else if (get_lvl() == 6)
	{
		item * ves = manager::create_armor("Vest of Stillness", core(0, 2, 3, 1, 1), ARMORSLOT::CHEST);
		manager::equip(ves, this);
	}
	else if (get_lvl() == 7)
		abilities.push_back(new ability("Conduit's Grasp", 0, nullptr, 6, 9, abil_target::ENEMY,
						   abil_scaler::NONE));
	else if (get_lvl() == 8)
		abilities.push_back(new ability("Formless Harmony", 0, nullptr, 5, 12, abil_target::SELF,
						   abil_scaler::NONE));
}

//Displays Ivy's preview
void monk::intro() const
{
	std::string header =
		"\nName: Ivy \nClass: Monk; Way of the Open Hand \n\n--------- BASE STATS ---------\n" 
                "\nHP: " + std::to_string(monk::base_hp) +  "\nMP: " + std::to_string(monk::base_mp) +
		"\nStrength: " + std::to_string(monk::base_str) + "\nIntellect: " +
		std::to_string(monk::base_int) + "\nAgility: " + std::to_string(monk::base_agi) +
                "\n\n--------- Preview ---------\n";
	std::string preview =
		"Once destined to be a formidable warrior, Ivy's path took an unexpected turn from "
		"combat to compassion. Raised in the quiet mmountains by a devoted order of Monks, "
		"her childhood was marked by extraordinary \nmartial prowess, but it was "
		"a trip to a nearby village and a burned boy's hand that changed everything. "
		"\nNow a Way of the Open Hand Monk, Ivy balances precision with empathy, "
		"trained not just to fight but to heal. Her bond with the villagers, especially "
		"Tyler, grew stronger over the years, and when tragedy \nstruck, Ivy led he charge "
		"to rescue the innocent and reclaim what was lost. \nBut in the ruins of the "
		"battle torn town, cryptic messages and a strange shift in the world's spiritual "
		"energy suggest a deeper threat, one Ivy may be uniquely attuned to sense... and "
		"perhaps destined to \nconfront.\n\n";

	slow_print(header);
	slow_print(preview);

}

//Displays Ivy's backstory		VERSION WHERE SHE IS THE DnD AVATAR
void monk::disp_backstory() const
{
	std::string backstory = 
		"\tIvy was raised in a secluded monastery high in the wind carveved mountains. There, "
		"the Order of the Four Aspects trained disciples of Ki, though each sect followed a "
		"different path. The Ember monks sought strength through fire and passion. The Tides "
		"embraced change and healing. Stone prized discipline and tradition, while the Winds "
		"walked a path of solitude and intuition. Though Ivy was born to the Stone sect, she "
		"often wandered between temples, listening, watching, learning. \n\tShe was quick, "
		"precise, a natural in combat. But when it came to channeling Ki, she struggled. "
		"Meditation left her restless. Focus slipped through her fingers like water. Her "
		"teachers insisted she focus on martial prowess and the path of the Kensei. But Ivy "
		"wasn't drawn to mastery of weapon but to people. To helping. \n\tShe joined a relief "
		"mission of the lowlands after a flood, where monks from multiple sects cooperated to "
		"rebuild homes and treat injuries. Among the wreckage and ruin, Ivy found a purpose "
		"that no kata or mantra had ever given her. While she mended broken beams and soothed "
		"frightened children, a different energy stirred quietly. \n\tLater, Ivy and a small "
		"group of monks were sent to protect a village near the mountain's base from raiders. "
		"They drove off the attackers but found only a handful of survivors. One was a boy, "
		"around Ivy's age, silent and wounded. Ivy sat beside him, day after day, telling "
		"stories, offering food, tending his wounds. He remained silent until one night, he "
		"was gone. Ivy would later have no memory of what the boy had looked like, only "
		"a cloud of gray static that hid his features. \n\tA few weeks after the mysterious "
		"boy had vanished, everything changed. \n\tA wave of Arcane energy swept through the "
		"region like a storm with no wind. The monks and villagers's memories fractured. Some "
		"began speaking in voices that weren't theirs or forgetting their own names, others "
		"screamed in terror as they clutched their heads before committing suicide or fell into "
		"a catatonic state. Tyler, the baker's son who Ivy had grown close to, stared through "
		"her as if she were a stranger before walking into the forest without a word. The monks "
		"panicked and the Ki faltered, the flow twisted. \n\tIvy stood still in the chaos and "
		"felt everything, flame, water, stone, and air, all at once. For the first time in her "
		"life, Ki surged through her. She called out and the ground trembled, the air around "
		"her shimmered. \n\tEmissaries from the Four Aspects sought her out, brining news "
		"of similar disruptions across the land that all traced back to a single source: a "
		"magical disturbance radiating from the Wizard City. The messanger from Ember demanded "
		"she join them to strike back at whatever caused the imbalance. Stone insisted the "
		"Order remain neutral and preserve its ways. Tides urged her to stay and heal. Winds "
		"offered no guidance, only quiet eyes and listening ears. \n\tIvy heard them all. " +
		ITALIC + "And chose none. " + RESET + "\n\tShe left the mountains behind. If the balance "
		"had been broken, then " + ITALIC + "someone had to restore it. " + RESET + "Ivy would "
		"walk all paths, the gentle, the fierce, the fluid, still, until the world was made "
		"whole again.\n\n";

//	slow_print(backstory, 0);
	slow_print(backstory);
}

//Sets starter ability/weapon
bool monk::set_starters()
{
	abilities.push_back(new ability("Balanced Strike", 3, nullptr, 0, 1, abil_target::ENEMY,
					   abil_scaler::NONE));
	return true;
}

//Displays Ivy and Ben's dialogue when she joins the party/quest
void monk::join_party() const
{
	std::string party =
		"\nIvy sat cross legged beneath the sloping arch of a ruined dome, half swallowed by moss "
		"and moonlight. The veins of energy running through the Wizard City had gone quiet, "
		"peaceful. She was already aware of him before he spoke. His approach was careful, "
		"respectful in the way people are when they don't know whether you're meditating or just "
		"trying not to fall apart. She turned before he could greet her, surprising him. 'You're "
		"Ben, right?' she asked brightly. \nThe boy blinked. 'Yeah, how did you-?' \n'You've got "
		"that 'haven't slept in 3 days, hyper active brain' look,' she said with a warm smile. "
		"'Also, people gossip about you around the City. Artificer boy, the one who made the "
		"dangerous magical device that was stolen from the keep. That the device caused the 'memory "
		"plague' as they like to call it.' \nBen shifted sheepishly as his expression grew "
		"confused, 'Is that what they call me?' \n'Don't worry. I think it's kind of cool. Though "
		"I'd vote for something a little catchier next time.' She stood, brushing dirt and moss "
		"from her clothes, and added, 'I'm Ivy.' \n'I know.' Ben hesitated. 'I've been trying to "
		"find you. I saw what you in the medical center when that crowd of people were panicking. "
		"You didn't use any magic, but you... calmed them. Just by talking.' \nIvy grinned proudly, "
		"Just some breathing with a little Ki manipulation. Nothing too fancy.' \n'It was more "
		"than that.' He stepped closer, voice lowering. 'You calmed them, eased their worries. Too "
		"many minds have come undone lately. What you did... was incredible.' \nIvy tilted her "
		"head, studying him. He seemed sincere, even if he seemed like he carried the weight of "
		"collapsing realities on his shoulders. There was something almost fragile in him. Not "
		"weak. Just... careful. Ivy smiled again, this time gentler. 'You seem scared.' \nHe "
		"blinked. 'Is it that obvious?' \n'Only a little.' \nHe let out a breath, part exhale, "
		"part laugh. 'There's something wrong with the NeuroArchive, the device I designed. The "
		"system it's built on was supposed to record knowledge, copies of memories. Not rewrite "
		"them or people.' \nIvy's smile faded a little, though not completely. 'I've felt it too. "
		"The Ki's rhythm is off here. Like there's a song playing underneath the world, but "
		"someone's changed the key.' \nBen nodded slowly, 'Exactly. And I think... I think "
		"someone's manipulated it's design. Turned it into a cage for the mind. I have to get it "
		"back before they can fully weaponize it. But I need help. From people who can help ease "
		"panic. People like you.' \nIvy looked up at the sky through the shattered dome. The stars "
		"above the Wizard City were faint tonight, but steady, watchful. 'Well,' she said softly, "
		"'I believe the Ki guided me here to help people. And here you are asking for mine. Who "
		"am I to refuse? I'd be honored to help.' \nShe offered him her hand, not glowing nor "
		"enchanted. Just a hand. 'Let's go, we have an adventure to start.'\n\n";

//	slow_print(party, 0);
	slow_print(party);
}

//Displays Ivy's good ending
void monk::good_ending() const
{

}

//Displays Ivy's bad ending
void monk::bad_ending() const
{

}

/*Displays Ivy's backstory		VERSION WHERE SHE ISN'T THE DnD AVATAR
void monk::disp_backstory() const
{
	std::string backstory =
		"Deep within the secluded mountains lived a quiet community of monks, an order "
		"Ivy came to know as her family. She began her martial arts training younger than "
		"most and swiftly mastered techniques by the age of twelve that had taken others "
		"decades to perfect. The monks believed she was destined to become a fierce Kensei Monk, "
		"given her natural prowess in combat. \nIn addition to her martial arts lessons, Ivy "
		"studied Ki manipulation and meditation. Yet, unlike her fluid grasp of martial arts, "
		"she found these disciplines exceptionally challenging. Just as she was on the verge "
		"of abandoning them altogether, a healing Master led a group of young monks into a "
		"nearby village to assist with treating wounds and illnesses. \nWitnessing the suffering "
		"caused by violence, which she had spent her life training for, shook Ivy deeply. Her "
		"desire to become a Kensei began to fade, replaced by a growing interest in medicine which "
		"surpassed even her passion for martial arts. \nAs time passed, Ivy's fighting style began "
		"to shift. Her once aggressive approached evolved into something more balanced, controlled, "
		"and deliberate. She struck only when necessary, her hands just as capable of healing as "
		"they were of harm. Her continued volunteer trips with the Healing Monks into the "
		"village, long after her duties required it, led her to follow the Way of the Open Hand. "
		"\nOn one such trip, Ivy, still not yet an adult, treated the baker's son, Tyler, for a "
		"burn on his hand. The two quickly became friends. Ivy would visit him whenever possible, "
		"sometimes sneaking away from the monastery under the guise of meditation. \nYears later, "
		"what began as an ordinary day took a dark turn. A young girl, her clothes stained with "
		"blood, stumbled into the monastery. She told of a raid on the village, many killed, "
		"the rest imprisoned, before collapsing from exhaustion. With some convincing, Ivy was "
		"granted permission to lead a small group of Monks down the mountain to help. \nThey "
		"discovered the prisoners held inside a crumbling barn. To Ivy's relief, Tyler was among "
		"them. Quietly, they led the villagers to safety, hiding in the trees at the base of "
		"the mountain to rest and tend to the wounded. \nAfter a few days, Ivy led the Monks and "
		"surviving townsfolk in a counterattack. They successfully drove the raiders from the "
		"ruins of the town. Yet victory came at a cost. The battle had further devastated the "
		"village, nearly every building left fractured and unstable. \nAs Ivy and Tyler walked "
		"through the wreckage, they came across two shattered walls bearing strange messages. One "
		"read, 'MEMORY IS A WEAPON'. The other: 'NULLDEX = MEMORY - MERCY'. \nAs Ivy read the "
		"scrawled words, she felt something shift in the cosmic balance. A thread of corruption "
		"twisted through the flow of spiritual energy. She turned to Tyler, her eyes wide, heart "
		"pounding, and full of fear, for something far worse was coming.\n\n";

	slow_print(backstory);

}
*/

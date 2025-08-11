/* Ben Rohmam, benrohman3@gmail.com
 * 
 * These are the implementations of the paladin class's member functions
 */

#include "user.h"
#include "flow_control.h"

//default constructor
paladin::paladin() : delegate()
{
	CONSTRUCT		//god i love macros <3
}

//returns the name of the character
std::string paladin::get_name() const
{
	return std::string("Tavish");
}

//levels up the character
void paladin::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
	{
		item * aegis = manager::create_armor("Thornwoven Aegis", core(1, 0, 0, 3, 3), ARMORSLOT::CHEST);
		manager::equip(aegis, this);
	}
	else if (get_lvl() == 2)
		abilities.push_back(new ability("Sylvan Light", 0, nullptr, 1, 3, abil_target::SELF,
						   abil_scaler::STR));
	else if (get_lvl() == 3)
		abilities.push_back(new ability("Earthen Vow", 0, nullptr, 1, 4, abil_target::SELF,
						   abil_scaler::AGI));
	else if (get_lvl() == 4)
		abilities.push_back(new ability("Smite of Renewal", 6, nullptr, 3, 1, abil_target::SELF,
						   abil_scaler::NONE));
	else if (get_lvl() == 5)
	{
		item * band = manager::create_armor("Grovewarden's Band", core(2, 0, 1, 3, 2), 
						    ARMORSLOT::RING1);
		manager::equip(band, this);
	}
	else if (get_lvl() == 6)
		abilities.push_back(new ability("Sunbind", 12, nullptr, 2, 3, abil_target::ENEMY, 
						   abil_scaler::NONE));
	else if (get_lvl() == 7)
	{
		item * exalted = manager::create_weapon("Exalted Crowned Longsword", core(6, 2, 5, 5, 3),
							WEAPONSLOT::MELEE, 6, 12);
		manager::equip(exalted, this);
	}
	else if (get_lvl() == 8)
	{
		item * crown = manager::create_armor("Crown of the Last Light", core(5, 3, 3, 2, 4),
						     ARMORSLOT::HELMET);
		manager::equip(crown, this);
	}
}

//Paced output of Tavish's preview
void paladin::intro() const
{
	std::string header = 
		"\nName: Tavish\nClass: Paladin; Oath of the Ancients\n\n--------- BASE STATS --------- \n"
		"\nHP: " + std::to_string(paladin::base_hp) + "\nMP: " + std::to_string(paladin::base_mp) +
		"\nStrength: " + std::to_string(paladin::base_str) + "\nIntellect: " + 
		std::to_string(paladin::base_int) + "\nAgility: " + std::to_string(paladin::base_agi) +
		"\n\n--------- Preview --------- \n\n";

	std::string preview = 
		  "Tavish never chased glory. While his father boasted endlessly of a long-lost "
		  "Paladin ancestor and divine blessings in their bloodline, Tavish sought peace, "
		  "not prestige. Raised among whispering woods and \nplayful forest sprites, he felt "
		  "more at home in the trees than in tales of war. But when violence crept too "
		  "close and the village he loved was forced to flee, Tavish was torn from the "
		  "only friends who truly \nunderstood him. \n"
		  "Haunted by loss ad bound by love, Tavish now walk a different path, one not forged "
		  "by steel or politics, but by reverence for life and light. Tavish answered a call "
		  "deep in an ancient forest to accept a \nsacred Oath: not to a king, but to nature "
		  "itself. Now clad in armor woven with leaves and bearing a sword crowned with antlers, "
		  "Tavish is a Paladin of the Ancients, sworn not to conquer, but to protect. His \npromise "
		  "to the sprites is unbroken, his heart rooted in devotion, and his strength "
		  "drawn from the beauty he vows to preserve.\n\n";

	slow_print(header);
	slow_print(preview);

}

//Paced output of Tavish's backstory
void paladin::disp_backstory() const
{
	std::string backstory = 
		"\tTavish grew up in a quiet village, the son of farmers. His father often rambled "
		"about their Paladin ancestry, a long dead warrior whose blood supposedly granted "
		"them divine protection. Tavish payed no mind to his father's stories. \n\tHe "
		"preferred the woods to family legends, spending his days with forest sprites who "
		"lived among the tress. When a nearby conflict crept towarard the village, soldiers "
		"came seeking volunteers, his father was the first to enlist. Tavish refused his "
		"father's attempts to convince him to join, spouting promises of glory and divine "
		"favor. He never returned. \n\tWhen the fighting grew closer, Tavish fled with his "
		"family. Before leaving, he begged the sprites to let him stay and protect them. "
		"\n\tThey smiled sadly and said, 'Replant the trees, and we will return. \n\tIn the "
		"city near the capital his family settled, Tavish grew homesick. One day, as he "
		"wandered the nearby forest, he found a man sitting by a stream, crying over a "
		"journal. The man, who introduced himself as Velian, said he'd lost his friends, "
		"one to betrayal, one to death and his memory falsified. Tavish offered comfort, "
		"telling him of his own lost friends and the memory he kept alive until he could "
		"be one day reuined with them. \n\t'You must keep his memory alive,' Tavish told "
		"him. 'That's how we honor those we lost. And if his story is rewritten, then as "
		"his friend, it's your duty to tell it truthfully,  " + ITALIC + "to make them "
		"remember.'" + RESET + "\n\tAfter Velian thanked him and left, Tavish heard a voice "
		"call to him deeper into the woods. There, in a clearing beneath an ancient tree, a "
		"circle of dryads stood waiting. They spoke not with words, but through wind and "
		"rustling leaves. " + ITALIC + "\n\t'We heard of your promise to the sprites and the "
		"love you feel for them. We know your sorrow. The forest listens.'" + RESET + "\n\tThey "
		"offered him an Oath, not to a kingdom, but to the natural world itself. Tavish "
		"accepted without hesitation. \n\tThe bark of the ancient tree, shifted and groaned, "
		"the face of Silvanus, the Forest Father, appeared within it. Tavish knelt before him "
		"and swore his oath: " + ITALIC + "\n\tI swear upon root and river, leaf and light: "
		"\n\tThat I shall guard the green and shield the gentle. \n\tWhere life grows, I will "
		"nurture it. \n\tWhere hope fades, I will kindle it. \n\tWhere the old magics slumber, "
		"I will remember. \n\tThis I vow, before the Ancient One and all those who walk beneath "
		"the canopy of stars.' " + RESET + "\n\tThe dryands placed a sword in his hands, its hilt "
		"crowned with antlers. He left the clearing reborn, not a knight of men, but a warden "
		"of life. \n\tBut peace would not last. After a wave of Arcane energy washed over the "
		"land, the forests began to fracture. The nymphs and dryads' minds twisted, their joy "
		"turned to fury. \n\tTavish was once more called before Silvanus, the forest quiet, the "
		"leaves turned dull. The bark of the tree creaked, 'Go. Find the source. Before it's too "
		"late.' Silvanus' voice groaned.  \n\tTavish left the forest behind with only his sword, "
		"determined to uphold his sacred oath.\n\n";

	slow_print(backstory, 0);

}

//Sets starter abilities/weapons
bool paladin::set_starters()
{
	item * sword = manager::create_weapon("Crowned Longsword", core(2, 0, 3, 2, 1), WEAPONSLOT::MELEE, 
					      4, 7);
	if (!sword)
		return false;
	manager::equip(sword, this);
	return true;
}

//Displays Tav and Ben's dialogue when he joins the party/quest
void paladin::join_party() const
{
	std::string party =
		"\nTavish sat among the trees in the Wizard City's Arboretum, enjoying the quiet that the "
		"early morning offered. It wasn't a real forest, too controlled, too curated, but it was "
		"the closest thing within the city. His freshly polished sword lay next to him, the scent "
		"of oil and cedar clinging to it's leather hilt. The cloak draped across his shoulders was "
		"still damp with the morning dew. \nApproaching footsteps cut through the silence, 'Too "
		"careful for a student, too steady for a wanderer.' Tavish thought without looking up and "
		"instead kept running his thumb along the smooth grain of his scabbard. \n'I heard you've "
		"been talking to the trees,' said the owner of the footsteps. \nTavish looked up at the "
		"boy, young man, really, standing a few paces away. His clothes were rumpled, as if they'd "
		"been slept in, the restlessness of his hands revealed ink stains on the cuffs of his "
		"sleeves. \nTavish's lips twitched. 'They're pretty chatty actually if you stop and "
		"listen.' \nThe other man looked at Tavish with an amused and curious expression. 'I'll "
		"have to come back another morning to try and hear them.' \nAn awkward silence settled "
		"between them. 'You can sit, if you're not here to assassinate me or anything.' Tavish "
		"nodded toward the ground beside him, finally breaking the uncomfortable atmosphere. "
		"\nHe laughed softly as he sat. 'I think if I were here to assassinate you, I'd have "
		"already embarrassed myself. \n'Probably,' Tavish agreed. 'My name's Tavish by the way, "
		"were you looking for something?' \n'Oh, right, my name's Ben. And yeah I was.' he shifted, "
		"clearly unsure of how to begin. 'I need help recovering something that was stolen, a "
		"magical device I designed called the NeuroArchive. The system it's built on was supposed "
		"to record knowlege, copies of memories for long-term memory preservation, portable "
		"education. But... I think that whoever stole it has exploited it's design and is using it "
		"to steal memories from people and others have unfamiliar ones forced into their minds. "
		"I have to get it back before they figure out how to fully weaponize it.' \nTavish "
		"listened. He'd heard confessions before, some uglier or louder, but there was a weight "
		"in this one. The heaviness of guilt you couldn't fake. \n'The forests have been affected "
		"too. The trees remember things they shouldn't, their roots have become tangled knots and "
		"long forgotten arguments are being rehashed among the dryads. They don't sleep anymore, "
		"just grow increasingly restless and angry. Silvanus is uneasy, unsure of what will happen "
		"if their condition worsens.' \nBen's head turned sharply, 'It shouldn't be able to affect "
		"anything nonhuman.' \n'And yet it did.' \nBen's eyes dropped to the ground at Tavish's "
		"response. 'I'm trying to fix it.' He said quietly. \nTavish looked at Ben curiously. "
		"'Why come to me?' \n'You know and see things I don't.' Ben said. 'My expertise is in "
		"Arcane Science, I know all about artificial sentientience but clueless about natural "
		"life. " + ITALIC + "Real " + RESET + "living things.' \nTavish looked up at the "
		"manufactured sunlight that casted slow shadows across neatly trimmed branches. 'You want "
		"to heal something,' Tavish said. 'But you're not sure if it's alive.' Ben nodded. \nTavish "
		"grabbed his sword and stood. 'I don't know if what you made can be undone,' he said. 'But "
		"if the NeuroArchive is rotting then we have to cut the decay out, down it's roots.' "
		"\nBen looked up at him with hopeful eyes. 'You'll come?' \nTavish extended his hand and "
		"pulled Ben to his feet. 'I always liked gardening with my mother. How different could "
		"ridding a magical object of corruption be from carving rot from a pumpkin?'\n\n";

	slow_print(party, 0);
}

//Displays Tav's good ending
void paladin::good_ending() const
{

}

//Displays Tav's bad ending
void paladin::bad_ending() const
{

}

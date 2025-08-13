/* Ben Rohman, benrohman3@gmail.com
 *
 * These are the implementations of the bard class's member functions. 
 *
 */

#include "user.h"
#include "flow_control.h"

//default constructor
bard::bard() : delegate()
{
	CONSTRUCT
}

//returns the name of the character
std::string bard::get_name() const
{
	return std::string("Maeve");
}

//levels up the character
void bard::level_up() noexcept
{
	LEVEL_UP;
	if (get_lvl() == 1)
	{
		item * clo = manager::create_armor("Storykeeper Cloak", core(0, 3, 3, 1, 1),
						   ARMORSLOT::CHEST);
		manager::equip(clo, this);
	}
	else if (get_lvl() == 2)
	{
		abilities.push_back(new ability("Dirge of Truth", 0, nullptr, 3, 4, 
				       abil_target::ALLY, abil_scaler::STR));
	}
	else if (get_lvl() == 3)
		abilities.push_back(new ability("Cutting Whisper", 0, nullptr, 2, 2, abil_target::ENEMY,
						   abil_scaler::AGI));
	else if (get_lvl() == 4)
	{
		item * bl = manager::create_weapon("Whispersharp Blade", core(2, 1, 1, 0, 0), 
						  WEAPONSLOT::MELEE, 3, 5);
		manager::equip(bl, this);
	}
	else if (get_lvl() == 5)
		abilities.push_back(new ability("Liar's Pyre", 8, nullptr, 3, 5, abil_target::ENEMY, 
						   abil_scaler::INT));
	else if (get_lvl() == 6)
		abilities.push_back(new ability("Chorus of Undoing", 0, nullptr, 3, 4, abil_target::SELF,
						   abil_scaler::NONE));
	else if (get_lvl() == 7)
	{
		item * quill = manager::create_weapon("Mythcarver's Quill", core(0, 2, 2, 0, 0), 
						      WEAPONSLOT::MELEE, 2, 7);
		manager::equip(quill, this);
	}
	else if (get_lvl() == 8)
		abilities.push_back(new ability("Silvertongue's Execution", 15, nullptr, 5, 10, 
				       abil_target::ENEMY, abil_scaler::NONE));
}

//Displays Maeve's Preview
void bard::intro() const
{
	
	std::string header = 
		"\nName: Maeve \nClass: Bard; College of Lore \n\n--------- BASE STATS --------- \n"
                "\nHP: " + std::to_string(bard::base_hp) + "\nMP: " + std::to_string(bard::base_mp) +
		"\nStrength: " + std::to_string(bard::base_str) + "\nIntellect: " +
		std::to_string(bard::base_int) +  "\nAgility: " + std::to_string(bard::base_agi) + 
		"\n--------- Preview --------- \n\n";
	
	std::string preview =		  
		"Once a wide-eyed student of legends, Maeve grew up enamored with the tales of noble "
		"heroes and glorious Monarchs passed down by her grandparents and the Bards of her city. "
		"Her passion for stories led her \nto the prestigious Bard's College, where she "
		"specialized in Lore and devoted herself to uncovering forgotten histories. But "
		"when her curiosity pulled her into the forbidden corners of the library, Maeve\n"
		"discovers a secret that shatters everything she believed. \nA long surpressed "
		"account of treachery, war, and rewritten history revealed the the beloved tale "
		"of her childhood to be a carefully orchestrated lie, one buried by fear, magic, "
		"and the stroke of a Bard's pen.\nWhen Maeve tried to bring the truth to light, "
		"she was cast out for treason and forced to leave her city behind. \nNow in "
		"exile, Maeve carries not only a haunted truth but also a burning question: if "
		"the stories we live by are lies, what else must be rewritten? \nDriven by a "
		"stubborn heart and fierce love of truth, Maeve seeks to reclaim the narrative, "
		"no matter the cost.\n\n";

	slow_print(header);
	slow_print(preview);

}

//Displays Maeve's backstroy
void bard::disp_backstory() const
{
	std::string backstory = 
		"\tMaeve grew up with a love for stories, especially the old legends passed down by her "
		"grandparents. Her favorite was a tale of a noble Monarch defeating a rebel in glorious "
		"single combat, earning the gods' blessing for their bloodline as great leaders. The tale "
		"was treated as gospel among the citizens of the Bard City, earning the Monarchy their "
		"unwavering devotion. \n\tShe followed that passion to the Bard's College, where she "
		"naturally chose Lore as her advanced technique. She spent most of her time buried in "
		"forgotten epics and ancient histories. One day, behind a locked gate in the library's "
		"restricted section, Maeve found a forbidden volume that shattered everything she believed. "
		"\n\tThe book told a different version of the familiar story of the Monarch and rebel. It "
		"claimed that the Monarch and the rebel, named Etro, were childhood friends and close as "
		"brothers. That Etro had become the Monarch's right hand until the latter betrayed the "
		"the former, severing their bond. Rather than admit fault, the Monarch's pride allowed "
		"a devestating battle to ensue. The bloody conflict was condemned by the people as "
		"senseless. Etro and his forces had nearly won the battle when the Monarch challenged "
		"him to a public duel, desperate to reclaim favor. However, he had been a far less skilled "
		"swordsman than Etro, nearly lost the fight when the Prince violated the sacred rule of "
		"single combat and killed Etro. Fearing further disgrace, the Monarch ordered his court "
		"Wizard to erase the memory of those who had witnessed the battle and a new version of "
		"events that painted him in better light to be written by the court Bard. \n\tAt the end of "
		"the book was a note from the author: " + ITALIC + "\n\t'I will likely be killed for "
		"writing the truth in these pages. But I beg any reader who's eyes may find this book: "
		"spead the truth. Do not let them bury the past. A loss of memory, of truth, is worse than "
		"death. If they control the story, they control everything. \n\t\t-- Lioren Varn, Bard of "
		"Lore; Apprentice to Lord Bard Seren Merek of Eloquence to the Monarch' " + RESET +  
		"\n\tMaeve brought the book to the College's Dean, expecting praise. Instead, she was branded "
		"a traitor and banished from the city. She fled only with her lute and one stolen page, the "
		"author's note. \n\tWeeks later, in a smoky tavern far from home, Maeve drunkenly recounted "
		"her story to a kind stranger, even showing him her stolen page. \n\tHe read it slowly, then "
		"said, 'They're right. Being forgotten is worse than death. No one, especially those in "
		"positions of power, should be allowed to suit themselves.' \n\tMaeve toasted the sentiment, "
		"slurred something poetic, and stumbled off to bed. \n\tIn the morning Maeve discovered the "
		"note to be missing. Her memory of the previous night was hazy. The nameless stranger's "
		"face nothing more than a blur of gray static. \n\tSince then, she's heard whispers, of "
		"memory magic gone wrong, of history reshaping itself, of a relic called the NeuroArchive. "
		"\n\tMaeve doesn't know what's true anymore. " + ITALIC + "But she's going to find out. " + 
		RESET + "\n\n";

//	slow_print(backstory, 0);
	slow_print(backstory);

}

//Sets starter ability/weapon
bool bard::set_starters() 
{
	abilities.push_back(new ability("Opening Act", 3, nullptr, 1, 0, abil_target::ENEMY, 
					   abil_scaler::NONE));
	return true;
}

//Displays Maeve and Ben's dialogue when she joins the party/quest
void bard::join_party() const
{
	std::string party = 
		"\nMaeve had been humming to herself, soft, aimless notes that didn't belong to any song in "
		"particular. She sat beneath the trees just outside the walls of the Wizard City. The lute "
		"she had aquired on her journey to the City lay across her knees, more companion than an "
		"instrument at the moment. She let her fingers dance along its strings without purpose. The "
		"melody was barely audible, but even the air seemed to pause to listen. \nThe sound of "
		"careful footsteps approaching caught here ear. \n'If you're here to arrest me,' she said "
		"without looking up, 'you're a little late. And I'd prefer a much more dramatic entrance, "
		"maybe with drums and a herald or two.' \n'I'm not here for that,' a voice replied, young, "
		"tentative. 'Though I admit, I was looking for you.' \nShe glanced up, eyebrows arched. "
		"'Oh? I didn't know my infamy was so popular.' \nThe boy, young man, really, stood at the "
		"edge of the clearing. He looked more scholar than soldier, in worn boots and ink stained "
		"cuffs. There was a hesitant look in his eyes. Guilt rather than fear. 'My name's Ben,' "
		"he said. 'We met once.' \n'Doubtful,' Maeve said. 'I tend to remember people who look like "
		"they've crawled out of a philosophy thesis and into a storm drain. But do go on.' \nBen "
		"scratched the back of his neck. 'It was years ago. You'd traveled to the capital and were "
		"performing outside the Academy gates. You sang a ballad about an ancient Monarch and a "
		"rebellion.' \nThat got her attention. Maeve leaned forward slightly, her lazy playfulness "
		"retreating just a bit. 'Hard to believe you remembered that, I barely do.' \n'The story "
		"wasn't particularly memorable, I'll admit. But your voice, the way you mesmerized the "
		"crowd.' \n'Good. That dumb story is the gospel of my hometown. But it isn't true.' Maeve "
		"replied bitterly. 'An old tale written by lying cowards to make a shitty, dead Monarch "
		"who wiped the memories of thousands of people to make himself look better.' \n'Rewritten "
		"history and false truth. Sounds familiar.' Ben said. \nMaeve's tone dropped an octave. "
		"'Spoken like a man who belongs in their archives. Rewriting history a special talent of "
		"yours?' She looked at him through narrowed eyes. \nBen didn't flinch as she had expected. "
		"'No. I'm trying to stop that from continuing to happen.' \nMaeve snorted. 'Good. For a "
		"moment I was worried you were just another fanboy of royal family whose rich daddy pays "
		"his overdue library fines.' \nBen smiled faintly. 'Not even remotely. I'm trying to find "
		"people to help me get something back. The magical object that's been causing people to "
		"lose or gain unfamiliar memories. People who still remember what was " + ITALIC + "real. "
		+ RESET + "Before someone starts rewriting the truth.' \nMaeve's fingers stilled on the "
		"strings of her lute. 'I had a note once,' she said in a quiet voice. 'From the apprentice "
		"of the bard who wrote that fake story. He'd told the truth of what really happened and were "
		"probably killed because of it. He asked that people spread the truth and that to control "
		"the story meant control of everything. I accidentally let someone take it...' Maeve trailed "
		"off with a regretful expression. \n'I designed the NeuroArchive, the object that's altering "
		"memories. But it was stolen and I think it's design has been exploited, causing it to feed "
		"on memory. It's warping the truth. I have to get it back before everything is rewritten. "
		"Before there isn't a past left to protect. \nMaeve tilted her head as she thought. 'You "
		"know, I always thought if I got a second chance to chase a story worth dying for, I'd take "
		"it. Never imagined I'd be invited by the boy who made the mess we're going to go clean "
		"up.' \n'I can't promise that it'll be safe or easy,' Ben said. 'But I can promise you "
		"that we can make the world remember the author of your lost note, the truth, the way that "
		"your hometown remembers that story.' \nMaeve studied him. Then, slowly, she strummed a "
		"single, ringing note across the strings of her lute. 'That'll do, Ben. That'll do.' She "
		"rose and slung the instrument over her shoulder and turned toward the city. 'Let's rewrite "
		"the ending this time. Together.'\n\n";

//	slow_print(party, 0);
	slow_print(party);
}

//Displays Maeve's good ending
void bard::good_ending() const
{

}

//Displays Maeve's bad ending
void bard::bad_ending() const
{

}

/* Ben Rohman, benrohman3@gmail.com
 *
 * Level 6 member function implementations
 */

#include "levels.h"

//constructor
level6::level6()
{
	completed = false;
	load_story();
}

//returns completed flag
bool level6::is_complete() const
{
	return completed;
}

//main level control
bool level6::play(user * pl)
{
	//variables
	int cmd {0};

	intro();
	do
	{
		cmd = menu();
//		int cmd = menu();
		if (cmd == 1)
		{
			std::string person = choose();
			disp_full(person);

		}
		else if (cmd == 2)
		{
			std::string par = pick();
			disp_part(par);
		}
		else if (cmd == 3)
			review();
		else if (cmd == 4)
		{
			if(choose_truth())
			{
				slow_print("\n\n\t\t" + ITALIC + "=========== Level 6 Passed " +
					   "=========\n\n" + RESET);
				completed = true;
				return true;
			}
			else
			{
				slow_print("\n\n\t\t" + ITALIC + "Truths are still hidden, lies " +
					   "persist... Level 6 failed...\n\n" + RESET);
				completed = false;
				return false;
			}
		}
		else if (cmd == 5)
		{
			completed = false;
			return false;
		}
		if (cmd < 1 || cmd > 5)
			std::cout << BOLD << RED << "[ERROR] Invalid input. Try again. " << RESET 
				  << std::endl;
	}	while(cmd < 1 || cmd > 5);
	completed = false;
	return completed;
}

//helper function to add a story
void level6::add_story(const std::string & person, const std::string & title, 
		       const std::vector<std::string> & facts)
{
	story s;
	s.person = person;
	s.title = title;
	s.version = facts;
	int count {1};
	for (const auto & f : facts)
	{
		part p;
		p.text = f;
		p.claimed = person;
		p.id = count++;
		s.parts.push_back(p);
	}
	stories.push_back(s);
}

//loads full stories and parts into vectors
void level6::load_story()
{
	add_story("Ben", "Milan's Death", 
		{
			"One moment, Milan was grinning at me from across the table, the glow of runes "
			"reflecting in his eyes. The next, he was screaming, beggingg for us to make "
			"it stop.",
			"Until he... died. I thought I could shut it down if anything when wrong, but "
			"it wouldn't respond to the override.",
			"Theo ran for help while I kept trying, but by the time he got back it was too "
			"late.",
			"We'd all known the risks, but Milan... he trusted me. I was supposed to keep "
			"him safe."
		});
	add_story("Theo", "Milan's Death",
		{
			"Milan's death wasn't an accident, it was inevitable.",
			"Ben pushed the experiment ahead, brushing off every warning, claiming he had "
			"'mitigated the risks'. I heard Milan hesitating.",
			"Ben insisted we had enough data, that there was no possibility of harm being "
			"done to Milan.",
			"But he was never good at double checking his work. The moment the magical "
			"static sparked, I knew. I saw the panic in Milan's face. I can still hear "
			"him... asking why I let him do it. That's why I left to go get help, and why "
			"I want to help him now."
		});
	add_story("Velia", "Milan's Death",
		{
			"I heard some professors gossip about what happened.",
			"Some think Milan willingly volunteered. He'd always followed the other two "
			"wherever they went, he'd have done anything for them. Others swear he'd been "
			"pressured, maybe even tricked.",
			"They all mention feeling the air fold in on itself and as if their thoughts "
			"were being pulled away from them.",
			"A few said Ben was holding him when it happened, others claim Theo dragged "
			"him away right before Milan put a althame in his chest."
		});
}
	

/*loads full stories and parts into vectors
void level6::load_story()
{
	stories.push_back({
		{"Ben", "Milan's Death",
			{"One moment, Milan was grinning at me from across the table, the glow of "
			 "runes reflecting in his eyes. The next, he was screaming, begging for "
			 "us to make it stop.", 1},
			{"Until he... died. I thought I could shut it down if anything went wrong, "
			 "but it wouldn't respond to the override.", 2},
			{"Theo ran for help while I kept trying, but by the time he got back it was "
			 "too late.", 3}, 
			{"We'd all known the risks, but Milan... he trusted me. I was supposed to "
			 "keep him safe.", "Ben", 4} 
		}
	});
	stories.push_back({
		{"Theo", "Milan's Death",
			{"Milan's death wasn't an accident, it was inevitable.", "Theo", 5},//true
			{"Ben pushed the experiment ahead, brushing off every warning, claiming "
			 "he had 'mitigated the risks'. I heard Milan hesitating.", "Theo", 6},//false
			{"Ben insisted we had enough data, that there was no possibility of harm "
			 "being done to Milan.", "Theo", 7},//false
			{"But he was never good at double checking his work. The moment the magical "
			 "static sparked, I knew. I saw the panic on Milan's face. I can still hear "
			 "him... asking why I let him do it. That's why I left to get help, and why "
			 "I want to help him now.", "Theo", 8}//true
		}
	});
	stories.push_back({
		{"Velia", "Milan's Death",
			{"I heard the professors gossip about what happened.", "Velia", 9},//true
			{"Some think Milan willingly volunteered. He'd always followed the other "
			 "two wherever they went, he'd have done anything for them. Others swear "
			 "he'd been pressured, maybe even tricked.", "Velia", 10},//false
			{"They all mentioned feeling the air fold in on itself and as if their "
			 "thoughts were being pulled away from them.", "Velia", 11},//true
			{"A few said Ben was holding Milan when it happened, others claim Theo dragged "
			 "him away right before Milan put a althame in his stomach.", "Velia", 12}//false
		}
	});
	stories.push_back({
		{"Ben", "Blame",
			{"I wanted to show the Headmaster the NeuroArchive's promise by stripping down "
			 "the interface, demonstrating the compression logic without extracting "
			 "memories.", "Ben", 13},//true
			{"Milan volunteered as the test subject, I never wanted him to, it was too "
			 "dangerous, too risky.", "Ben", 14},//true
			{"But Theo kept telling Milan that it would be fine, that he could handle it, "
			 "at least that's how I remember it. But I can't shake the feeling something's "
			 "missing from that day...", "Ben", 15},//true
			{"Still, I know Theo kept pushing for 'undeniable proof' of the NeuroArchive's "
			 "potential to show the dean when I wanted to dial things back. Maybe we were "
			 "just naive. But I refuse to let his death be meaningless.", "Ben", 16}//true
		}
	});
	stories.push_back({
		{"Theo", "Blame",
			{"I wanted to add safe guards, find another way to prove its potential "
			 "without testing it on anyone.", "Theo", 17},//false
			{"Ben said that it would work. If we did nothing then we'd lose everything, "
			 "our work, our futures, our dreams.", "Theo", 18},//false
			{"Even though I see now that it was his work, his dreams, not mine nor "
			 "Milan's, I don't know if what Ben said convinced me. If I kept trying to "
			 "slow the test or if I was pushing him forward.", "Theo", 19},//true
			{"And Milan... Milan followed him like a shadow. Ben wrapped his recklessness "
			 "in talk of discovery. He gambled with a life, and lost.", "Theo", 20}//true
		}
	});
	stories.push_back({
		{"Velia", "Blame",
			{"They both wanted the experiment to happen, they just tell it differently." 
			 "Velia", 21}//true
			{"One claims they were being cautious while the other pushed too far." 
			 "Velia", 22},//false
			{"As for Milan, some say he was the one who insisted they try. That it was the "
			 "only way to avoid losing everything, to achieve their dreams and change the "
			 "world.", "Velia", 23},//false
			{"He believed that Ben had built something incredible, believed in both of "
			 "them. That's why he stepped in at all.", "Velia", 24}//true
		}
	});
	stories.push_back({
		{"Ben", "The Split",
			{"When the Headmaster ordered that I oversee the NeuroArchive dismantled, "
			 "I agreed. Destroying it was the only way I could forgive myself, at least "
			 "that's what I always told myself.", "Ben", 25},//false
			{"But there's these sketches in my old notebooks, designs, refinements, and "
			 "footnotes from the Tome I don't remember decoding.", "Ben", 26},//true
			{"Before I left for the Wizard City we fought, Theo called me a coward for "
			 "agreeing to destroy it, said I was betraying Milan.", "Ben", 27},//true
			{"But it was never meant to cost lives and it's not our place to make it "
			 "worth Milan losing his.", "Ben", 28}//false
		}
	});
	stories.push_back({
		{"Theo", "The Split",
			{"The Headmaster's 'order' was a grave dug with polished words. Ben didn't "
			 "even fight it, just stood there looking... guilty.", "Theo", 29},//true
			{"We fought before he left, I told him that he was throwing away Milan's "
			 "life and the most important magical advancement in decades." 
			 "Theo", 30},//true
			{"But he argued that continuation of the project would be disrespectful to "
			 "Milan's suffering and dangerously reckless.", "Theo", 31},//false
			{"Then I found out later he'd kept working on it, in secret. That's when I "
			 "realized, he's not guilty or trying to protect anyone from ending up like "
			 "Milan. He's trying to protect his legacy, he's afraid the world will "
			 "remember Milan as his failure.", "Theo", 32}//true
		}
	});
	stories.push_back({
		{"Velia", "The Split",
			{"I heard them fighting in one of those stone corridors near the gates of the "
			 "Academy.", "Velia", 33},//true
			{"Theo's voice was angry, accusing Ben of betrayal.", "Velia", 34},//true
			{"Ben's voice was quieter, almost apologetic, but... there was something in it. "
			 "Something cold, disingenuous. Almost annoyance at Theo's accusations.", 
			 "Velia", 35},//false
			{"Before Ben turned toward to leave and Theo stormed back inside the Academy "
			 "I heard Theo shout one last thing, louder this time. He said, 'One day, "
			 "you'll admit the truth, even if it kills you.'", "Velia", 36}//true
		}
	});
	stories.push_back({
		{"Ben", "Present",
			{"I've seen the NeuroArchive hurt people. Why would I have kept working on it? "
			 "I mean, it gave Aurora her powers... its helped others in some ways... but "
			 "I wouldn't have kept going... right?", "Ben", 37},//false
			{"But the sketches and notes in my old notebook...  I think they could hold the "
			 "key to fixing it. To make it into everything I designed it to be. I could fix "
			 "everything.", "Ben", 38},//true
			{"Part of me wants to live in those memories forever, to keep him alive in some "
			 "way. But if he is still in there, I know he deserves to be freed, to be "
			 "allowed to rest.", "Ben", 39},//false
			{"But I KNOW that destroying it is the only way to ensure it can't hurt anyone "
			 "else.", "Ben", 40}//false
		}
	});
	stories.push_back({
		{"Theo", "Present",
			{"I know how dangerous the NeuroArchive is, but it holds what's left of Milan. "
			 "If it's destroyed, he's gone forever.", "Theo", 41},//true
			{"Maybe... I can keep Milan alive with it somehow. A person is just a sum "
			 "of memories, if I can preserve them, like Milan's in the NeuroArchive, "
			 "reshape them, I can bring him back... he'll never die. No one would.", 
			 "Theo", 42},//false
			{"This isn't just about grief, though. It's about refusing to let fear dictate "
			 "what we can create, what is 'true'.", "Theo", 43},//true
			{"Ben pretends he's the responsible one, but I was there when the NeuroArchive "
			 "was created. He's not as virtuous as he says, whether he admits it or not.", 
			 "Theo", 44}//true
		}
	});
	stories.push_back({
		{"Velia", "Present",
			{"It seems like they've traded masks somewhere along the way.", "Velia", 45},//false
			{"Their stories sound jumbled together, like they can't remember which one is "
			 "theirs and which is the other's.", "Velia", 46},//true
			{"One claims to want it gone but continued to enhance its design and intended "
			 "to use it. The other says it should be used but might be the one willing to "
			 "stop it. Or maybe they've both convinced themselves of lies.", "Velia", 47},//false
			{"I can't tell which version of Milan's memory is real... or if either of them "
			 "can.", "Velia", 48}//true
		}
	});
}
*/
//level header
void level6::intro()
{
	slow_print("\n\n\t\t" + ITALIC + UNDERLINE + "========= Level 6: Three Sides to the Story "
		   "========= " + RESET + "\n\n\tInvestigate Three Accounts of an Event and Figure "
		   "Out Which is True...");
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
}

//gets the users menu selection
int level6::menu() const
{
	int ch {0};
	slow_print("\n\n\t\t--------- Investigation Menu ---------\n\t(1) View a Specific Person's "
		   "Version of Events \n\t(2) View the Same Part From all Three Stories \n(3) View "
		   "Your Notebook \n\t(4) Choose the Truth \n\t(5) Give Up \n\nEnter choice: ");
	std::cin >> ch;
	std::cin.ignore(100, '\n');
	return ch;
}

//gets which person's story the player wants to see(if selected)
std::string level6::choose() const
{
	std::string person;
	do
	{
		slow_print("\n\n\tChoose Which Person's Version You Want to View "
			   "<Ben>/<Theo>/<Velia> \nChoose Person: ");
		std::getline(std::cin, person);
		if (person == "Ben" || person == "Theo" || person == "Velia")
			return person;
		else
			std::cout << BOLD << RED << "\n[ERROR] Invalid input. Try again." << std::endl;
	}	while (person != "Ben" || person != "Theo" || person != "Velia");
	return person;
}

//gets the part the player wants to see (if selected)
std::string level6::pick() const
{
	std::string part;
	do
	{
		slow_print("\n\n\tChoose Which Part of The Story You Want to View: \n\t(1) Part 1: "
			   "Milan's Death \n\t(2) Part 2: Blame \n\t(3) Part 3: The Split \n\tPart 4: "
			   "Present \nChoose Part<milan's death>/<blame>/<the split>/<present>: ");
		std::getline(std::cin, part);
		std::transform(part.begin(), part.end(), part.begin(), ::tolower);
		if (part == "milan's death" || part == "blame" ||  part == "the split" || 
		    part == "present")
			return part;
		else
			std::cout << BOLD << RED << "\n[ERROR] Invalid input. Try again." << std::endl;
	}	while (part == "part 1" || part == "part 2" ||  part == "part 3" || part == "part 4");
	return part;
}

//displays a person's full story
void level6::disp_full(const std::string & person)
{
	for (auto & s : stories)
	{
		if (s.person == person)
		{
			for (auto & p : s.parts)
			{
				if (notebook.find(p.id) == notebook.end())
				{
					notebook.insert(p.id);
					slow_print("\n\t[" + s.title + "] [Fact ID: " + 
						   std::to_string(p.id) + 
						   "[Claimed by: " + p.claimed + '\n' + p.text + '\n');
				}
				else
					std::cout << BOLD << RED << "[ERROR] Fact ID: " << p.id 
						  << "already in notebook, skipped " << std::endl;
			}
			return;
		}
	}
}

//displays the part of the stories the player wants to see
void level6::disp_part(const std::string & par)
{
	for (auto & s : stories)
	{
		for (auto & p : s.parts)
		{
			if (s.title.find(par) != std::string::npos)
			{
				notebook.insert(p.id);
				slow_print("\n\t[" + s.title + "] [Fact ID: " + std::to_string(p.id) + 
					   "[Claimed by: " + p.claimed + '\n' + p.text + '\n');
			}
			else
				std::cout << BOLD << RED << "[ERROR] Fact ID: " << p.id 
					  << "already in notebook, skipped " << std::endl;
		}
	}
}

//displays the notebook
void level6::disp_notebook() const
{
	slow_print("\n\n\t--------- Notebook ---------\n\n");
	for (auto & story : stories)
	{
		for (auto & part : story.parts)
		{
			if (notebook.count(part.id))
			{	
				std::cout << '[' << part.claimed << ']' << part.text;
				if (truth.count(part.id))
					std::cout << " [Marked: ";
				std::cout << '\n';
			}
		}
	}
}

//marks facts in the notebook as 'true' or false
bool level6::review()
{
	if (notebook.empty())
	{
		std::cout << BOLD << RED << "[ERROR] Your notebook is empty. " << std::endl;
		return false;
	}
	slow_print("\n\n\t========= NOTEBOOK REVIEW ========= \n\n\tMark each discovered "
		   "fact as " + BOLD + GREEN + "TRUE " + RESET + "or " + BOLD + RED + "FALSE" +
		   RESET);
	for (auto fid : notebook)
	{
		const part * fptr {nullptr};
		for (const auto & s : stories)
		{
			for (const auto & p : s.parts)
			{
				if (p.id == fid)
				{
					fptr = &p;
					break;
				}
			}
			if (fptr)
				break;
		}
		if (!fptr)
			continue;	//skip if not found
		disp_part(fptr->text);
		char mark {' '};	//players choice to mark fact as true/false
		do
		{
			std::cout << "Mark as " << BOLD << GREEN << "True " << RESET << "or " 
				  << BOLD << RED << "False" << RESET << ", <t>/<f>: ";
			std::cin >> mark;
			mark = std::tolower(mark);
			if (mark == 't')
				truth[fptr->id] = true;
			else if (mark == 'f')
				truth[fptr->id] = false;
			else
				std::cout << BOLD << RED << "[ERROR] Invalid input. Enter 't' or 'f'. "
					  << RESET << std::endl;
		}	while(true);
		std::cout << '\n' << std::endl;
	}
	slow_print("\n\tAll facts have been marked.\n");
	return true;
}

//final phase of the level, player's notebook with t/f markings compared to facts 'real' markings
bool level6::choose_truth()
{
	bool all {true};
	std::map<int, bool> correct = 
	{
		{1, true}, {2, true}, {3, true}, {4, true}, {5, true}, {6, false}, {7, false}, 
		{8, true}, {9, true}, {10, false}, {11, true},  {12, false}, {13, true},
		{14, true}, {15, true}, {16, true}, {17, false}, {18, false}, {19, true}, 
		{20, true}, {21, true}, {22, false}, {23, false}, {24, true}, {25, false},
		{26, true}, {27, true}, {28, false}, {29, true}, {30, true}, {31, false}, {32, true},
		{33, true}, {34, true}, {35, false}, {36, true}, {37, false}, {38, true}, {39, false},
		{40, false}, {41, true}, {42, false}, {43, true}, {44, true}, {45, false}, {46, true},
		{47, false}, {48, true}
	};
	//iterate through players truths vector
	for (const auto & entry : truth)
	{
		int fid {entry.first};
		bool pmark {entry.second};
		//check if fact in notebook
		if (notebook.find(fid) == notebook.end())
		{
			std::cerr << BOLD << RED << "[ERROR] Fact ID " << fid << " is not in the "
				  << "notebook " << RESET << std::endl;
			all = false;
			continue;
		}
		//check if fid exits in correct
		auto it = correct.find(fid);
		if (it == correct.end())
		{
			std::cerr << BOLD << RED << "[ERROR] No correct answer found for Fact ID "
				  << fid << RESET << std::endl;
			all = false;
			continue;
		}
		//compare player's marking to correct marking
		if (pmark != it->second)
		{
			std::cerr << BOLD << RED << "[ERROR] Incorrect Fact ID: " << fid << " is "
				  << "marked as " << (pmark ? "True" : "False") << " but should "
				  << "be " << (it->second ? "True" : "False") << RESET << std::endl;
			all = false;
		}
	}
	return all;
}

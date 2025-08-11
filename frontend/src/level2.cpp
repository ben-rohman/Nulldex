/* Ben Rohman, benrohman3@gmail.com
 *
 * level2 member function + any helpers defs 			*/

#include "levels.h"

//constructor
level2::level2()
{
	completed = false;
	num = 0;
	trials =
	{
		{"Truth Trial", false, false},
		{"Memory Trial", false, false},
		{"Light Trial", false, false}
	};
	riddle =
	{
		"\n\n\tA glyph inscribed with no intent, \n\tA portal carved where none were "
		"meant, \n\tIt bears no name, no mark, no fate, \n\tIt leads to void and empty "
		"state, \nWhat rune am I, that spells no thing?\n", "null"
	};
	hints = 
	{
		"\n\n\tHint 1: Seek not what is, but what is not. The answer hides in emptiness. ",
		"\n\n\tHint 2: The rune defined by absence rather than presence. It holds space "
		"but contains nothing. ",
		"\n\n\tHint 3: In many systems, it means zero, yet it is not a number, but the "
		"concept of nil. ",
		"\n\n\tHint 4: In programming, it often represents no value, a placeholder for "
		"the empty or missing. ",
		"\n\n\tHint 5: It is the answer named in silence, a symbol of an address "
		"left unwritten, the null that means none. "
	};
	frags =
	{
		{"lune", "In Sky's tavern, Lune brushed the legs of patrons in hopes of head "
		 "scratches.", "Brushed the legs of patrons in hopes of head scratches."},
		{"yuki", "When bellowing voices began to fill the tavern, Yuki ran to Sky's "
		 "room upstairs.", "Ran and hid in Sky's room when bellowing voices filled "
		 "the taver."},
		{"scooby", "Guards ranted to Sky about a dog named Scooby sneaking into the "
		 "City's emergency rations and eating 2 winters' worth of food.", "Snuck into "
		 "the City's emergency rations and ate 2 winers' worth of food."},
		{"mr chow", "In the field next to Sky's City, a cat named Mr Chow dozed "
		 "peacefully in the sun.", "Dozed peacefully in the sun in the field next "
		 "to Sky's City."},
		{"tuck", "The buther's dog, Tuck, as simple and happy as they come, chased "
		 "his own shadow.", "As simple and happy as they come, chased his own shadow."}
	};
	poems = 
	{
		{"\n\tThe silent dusk, a fleeting breath, \n\tLost to shadows, whispered "
		 "death. \n\tNo last word, no mournful cry, \n\tVeiled beneath a somber "
		 "sky. \n\tIn hidden halls where secrets dwell, \n\tEchoes rise, a silent "
		 "toll. \n\tThe name once bright, now softly wanes.", "milan", 
		 {
		 	{"mournful", "mou"}, 
			{"hidden", "hid"}, 
			{"dwell", "ell"}, 
			{"name", "nam"}, 
			{"wanes", "ane"}
		}}, 
		{"\n\tSecrets taken, veiled in static, \n\tBy the one that is vatic. "
		 "\n\tFootsteps swift in moonlit halls, \n\tEcho faint where silence calls. "
		 "\n\tMasked in shadows, truth concealed, \n\tA whispered name the light "
		 "revealed. \n\tLook to where secrets grow.", "theo",
		 {
		 	{"taken", "tak"}, 
			{"echo", "cho"}, 
			{"concealed", "cea"}, 
			{"grow", "row"}
		}},
		{"\n\tThe architect of whispered lore, \n\tBuilder of the hidden door. "
		 "\n\tCurious hands that weave the thread, \n\tBinding the living and the "
		 "dead. \n\tBurden carried, veiled in pain, \n\tTruth concealed within "
		 "the Arcane. \n\tListen close to the ember's ken.", "ben",
		 {
		 	{"builder", "bui"}, 
			{"dead", "dea"}, 
			{"arcane", "ane"}
		}} 
	};
}

//returns the comepleted flag
bool level2::is_complete() const
{
	return completed;
}

//level control
bool level2::play(user * player)
{
	//table of trial functions
	using trial_func = bool (level2::*)();
	std::vector<trial_func> funcs = 
	{
		&level2::truth_trial,
		&level2::mem_trial,
		&level2::light_trial
	};

	slow_print("\n\n\t\t" + ITALIC + UNDERLINE + "========= Level 2: The Chamber of Trials =========\n\n"
		   + RESET + "\tComplete at least 2 trials to advance.");
	//main loop
	while (num < 2)
	{
		//variables
		char choice;		//player's trial choice
		size_t index;		//index of chosen trial
		bool result {false};	//flag for if the trial was completed

		slow_print("\nChoose a trial: \n");
		for (size_t i = 0; i < trials.size(); ++i)
		{
			if (!trials[i].attempted)
				std::cout << '(' << (i + 1) << ") " << trials[i].name << std::endl;
		}
		std::cout << "(Q) Quit " << std::endl;
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (choice == 'Q' || choice == 'q')
		{
			slow_print("\n\t\tYou step away from the trials... for now.");
			return false;	//player quits early
		}
		index = choice - '1';
		if (index >= trials.size() || trials[index].attempted)
		{
			slow_print("\n\tInvalid trial or trial has already been completed. Try again.");
			continue;	//go back to start of loop
		}
		result = (this->*funcs[index])();
		trials[index].attempted = true;
		trials[index].passed = result;
		if (result)
		{
			++num;
			slow_print(trials[index].name + (result ? " completed successfully " : "was not "
							 "completed ") + '\n');
		}
	}
	slow_print("\n\n\t\t" + ITALIC + "Level 2 completed \n" + RESET);
	completed = true;
	return true;
}



//truth trial (reacts to memory trial)
bool level2::truth_trial()
{
	//variables
	bool done {trials[MEMORY].passed};
	int lim {done ? 5 : 4};
	int attempts {0};
	
	clear_screen();
	slow_print("\n\n\t\t" + ITALIC + "--------- Trial of Truth: Solve the Riddle of the Hollow "
		   "Sigil ---------" + RESET);
	do
	{
		slow_print("\n\tAttempts remaining: <" + std::to_string(lim - attempts) + ">" );
		slow_print(riddle.question);
		std::string ans = guess();
		if (check(ans, riddle.answer))
		{
			slow_print("\n\n\t\t" + ITALIC + "Correct. The rune that is nothing shapes all "
				   "that is. Understanding the void grants passage.\n" + RESET);
			return true;
		}
		give_hint(attempts, lim);
		++attempts;
	}	while (attempts < lim);
	slow_print("\n\n\t\t" + ITALIC + "The trial was failed and truth remains hidden...\n " + RESET);
	return false;
}

//truth trial helper, displays hints
void level2::give_hint(int attempt, int lim) const
{
	if (attempt < lim && attempt < static_cast<int>(hints.size()))
		slow_print(hints[attempt]);
	else
		slow_print("\n\n\t\t" + ITALIC + "The silence remains. The path dims. \n" + RESET);
}

//memory trial
bool level2::mem_trial()
{
	clear_screen();
	slow_print("\n\n\t\t" + ITALIC + "--------- Trial of Rememberance: Match the Memory "
		   "Fragments ---------" + RESET);
	std::shuffle(frags.begin(), frags.end(), std::mt19937{std::random_device{}()});
	display_frags();
	slow_print("\n\n\tYou have seen the echoes. Recall them true.\n\n");
	return match_choices();
}


//helper for memory trial, displays the memory fragments
void level2::display_frags()
{
	//variables
		//if light trial completed, displayed for more time
	int wait {trials[LIGHT].passed ? 12 : 8};
	slow_print("\n\n\t[Flashback begins]\n\n");
	for (const auto & p : frags)
		std::cout << "- " << p.focus << ": " << p.memory << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(wait));
	clear_screen();
}

//memory trial helper, match the fragments
bool level2::match_choices()
{
	//variables
	int right {0};	//counter for number of correctly matched fragments
			//if light trial completed only need 3 frags to be 
			//	matched correctly, otherwise need 4
	int req {trials[LIGHT].passed ? 3 : 4};
	std::string ans;

	//shuffle twice for better replayability
	std::shuffle(frags.begin(), frags.end(), std::mt19937{std::random_device{}()});
	for (const auto & p : frags)
	{
		std::cout << "\nWho: " << p.part << "\nAnswer: ";
		std::getline(std::cin >> std::ws, ans);
		std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
		if (ans == p.focus)
			++right;
	}
	if (right >= req)
	{
		slow_print("\n\n\t\t" + ITALIC + "Well remembered... The trial has been "
			   "passed." + RESET);
		return true;
	}
	else
	{
		slow_print("\n\n\t\t" + ITALIC + "You've seen shadows... But memory deceives "
			   "the faithful... The trial was failed.\n" + RESET);
		return false;
	}
}

//hidden words in poems challenge
bool level2::light_trial()
{
	//variables
	//if truth trial completed get 4 attempts, otherwise get 3
	int max {trials[TRUTH].passed ? 4 : 3};
	int correct {0};	
				//make a copy for this attempt at the trial
	std::vector<poem> tmp = poems;

	clear_screen();
	slow_print("\n\n\t\t" + ITALIC + "--------- Trial of Light: Listen to Aether's Cryptic "
		   "Whispers ---------" + RESET);
	std::shuffle(tmp.begin(), tmp.end(), std::mt19937{std::random_device{}()});
	while (!tmp.empty())
	{
		int atmpt {0};
		bool solved {false};
		const poem & po = tmp.front();
		while (atmpt < max && !solved)
		{
			display_poem(po, atmpt);
			std::string reckon = guess();
			if (check(reckon, po.answer))
			{
				slow_print("\n\n\t\t" + ITALIC + "The light shines bright... "
					   "You have uncovered the secret.\n");
				solved = true;
				++correct;
			}
			else
			{
				++atmpt;
				if (atmpt < max)
					print_hint(atmpt);
			}
		}
		tmp.erase(tmp.begin());
		if (!solved)
		{
			slow_print("\n\n\t\t" + ITALIC + "The light's voice dims... you have failed "
				   "to uncover all of the secrets.\n" + RESET);
			return false;
		}
	}
	return correct == static_cast<int>(poems.size());
}

//light trial helper, displays poem
void level2::display_poem(const poem & po, int attempt)
{
	std::istringstream ls(po.text);
	std::string line;
	std::string answer = po.answer;
	std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
	std::string scrambled = answer;
	std::shuffle(scrambled.begin(), scrambled.end(), std::mt19937{std::random_device{}()});
	std::unordered_set<char> hletters (scrambled.begin(), scrambled.end());
	std::unordered_map<std::string, std::string> lower_clust;
	for (const auto & [word, cluster] : po.clust)
	{
		std::string lower_word = word;
		std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
		lower_clust[lower_word] = cluster;
	}

	while (std::getline(ls, line))
	{
		std::cout << '\t';
		//highlight words within the line
		std::istringstream ws(line);
		std::string word;
		while (ws >> word)
		{
			std::string strip = word;
			strip.erase(std::remove_if(strip.begin(), strip.end(),
						   [](unsigned char c) { return std::ispunct(c); }),
				    strip.end());
			std::string lower_word = strip;
			std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
			bool match = lower_clust.find(lower_word) != lower_clust.end();
			if (attempt == 0)
				slow_print(word + ' ');
			else if (attempt == 1)
			{
				if (match)
					slow_print(YELLOW + BOLD + word + RESET + ' ');
				else
					slow_print(word + ' ');
			}
			else if (attempt == 2)
			{
				if (match)
				{
					std::string cluster = lower_clust[lower_word];
					size_t pos = lower_word.find(cluster);
					if (pos != std::string::npos)
					{
						std::string before = word.substr(0, pos);
						std::string focus = word.substr(pos, cluster.size());
						std::string after = word.substr(pos + cluster.size());
						slow_print(before + YELLOW + UNDERLINE + focus + RESET + 
							   after + ' ');
					}
					else
						slow_print(word + ' ');
				}
				else 
					slow_print(word + ' ');
			}
			else if (attempt >= 3)
			{
				bool hlight = false;
				for (size_t i = 0; i < word.size(); ++i)
				{
					char c = word[i];
					char lc = std::tolower(c);
					if (!hlight && hletters.count(lc))
					{
						slow_print(YELLOW + std::string(1, c) + RESET);
						hletters.erase(lc);
						hlight = true;
					}
					else
						slow_print(std::string(1, c));
				}
				std::cout << ' ';
			}
			else
				slow_print(word + ' ');
		}
		std::cout << '\n';
	}
	slow_print("\n\nWhat does the light reveal?\n");
}

//light trial helper, gets the player's guess
std::string level2::guess() const
{
	std::string ans;
	std::cout << "Your answer: ";
	std::getline(std::cin >> std::ws, ans);
	std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
	return ans;
}

//light trial helper, checks if guess is correct
bool level2::check(const std::string & gs, const std::string & ans) const
{
	return gs == ans;
}

//light trial helper, prints hints
void level2::print_hint(int atmpt)
{
	switch (atmpt)
	{
		case 1:
		{
			slow_print("\n\n\tNot quite. Focus on the words illuminated in the light, "
				   "each contains a letter of the key.");
			return;
		}
		case 2:
		{
			slow_print("\n\n\tThe answer is a name, important to the story's hear. "
				   "The light shines on the three letters nearest that which you "
				   "seek" );
			return;
		}
		case 3:
		{
			slow_print("\n\n\tLast chance: consider the story of the Archivist that leads "
				   "the party... the key is now freely given but remains scrambled. ");
			return;
		}
		default:
			slow_print("\nThe flame's voice fades... you failed to complete the trial.");
	}
	return;
}





/*constructor
level2::level2() : completed(false) {}

//returns the 'completed' flage
bool level2::is_complete() const
{
	return completed;
}

//main gameplay logic
bool level2::play(user * player)
{
	//variables
	int chosen {0};		//which chosen
				//vector to hold trials (remove completed trials)
	std::vector<int> avail = {1, 2, 3};
	slow_print("\n\n\t\t" + ITALIC + UNDERLINE + "========= Level 2: The Trial of Fate =========\n\n" +
		   RESET, 60);

	slow_print("\tWelcome, seekers of fate. Choose your path. ");

	while (chosen < 2)
	{
		slow_print("\n\n\t\t" + ITALIC + BOLD + UNDERLINE + "========= Choose a Trial =========\n\n" 
			   + RESET);
		for (int i = 0; i < avail.size(); ++i)
		{
			switch (avail[i])
			{
				case 1:
					slow_print(std::to_string(i + 1) + ". Trial of Truth \n");
				case 2:
					slow_print(std::to_string(i + 1) + ". Trial of Remembrance \n");
				case 3:
					slow_print(std::to_string(i + 1) + ". Trial of Fire \n");
			}
		}

		int pick {0};	//player's choice
				//flag for if the trial was completed
		bool done {false};	

		do 
		{
			std::cout << "\nYour choice: ";
			std::cin >> pick;
			std::cin.ignore(10, '\n');
			
			if (pick < 1 || pick > static_cast<int>(avail.size()))
			{
				std::cout << RED << BOLD << "\n[ERROR] Invalid input. " << RESET
					  << std::endl;
				continue;		//gotta restart loop for input
			}

			int id = avail[pick - 1];

			if (id == 1)
			{
				if (!truth_trial())
					std::cout << "\nThe Trial of Truth was failed... " << std::endl;
			}
			else if (id == 2)
			{
				if (!mem_trial())
					std::cout << "\nThe Trial of Rememberance was failed... " 
						  << std::endl;
			}
			else
			{
				if (!fire_trial())
					std::cout << "\nThe Trial of Fire was failed... " << std::endl;
			}

			++chosen;			//increment num trials attempted
			avail.erase(avail.begin() + (pick - 1));
			done = true;
		}	while (!done);

	}
	completed = true;
	return true;
}

//Riddle Trial
bool level2::truth_trial()
{
	std::string riddle = 
		"\n\n\tA glyph inscribed with no intent, \n\tA portal carved where none were "
		"meant, \n\tIt bears no name, no mark, no fate, \n\tIt leads to void, and empty "
		"state, \n\tWhat rune am I, that spells no thing? \n";
	int attempts {0};
	std::string ans;
	const std::vector<std::string> hints = 
	{
		"\n\n\tSeek not what is, but what is not. The answer hides in emptiness. ",
		"\n\n\tThe rune is defined by absence rather than presence. It holds space, but "
		"contains nothing.",
		"In many systems, it means zero, yet it is not a number, but the concept of "
		"nothingness itself.",
		"In programming, it often represents no value, a placeholder for the empty or missing.",
		"It is the answer named in silence, a symbol of emptiness, the null that means none."
	};

	slow_print("\n\n\t\t---------- Trial of Truth: Solve the Riddle of the Hollow Sigil --------- "
		   "\n\tYou have 5 guesses... ");
	slow_print(riddle, 35);

	do
	{
		std::cout << "\nYour answer: ";
		std::getline(std::cin >> std::ws, ans);
		std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);

		if (ans == "null")
		{
			slow_print("\n\n\t\tCorrect. The rune that is nothing shapes all that is. "
				   "Understanding void grants passage.\n");
			return true;
		}
		
		if (attempts < static_cast<int>(hints.size()))
			slow_print(hints[attempts]);
		else
			slow_print("\nThe silence remains. The path dims.");

		++attempts;
	
	}	while(attempts < 5);

	return false;
}

//Memory trial
bool level2::mem_trial()
{
	generate_pairs();
	display_frags();
	slow_print("\n\n\t\t\tYou have seen the echoes. Recall them true. \n\n");

	return match_choices();
}

//generate the correct matches
void level2::generate_pairs()
{
	pairs = 
	{
		{"Lune", "Brewed healing tonics for the sick in Sky's tavern."},
		{"Yuki", "Refused to flee as the footsteps of giants shook the Earth."},
		{"Scooby", "Stood Guard at the gates of the Kingdom's emergency rations."},
		{"Mr. Chow", "Dozed peacefully on a rock in the sun and dreamt of FancyFeast."},
		{"Tuck", "Chased his own shadow, as simple and happy as they come."}
	};

	std::shuffle(pairs.begin(), pairs.end(), std::mt19937{std::random_device{}()});
}

//displays the memory fragments
void level2::display_frags()
{
	slow_print("\n\n\t[Flashback begins: Cats...]\n\n");
	for (const auto & p : pairs)
		std::cout << "- " << p.first << ": " << p.second << '\n';
	std::this_thread::sleep_for(std::chrono::seconds(8));
	clear_screen();
}

//helper to match the fragments
bool level2::match_choices()
{
	//variables
	int right {0};		//number of frags matched
	std::string ans;	//player's answer

	std::shuffle(pairs.begin(), pairs.end(), std::mt19937{std::random_device{}()});
	
	for (const auto & p : pairs)
	{
		std::cout << "\n\nWho: " << p.second << "\nAnswer: ";
		std::getline(std::cin >> std::ws, ans);
		std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
		std::string expect = p.first;
		std::transform(expect.begin(), expect.end(), expect.begin(), ::tolower);
		if (ans == expect)
			++right;
	}
	if (right >= 3)
	{ 
		slow_print("\n\tWell remembered... \n\tBut memory deceives even the faithful...\n");
		return true;
	}
	else
	{
		slow_print("\n\tYou have seen shadows... not truths.");
		return false;
	}
}


//moral dilemma trial
bool level2::fire_trial()
{
	int choice {0};

	slow_print("\n\n\t\t---------- Trial of Fire --------- \n\tOne must burn. One my pass. \n\tTo "
		   "your left: a young rebel, said to plot treason. \n\tTo your right: a priestess who "
		   "hid prophecy from the people. \n\tOnly one can be saved. " + BOLD + UNDERLINE +
		   "\n\n\t\tChoose. " + RESET);
	std::cout << "\n\n1. Save the revolutionary. \n\n2. Save the priestess. " << std::endl;

	std::cin >> choice;
	std::cin.ignore(10, '\n');

	if (choice == 1)	
		slow_print("\n\n\tYou chose wisdom... Or perhaps fear...\n");
	else
		slow_print("\n\n\tYou choose wisdom... Or perhaps fear...\n");

	slow_print("\n\n\t\tYour path is shaped... \n\n\t\tWe shall see who you become...");
	return true;
}
*/

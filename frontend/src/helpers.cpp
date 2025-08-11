/* Ben Rohman, benrohman3@gmail.com
 * 
 * These are gonna help with the game's flow or just serve as helper functions to various aspects. */

#include "game.h"
//#include "flow_control.h"

//Welcome message, explains the game to the user
void welcome()
{
	std::cout << "\n\n\t\t TITLE SCREEN " << std::endl;
}

//clear screen of text
void clear_screen()
{
#if defined(_WIN32)
	std::system("cls");
#else
	std::system("clear");
#endif
}

//prompts user to press 'enter' to continue
void wait()
{
	std::cout << "\nPress 'Enter' to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//to help regulate the output of text
void slow_print(const std::string & text, int delay)
{
	for (char c : text)
	{
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}

//TEMP QUIT FUNCTION
void quit()
{
	std::cout << "\n\t\t\tEXIT SUCCESS " << std::endl;
}

/*helper to make string arg passed all lower case
std::string to_lower(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
	return s;
}
*/
//Beginning combat helpers
bool tutorial_fight(user * mc)
{
	//variables
	int choice {0};
	bool escaped {false};
	player * p = mc->get_player();

	if (!mc)
	{
		std::cerr << RED << BOLD << "\n[ERROR] Null pointer passed. " << RESET << std::endl;
		return false;
	}

	monster thug (18, 4, 1, "Thug");

	slow_print("\nYou wander through the thick forest just outside the walls of the Wizard City. \nAs you "
		   "step into a clearing in the trees a shady figure blocks your path, a thug brandishing a "
		   "pipe stands before you. \nThug: Alright, easy now... Hand over what's in your pockets and "
		   "no one has to get hurt, alright? \nDo you want to try to fight him off or try to run away? "
		   "\n(1) Fight\n(2) Run\nChoice: ");
	std::cin >> choice;
	std::cin.ignore(10, '\n');

	if (choice == 2)
	{
		slow_print("\nYou turn and flee back into the forest dodging between the trees...");
		escaped = agility_success(p, 15);
		if (escaped)
		{
			slow_print("\nYou manage to lose the thug among the trees, escaping the danger for now...");
			return true;
		}
		else
			slow_print("\nYou trip on a root and fall to the ground. You stand back up just as the "
				   "thug catches back up to you, looking angrier...");
	}
	else
		slow_print("\nYou ready yourself for a fight...");

	std::cout << "\n\n\t\t========= COMBAT STARTED: Thug =========" << std::endl;

	while (p->get_curr_hp() > 0 && thug.hp.get_current() > 0)
	{
		show_stats(p, thug);
		if (!char_act(p, thug))
		{
			std::cerr << RED << BOLD << "\n[ERROR] Action failed in tutorial fight " << RESET 
				  << std::endl;
			return false;
		}

		if (thug.hp.get_current() > 0)
			dummy_turn(p, thug);
		p->get_class()->dec_cd();
	}
	if (p->get_curr_hp() > 0)
	{
		slow_print("\nThe thug stumbles and falls. \nThug: Man fuck this \nHe stands and runs into the "
			   "trees. \nYou've won your first fight!");
		return true;
	}
	else
	{
		slow_print("\nYou black out as the thugs final blow strikes your skull... you lost the fight.");
		return false;
	}
}

//shows the player and opponents stats
void show_stats(player * p, monster & thug)
{
	std::string name = p->get_name();
	slow_print('\n' + name + "'s HP: " + std::to_string(p->get_curr_hp()) + '/' +
		   std::to_string(p->get_maxhp()));
	if (p->get_curr_mp() > 0)
		slow_print("\nMP: " + std::to_string(p->get_curr_mp()) + '/' + std::to_string(p->get_maxmp()));
	slow_print("\nThug's HP: " + std::to_string(thug.hp.get_current()) + '/' + 
		  std::to_string(thug.hp.get_max()));
}

//player action control
bool char_act(player * p, monster & thug)
{
	//variables
	bool mag = p->get_curr_mp() > 0;
	bool success {false};

	do
	{
		int choice = choose_act(p, mag);
		if (choice == 1)
			success = use_weap(p, thug);
		else if (mag && choice == 2)
			success = cast_spell(p, thug);
		else if (choice == 3)
			success = use_item(p);
		else
			success = false;
	}	while (!success);
	return success;
}

//action menu
int choose_act(player * p, bool mag)
{
	//variables
	int choice {0};
	std::string name = p->get_name();

	slow_print("\n\n\t\t--------- " + name + "'s Turn ---------");
	do
	{
		slow_print("\nChoose an action: \n(1) Attack with a Weapon");
		if (mag)
			slow_print("\n(2) Cast a Spell");
		slow_print("\n(3) Use an Item \nEnter your choice here: ");
		std::cin >> choice;
		std::cin.ignore(10, '\n');

		if (std::cin.fail() || choice < 1 || choice > 3 || (!mag && choice == 2))
		{
			std::cin.clear();
			std::cerr << RED << BOLD << "\n[ERROR] Invalid input. Try again " << RESET << std::endl;
			choice = 0;
		}
	}	while (choice == 0);
	
	return choice;
}

//option 1
bool use_weap(player * p, monster & thug)
{
	//variables
	const weapon * mel = p->get_equip_weapon(static_cast<unsigned long long>(WEAPONSLOT::MELEE));
	const weapon * ran = p->get_equip_weapon(static_cast<unsigned long long>(WEAPONSLOT::RANGED));
	damage_type dmg {0};

	if (ran)
	{
		dmg = p->ranged_attack();
		slow_print("\nYou're shot hits the thug and deals " + std::to_string(dmg) + " damage");
		thug.hp.reduce(dmg);
	}
	else if (mel)
	{
		dmg = p->melee_attack();
		slow_print("\nYou're weapon hits the thug and deals " + std::to_string(dmg) + " damage");
		thug.hp.reduce(dmg);
	}
	return true;
}

//option 2
bool cast_spell(player * p, monster & thug)
{
	//variables
	int pick {0};

	const auto & sp = p->get_abil_list();
	if (sp.empty())
	{
		slow_print(RED + BOLD + "\n[ERROR] Ability vector is empty " + RESET);
		return false;
	}
	slow_print("\nChoose a spell to cast: ");
	for (size_t j = 0; j < sp.size(); ++j)
	{
		const ability * s = sp[j];
		std::string info =
			'\n' + std::to_string(j + 1) + ". " + s->get_name();
		if (p->get_class()->is_cooling(s->get_name()))
			info += " [Cooldown: " + std::to_string(p->get_class()->cd_left(s->get_name())) + ']';
		else if (s->get_cost() > p->get_curr_mp())
			info += " [Not enough MP] ";
		slow_print(info);
	}
	while (true)
	{
		std::cin >> pick;
		std::cin.ignore(10, '\n');
		if (pick >= 1 && pick <= static_cast<int>(sp.size()))
		{
			const ability * fin = sp[pick - 1];
			if (p->get_class()->is_cooling(fin->get_name()))
				slow_print(RED + BOLD + "\n[ERROR] Spell is on cooldown. Choose another" + RESET);
			else
			{
				damage_type dmg = fin->get_hpe();
				thug.hp.reduce(dmg);
				p->get_class()->start_cd(fin->get_name(), fin->get_cd());
				slow_print("\nYou cast " + fin->get_name() + " deaming " + std::to_string(dmg) +
					   " damage ");
				return true;
			}
		}
		else
			slow_print(RED + BOLD + "\n[Error] Invalid input. Try again " + RESET);
	}
	return false;
}

//option 3
bool use_item(player * p)
{
	//variables
	bool used {false};
	size_t i {0};
	const auto & bp = p->get_backpack_list();

	if (p->get_curr_hp() == p->get_maxhp())
	{
		slow_print(RED + BOLD + "\n[ERROR] Health is full. No potion needed. " + RESET);
		return false;
	}
	while (!used && i < bp.size())
	{
		item * it = bp[i];
		potion * pot = nullptr;
		if (it && it->get_data())
		{
			manager::cast_to_potion(it, pot);
			if (pot && pot->quantity > 0 && manager::use(it, p))
			{
				slow_print("\nPotion used: " + pot->name + '\n' + std::to_string(p->get_curr_hp()) +
					   '/' + std::to_string(p->get_maxhp()));
				used = true;
			}
		}
		++i;
	}
	if (!used)
		slow_print(RED + BOLD + "\n[ERROR] No useable potions found." + RESET);
	return used;
}

void dummy_turn(player * p, monster & thug)
{
	//variables
	bool dodge {false};

	slow_print("\n\n\t\t--------- Thug's Turn --------- \nHe raises his pipe and swings it at you.");
	dodge = agility_success(p, 15);
	if (dodge)
		slow_print("\nYou dodge out of the way narrowly missing the pipe...");
	else
	{
		int dmg = roll_d8();
		p->damage(dmg);
		slow_print("\nYou mistimed your dodge and the pipe strikes you dealing " + std::to_string(dmg) +
			   " damage");
	}
}

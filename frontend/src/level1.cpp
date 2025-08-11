/* Ben Rohman, benrohman3@gmail.com
 *
 * Implementation of the required Level 1 functions		*/

//#include "monster.h"
#include "levels.h"
#include "game.h"
#include "types.h"
#include "user.h"
#
//constructor
level1::level1()
{
	completed = false;
}

//level control function
bool level1::play(user * player)
{
/*	//Variables
						//Memory fragments for puzzles	
	std::vector<std::pair<std::string, std::string>> puzzles = {
		{ "\n[Memory Fragment 1]\nShe always said... \n(a) Stay strong\n(b) Look forward\n(c) Never "
		  "run\n> ", "c" },
		{ "\n[Memory Fragment 2]\nThe day it all changed was...\n(a) The storm\n(b) The silence\n(c) "
		  "The song\n> ", "a"},
		{ "\n[Memory Fragment 3]\nWhat did he give you?\n(a) A knife\n(b) A charm\n(c) A promise\n> ",
		  "a" }
	};
	int correct {0};			//how many has the player gotten right?
	bool survived {false};			//flag for if the player survived the wraith

*/	clear_screen();
	slow_print("\n\n\t\t" + ITALIC + UNDERLINE + "========= Level 1: Echoes in the Mind =========\n\n" + 
		   RESET, 60);
	
/*	//solve the puzzles
	for (size_t i {0}; i < puzzles.size(); ++i)
	{
		if (mem_puzzle(puzzles[i].first, puzzles[i].second))
			++correct;

	//threat progression messages
		if (i == 0)
			slow_print("\n... You feel something moving in the distance... ", 40);
		else if (i == 1)
			slow_print("\n... The air thickens. It's getting closer... too close...", 40);
		else if (i == 2)
			slow_print("\n... The mist parts... it's here... \nTranslucent fog flooded through "
				   "fog", 40);
	}

	//scale wraith based on incorrect answers
	damage_type b_min = 4 + (3 - correct);
	damage_type b_max = 8 + 2 * (3 - correct);
	well_type wraith_hp = 30 + 5 * (3 - correct);

	//create monster
	monster wraith(wraith_hp, b_min, b_max, "Mind Wraith");
*/	monster wraith(35, 5, 10, "Mind Wraith");
//	//error check
//	if (!mind_wraith)
//	{
//		std::cout << "\nYOUR MONSTER CONSTRUCTOR DON'T WORK!! " << std::endl;
//		return false;
//	}
//	slow_print("\n\nout a bloodcurdling shriek and its spectral form flickered. "); 

	//start combat sequence
	bool survived = fight_wraith(player, wraith);	
	if (survived)	
	{
		slow_print("\nThe Wraith disolves. The memory fades, but the chill lingers... \nLevel 1 "
			   "Complete\n", 40);
		completed = true;
	}
	else
	{
		slow_print("\nYour thoughts shatters and vision fades as the Mind Wraith consumes your "
			   "thoughts...\n");
		completed = false;
	}
	//temp debug test
	return true;

//	return survived;
}

//function that returns if the level was completed or not, accessor
bool level1::is_complete() const
{
	return completed;
}

/*private member function for solving the memory puzzles
bool level1::mem_puzzle(const std::string & prompt, const std::string & ans)
{
	//Variables
	std::string res;
	slow_print(prompt, 30);
	std::getline(std::cin, res);
	bool result {false};

	//make lowercase
	std::transform(res.begin(), res.end(), res.begin(), ::tolower);

	//check if player's input is correct and return result
	if (res == ans)
	{
		slow_print("\n...The memory aligns, just for a moment\n", 40);
		return true;
	}
	else
	{
		slow_print("\n...The fragments scatter...\n", 40);
		return false;
	}
	if (!play || !play->get_player())
	{
		std::cerr << RED << BOLD << "\n[ERROR] Null pointer found at first error check in "
		          << "fight_wraith. " << RESET << std::endl;
		return false;
	}
	player * p = play->get_player();
	if (!p)
	{
		std::cerr << RED << BOLD << "\n[ERROR] Player object construction failed in fight_wraith. "
			  << RESET << std::endl;
		return false;
	}

	slow_print("\n\n\t\t========= COMBAT STARTED: Mind Wraith =========\n", 40);

}
*/
bool level1::fight_wraith(user * play, monster & wraith)
{
	player * pl = play->get_player();
	if (!pl)
	{
		std::cerr << RED << BOLD << "\n[ERROR] Null pointer found at fight_wraith " << RESET << std::endl;
		return false;
	}
	combat c(pl, wraith);
	return c.control();
}
/*
//version that uses the combat class
bool level1::fight_wraith(user * player, monster & wraith)

//Main combat control function
bool level1::fight_wraith(user * play, monster & wraith)
{
	if (!play || !play->get_player())
	{
		std::cerr << RED << BOLD << "\n[ERROR] Null pointer found at first error check in "
		          << "fight_wraith. " << RESET << std::endl;
		return false;
	}
	player * p = play->get_player();
	if (!p)
	{
		std::cerr << RED << BOLD << "\n[ERROR] Player object construction failed in fight_wraith. "
			  << RESET << std::endl;
		return false;
	}

	slow_print("\n\n\t\t========= COMBAT STARTED: Mind Wraith =========\n", 40);
	while(p->get_curr_hp() > 0 && wraith.hp.get_current() > 0)
	{
		display_stats(p, wraith);

		if (!player_action(p, wraith))
		{
			std::cerr << RED << BOLD << "\n[ERROR] execution of player_action failed. " << RESET
				  << std::endl;
			return false;
		}

		if (wraith.hp.get_current() > 0)
			wraith_action(p, wraith);

		p->get_class()->dec_cd();
	}

	return p->get_curr_hp() > 0;	//is the player still alive
}

************************************** HELPER FUNCTION FOR COMBAT **************************************

//Displays the stats of the player and Wraith at the start of each turn
void level1::display_stats(player * p, monster & wraith)
{
	std::string name = p->get_name();
	slow_print('\n' + name + "'s HP: " + std::to_string(p->get_curr_hp()) + '/' + 
		   std::to_string(p->get_maxhp()));
	if (p->get_curr_mp() > 0)
		slow_print("\nMP: " + std::to_string(p->get_curr_mp()) + '/' + std::to_string(p->get_maxmp()));
	slow_print("\nWraith's HP: " + std::to_string(wraith.hp.get_current()) + '/' +
		   std::to_string(wraith.hp.get_max()));
}

//Handles the player's action turns
bool level1::player_action(player * p, monster & wraith)
{
	//variables
	bool mag = p->get_curr_mp() > 0;
	bool success {false};

	do 
	{
		int choice = choose_action(p, mag);
		if (choice == 1)
			success = weap_action(p, wraith);
		else if (choice == 2) 
			success = spell_action(p, wraith);
		else if (choice == 3)
			success = item_action(p);
		else
		{
			std::cerr << RED << BOLD << "\n[ERROR] Action function failed somehow. " << RESET 
				  << std::endl;
			success = false;
		}
	}	while (!success);
	return success;
}

//Reads in and returns the player's action choice
int level1::choose_action(player * p, bool mag)
{
	//variables
	int choice {0};
	std::string name = p->get_name();

	slow_print("\n\n\t\t--------- " + name + "'s Turn --------- ");
	do
	{
		slow_print("\nChoose an action: \n(1). Attack with a Weapon");
		if (mag)
			slow_print("\n(2). Cast a Spell");
		slow_print("\n(3). Use an Item \nEnter your choice here: ");
		std::cin >> choice;
		std::cin.ignore(10, '\n');

		if (std::cin.fail() || choice < 1 || choice > 3 || (!mag && choice == 2))
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cerr << RED << BOLD << "\n[ERROR] Invalid input. Try again. " << RESET << std::endl;
			choice = 0;
		}
	}	while (choice == 0);

	return choice;
}

//Handles the option to attack with a weapon
bool level1::weap_action(player * p, monster & wraith)
{
	//variables
	const weapon * mel = p->get_equip_weapon(static_cast<unsigned long long>(WEAPONSLOT::MELEE));
	const weapon * ran = p->get_equip_weapon(static_cast<unsigned long long>(WEAPONSLOT::RANGED));
	damage_type dmg {0};

	if (ran)
	{
		dmg = p->ranged_attack();
		slow_print("\nYour shot hits the Wraith and deals " + std::to_string(dmg) +
			   " damage.");
		wraith.hp.reduce(dmg);
	}
	else if (mel)
	{
		dmg = p->melee_attack();
		slow_print("\nYour blade slices through the Wraith's smoggy flesh, dealing " + 
			   std::to_string(dmg) + " damage.");
		wraith.hp.reduce(dmg);
	}

	if (ran)
	{
		if (agility_success(p, 17))
		{
			dmg = p->ranged_attack();
			slow_print("\nYou're shot hits the Wraith and deals " + std::to_string(dmg) + " damage.");
			wraith.hp.reduce(dmg);
		}
		else
			slow_print("\nYou're shot goes through the eldritch fog that had been the Wraith a "
				   "moment ago. It takes no damage. ");
	}
	else if (mel)
	{
		if (strength_success(p, 19))
		{
			dmg = p->melee_attack();
			slow_print("\nYou're blade slices through the Wraith's smoggy flesh, dealing " + 
				   std::to_string(dmg) + " damage. ");
			wraith.hp.reduce(dmg);
		}
		else
			slow_print("\nThe Wraith's incorporeal body vanished as you're blade swung at them. The "
				   "Wraith takes no damage. ");
	}

	return true;
}

//Handles the spell casting mechanics
bool level1::spell_action(player * p, monster & wraith)
{
	//variables
	int pick {0};

	const auto & sp = p->get_abil_list();
	if (sp.empty())
	{
		slow_print(RED + BOLD + "\n[ERROR] Ability vector is empty. " + RESET);
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
				slow_print(RED + BOLD + "\n[ERROR] That spell is on cooldown. Choose another. " +
					   RESET);
			else if (fin->get_cost() > p->get_curr_mp())
				slow_print(RED + BOLD + "\n[ERROR] Not enough MP. Choose another. " + RESET);
			else
			{
				damage_type dmg = fin->get_hpe();
				wraith.hp.reduce(dmg);
				p->get_class()->start_cd(fin->get_name(), fin->get_cd());
				slow_print("\nYou cast " + fin->get_name() + " dealing " + std::to_string(dmg) +
					   " damage. ");
				return true;
			}
		}
		else
			slow_print(RED + BOLD + "\n[ERROR] Invalid input. Try again." + RESET);
	}
	return false;
}
	

//Handles the option to use an item
bool level1::item_action(player * p)
{
	bool used {false};
	size_t i {0};
	const auto & backpack = p->get_backpack_list();

	if (p->get_curr_hp() == p->get_maxhp())
	{
		slow_print(RED + BOLD + "\n[ERROR] You're health is already full. No potion used. " + RESET);
		return false;
	}

	while (!used && i < backpack.size())
	{
		item * it = backpack[i];
		potion * pot = nullptr;
		if (it && it->get_data())
		{
			manager::cast_to_potion(it, pot);
			if (pot && pot->quantity > 0 && manager::use(it, p))
			{
				slow_print("\n--------- Potion Used: " + pot->name + "--------- \nHP: " +
					   std::to_string(p->get_curr_hp()) + '/' + std::to_string(p->get_maxhp()));
				used = true;
			}
		}
		++i;
	}
	if (!used)
		slow_print(RED + BOLD + "\n[ERROR] No useable potions found or HP is full.\n " + RESET);
	slow_print("\n--------- INVENTORY ---------\n");
	display_backpack(p);
	return used;
}

//Handles the Wraith's turn to attack
void level1::wraith_action(player * p, monster & wraith)
{
	//variables
	bool dodge {false};

	slow_print("\n\n\t\t--------- Wraith's Turn... --------- \nThe Mind Wraith lets out a bloodcurdling "
		   "shriek and lunges at you. You try to track it as it's warped silhouette flickers rapidly "
		   "towards you. ");
	dodge = agility_success(p, 15);
	if (dodge)
		slow_print("\nYou managed to dodge out of the way and see its hand slash through the air where "
			   "your head had been moments earlier. ");
	else
	{
		int dmg = roll_d8() + 2;
		p->damage(dmg);
		slow_print("\nYou mistimed your dodge. The Wraith hits you, dealing " + std::to_string(dmg) + 
			   " damage. ");
	}
}

****************************************** HOARDING OLD BUSTED FXNS **************************************
bool level1::fight_mind_wraith(user * play, monster & wraith)
{
	//variables
	bool mag {false};		//does the character have mp
	bool dodge {false};		//flag for if the player dodges successfully

	//error check	s
	if (!play || !play->get_player())
	{
		std::cerr << "\n[ERROR] Null pointer passed for user or player to fight_mind_wraith.\n";
		return false;
	}
	//create a 'player' pointer and error check
	player * p = play->get_player();
	if (!p)
	{
		std::cout << "\n[ERROR] Player object construction failed. " << std::endl;
		return false;
	}
	//if all good then get the character's name
	std::string name = p->get_name();
	
	//figure out if they have mp
	mag = p->get_curr_mp() > 0;	//true if mp > 0

	//start battle
	slow_print("\n\n\t\t========= COMBAT STARTED: Mind Wraith =========\n", 40);
	slow_print("The Mind Wraith shrieks and lunges from the shadows...\n", 40);
	
	//loop for turn based combat
	while (p->get_curr_hp() > 0 && wraith.hp.get_current() > 0)
	{
		//output stats
		slow_print(name + "'s HP: " + std::to_string(p->get_curr_hp()) + '/' + 
			   std::to_string(p->get_maxhp()));
		if (mag)
			slow_print("\nMP: " + std::to_string(p->get_curr_mp()) + '/' +
				   std::to_string(p->get_maxmp()));
		slow_print("\nWraith's HP: " + std::to_string(wraith.hp.get_current()) + '/' +
			   std::to_string(wraith.hp.get_max()));

		//player's turn
		slow_print("\n\n\t\t--------- " + name + "'s Turn --------- \nChoose an action: "
			   "\n1. Attack with a Weapon");
		if (mag)
			slow_print("\n2. Cast a Spell");
		slow_print("\n3. Use an Item");

		//get user input
		int choice = 0;
		do
		{
			std::cin >> choice;
			std::cin.ignore(10, '\n');

			if ((mag && choice >= 1 && choice <= 3) || (!mag && (choice == 1 || choice == 3)))
			{	
				slow_print("\n" + RED + BOLD + "[ERROR] Invalid input try again...");
			}
		}	while (true);
		if (choice == 1)
		{
			damage_type dmg = p->melee_attack();
			slow_print("\nYou strike the Mind Wraith and deal " + std::to_string(dmg) +
				   " damage.");
			wraith.hp.reduce(dmg);
		}
		else if (mag && choice == 2)
		{
			const auto & sp = p->get_abil_list();
			if (sp.empty())
				slow_print(RED + BOLD + "\n[ERROR] Ability vector is empty." + RESET);
			slow_print("\nChoose a spell to cast: ");
			int j = 1;
			for (const ability * s : sp)
			{
				std::string info = '\n' + std::to_string(j) + ". " + s->get_name();
				if (p->get_class()->is_cooling(s->get_name()))
					info += " [Cooldown: " + 
					std::to_string(p->get_class()->cd_left(s->get_name())) + ']';
				else if (s->get_cost() > p->get_curr_mp())
					info += " [Not enough MP]";
				slow_print(info);
				++j;
			}
			int pick;
			while (true)
			{
				std::cin >> pick;
				std::cin.ignore(100, '\n');
				if (pick >= 1 && pick <= static_cast<int>(sp.size()))
				{
					const ability * fin = sp[pick - 1];
					if (p->get_class()->is_cooling(fin->get_name()))
						slow_print(RED + BOLD + "\nThat spell is on cooldown. Choose "
							   "another." + RESET);
					else if (fin->get_cost() > p->get_curr_mp())
						slow_print(RED + BOLD + "\n[ERROR] Not enough MP. Choose "
							   "another." + RESET);
					else
					{
						damage_type dmg = fin->get_hpe();
						wraith.hp.reduce(dmg);
//						p->spend_mp(fin->get_cost());
						p->get_class()->start_cd(fin->get_name(), fin->get_cd());
						slow_print("\nYou cast " + fin->get_name() + "dealing " +
							   std::to_string(dmg) + " damage.");
					}
				}
				else
					slow_print(RED + BOLD + "\n[ERROR] Invalid input. Try again.");
			}
		}
		else if (choice == 3)
		{
			bool used = false;
			size_t i = 0;
			const auto & backpack = p->get_backpack_list();

			while (!used && i <backpack.size())
			{
				item * it = backpack[i];
				potion * pot = nullptr;

				if (it && it->get_data())
				{
					manager::cast_to_potion(it, pot);
					if (pot && pot->quantity > 0 && manager::use(it, p))
					{
						std::string msg = 
							"\n--------- Potion Used: " + pot->name +
							" ---------";
						std::string hp_msg = 
							"\nHP: " + std::to_string(p->get_curr_hp()) + '/' +
							std::to_string(p->get_maxhp());
						
						slow_print(msg);
						slow_print(hp_msg);

						used = true;
					}
				}
				++i;
			}
			if (!used)
				slow_print(RED + BOLD + "\n[ERROR] No useable potion found or HP is full." +
					   RESET);
			slow_print("\n--------- INVENTORY ---------\n"); 
			display_backpack(p);
		}
		
		//wraith's turn
		slow_print("\n\n\t\t--------- Wraith's Turn... -------- \nThe Mind Wraith lets out a "
			   "bloodcurdling shriek and lunges at you. You try to track it's movement as "
			   "form flickers as it advances quickly toward you.");
		
		//does the player successfully dodge the attack
		dodge = dodge_success(p, 15);
		if (dodge)		//success, no damage taken
			slow_print("\nIt's hand slashs through the air where you're head had been a "
				   "heartbeat earlier. You roll to the side then spring back to your "
				   "feet facing the Mind Wraith again.");
		else			//failure, damage taken
		{
			int dmg = roll_d8() + 2;
			p->damage(dmg);
			slow_print("\nYou mistimed your dodge and feel blinding pain as it's strike "
				   "hits you, dealing " + std::to_string(dmg) + " damage.");
			p->damage(dmg);
		}
	p->get_class()->dec_cd();
	}
	//If player's hp < 1 and wraith's hp > 0
	if (p->get_curr_hp() < 1)
		return false;

	//means player's hp > 0 and wraith's < 0
	return true;

}
*/

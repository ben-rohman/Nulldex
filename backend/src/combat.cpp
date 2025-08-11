/* Ben Rohman, benrohman3@gmail.com
 *
 * Implementations of the 'monster' class member functions. */

#include "combat.h"

/************************************** Monster Class Member Functions *********************************/
//constructor
monster::monster(well_type h, damage_type mi, damage_type ma, std::string n)
	: hp(h, h), min(mi), max(ma), nam(n)
{
}

//monster's attack
const damage_type monster::attack() const
{
	return Random::NTK(min, max);
}

//getter functions
const damage_type monster::get_min() const noexcept
{
	return min;
}

//other getter
const damage_type monster::get_max() const noexcept
{
	return max;
}

//returns the name of the monster
std::string monster::get_name() const
{
	return nam;
}

/************************************** Combat Class Member Functions ********************************/
//constructor
combat::combat(player * play, monster & monst) : pl(play), mon(monst) {}

//combat loop control function
bool combat::control()
{
	while (pl->get_curr_hp() > 0 && mon.hp.get_current() > 0)
	{
		show_stats();
		if (!player_turn())
			std::cout << RED << BOLD << "\n[ERROR] Player action failed. " << RESET << std::endl;
		if (mon.hp.get_current() > 0)
			op_turn();
	}
	return pl->get_curr_hp() > 0;
}

//public wrapper for disp_stats
void combat::show_stats()
{
	disp_stats();
}

//show the player and monster's stats
void combat::disp_stats()
{
	std::string name = pl->get_name();
	slow_print('\n' + name + "'s HP: " + std::to_string(pl->get_curr_hp()) + '/' + 
		   std::to_string(pl->get_maxhp()) + "\nMP: " + std::to_string(pl->get_curr_mp()) + 
		   '/' + std::to_string(pl->get_maxmp()) + '\n' + mon.get_name() + "'s HP: " +
		   std::to_string(mon.hp.get_current()) + '/' + std::to_string(mon.hp.get_max()));
}

//public play_turn wrapper
bool combat::player_turn()
{
	return play_turn();
}

//action control function
bool combat::play_turn()
{
	bool success {false};

	do
	{
		int choice = choose_act();
		if (choice == 1)
			success = use_weap();
		else if (choice == 2)
			success = cast_spell();
		else if (choice == 3)
			use_item();
		else
			success = false;
	}	while (!success);
	return success;
}

//returns the action the player wants to do
int combat::choose_act()
{
	int choice {0};
	std::string name = pl->get_name();

	slow_print("\n\n\t\t--------- " + name + "'s Turn ---------\n");
	do
	{
		slow_print("\nChoose an action: \n(1) Attack with a Weapon \n(2) Cast a Spell \n(3) Use an "
			   "Item \nEnter your choice here: ");
		std::cin >> choice;
		std::cin.ignore(10, '\n');

		if (std::cin.fail() || choice < 1 || choice > 3)
		{
			std::cin.clear();
			std::cerr << RED << BOLD << "\n[ERROR] Invalid input. Try again " << RESET << std::endl;
			choice = 0;
		}
	}	while (choice == 0);
	return choice;
}

//attack with a weapon option
bool combat::use_weap()
{
	const weapon * mel = pl->get_equip_weapon(static_cast<unsigned long long>(WEAPONSLOT::MELEE));
	const weapon * ran = pl->get_equip_weapon(static_cast<unsigned long long>(WEAPONSLOT::RANGED));
	damage_type dmg {0};

	if (ran)
	{
		dmg = pl->ranged_attack();
		slow_print("\nYour shot hits the " + mon.get_name() + " and deals " + std::to_string(dmg) +
			   " damage");
		mon.hp.reduce(dmg);
	}
	else if (mel)
	{
		dmg = pl->melee_attack();
		slow_print("\nYour weapon hits the " + mon.get_name() + " and deals " + std::to_string(dmg) +
			   " damage");
		mon.hp.reduce(dmg);
	}
	return true;
}

//cast a spell option
bool combat::cast_spell()
{
	int pick {0};
	damage_type dmg {0};

	const auto & sp = pl->get_abil_list();
	if (sp.empty())
	{
		std::cerr << RED << BOLD << "\n[ERROR] Ability vector is empty. " << RESET << std::endl;
		return false;
	}
	slow_print("\nChoose a spell to cast: ");
	for (size_t j = 0; j < sp.size(); ++j)
	{
		const ability * s = sp[j];
		std::string info = '\n' + std::to_string(j + 1) + ". " + s->get_name();
		if (pl->get_class()->is_cooling(s->get_name()))
			info += " [Cooldown: " + std::to_string(pl->get_class()->cd_left(s->get_name())) + ']';
		else if (s->get_cost() > pl->get_curr_mp())
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
			if (pl->get_class()->is_cooling(fin->get_name()))
				slow_print(RED + BOLD + "\n[ERROR] Spell is on cooldown. Choose another " + RESET);
			else
			{
				dmg = fin->get_hpe();
				mon.hp.reduce(dmg);
				pl->get_class()->start_cd(fin->get_name(), fin->get_cd());
				slow_print("\nYou cast " + fin->get_name() + " dealing " + std::to_string(dmg) +
					   " damgage ");
				return true;
			}
		}
		else 
			std::cerr << RED << BOLD << "\n[ERROR] Invalid input. Try again " << RESET << std::endl;
	}
	return false;
}

//use an item option
bool combat::use_item()
{
	bool used {false};
	size_t i {0};
	const auto & bp = pl->get_backpack_list();

	if (pl->get_curr_hp() == pl->get_maxhp())
	{
		std::cerr << RED << BOLD << "\n[ERROR] Health is full. No potion needed. " << RESET << std::endl;
		return false;
	}
	while (!used && i < bp.size())
	{
		item * it = bp[i];
		potion * pot = nullptr;
		if (it && it->get_data())
		{
			manager::cast_to_potion(it, pot);
			if (pot && pot->quantity > 0 && manager::use(it, pl))
			{
				slow_print("\nPotion used: " + pot->name + "\nUpdated HP: " + 
					   std::to_string(pl->get_curr_hp()) + '/' + 
					   std::to_string(pl->get_maxhp()));
				used = true;
			}
		}
		++i;
	}
	if (!used)
		std::cerr << RED << BOLD << "\n[ERROR] No useable potions found " << RESET << std::endl;
	return used;
}

//public wrapper for enemy turn
void combat::op_turn()
{
	enemy_turn();
}

//opponent's turn
void combat::enemy_turn()
{
	bool dodge {false};
	slow_print("\n\n\t\t--------- " + mon.get_name() + "'s Turn --------- \nIt attacks!");

	dodge = agility_success(pl, 15);
	if (dodge)
		slow_print("\nYou dodge out of the way narrowly...");
	else
	{
		int dmg = mon.attack();
		pl->damage(dmg);
		slow_print("\nThe attack lands, dealing " + std::to_string(dmg) + " damage");
	}
}
/************************************** Combat Helper Functions **************************************/

//			DICE

//simulates a D20 roll
int roll_d20()
{
	return rand() % 20 + 1;
}

//simulates a D12 roll
int roll_d12()
{
	return rand() % 12 + 1;
}

//simulates a D10 roll
int roll_d10()
{
	return rand() % 10 + 1;
}

//simulates a D8 roll
int roll_d8()
{
	return rand() % 8 + 1;
}

//simulates a D6 roll
int roll_d6()
{
	return rand() % 6 + 1;
}

//simulates a D4 roll
int roll_d4()
{
	return rand() % 4 + 1;
}

//			ACTIONS
//Checks if an action reliant on agility is successful
bool agility_success(player * pl, int diff)
{
	int a = pl->get_tagil();
	int roll = roll_d20();
	int total = a + roll;

	slow_print("\nYou rolled a " + std::to_string(roll) + " + agility stat (" + std::to_string(a) +
		   ") = " + std::to_string(total) + '\n');

	return total >= diff;
}

//Checks if an action reliant on strength is successful
bool strength_success(player * pl, int diff)
{
	int s = pl->get_tstr();
	int roll = roll_d20();
	int total = s + roll;

	slow_print("\nYou rolled a " + std::to_string(roll) + " + strength stat (" + std::to_string(s) +
		   ") = " + std::to_string(total) + '\n');

	return total >= diff;
}

/* Ben Rohman, benrohman3@gmail.com
 *
 * Level 4 class member functions and non-class helper function implementations		*/

#include "levels.h"

//constructor
level4::level4() : completed(false) {}

//returns completed flag's value
bool level4::is_complete() const
{
	return completed;
}

//level control function
bool level4::play(user * p)
{
	if (!p || !p->get_player())
	{
		std::cerr << RED << BOLD << "\n[ERROR] Null player in level4::play " << RESET << std::endl;
		return false;
	}

	slow_print("\n\n\t\t" + ITALIC + UNDERLINE + "========= Level 4: To Ashes =========\n" + RESET +
		   "\n\tThe forest burns... You pursue the bandits that raided the village...\n ");

	//lose conditions
	if (!scout(p))
		return false;
	if (!trap_escape())
		return false;
	if (!leader(p))
		return false;
	//if player hasn't lost in any of the phases then they win
	completed = true;
	slow_print("\n\n\tYou avenged the village...\n");
	return true;

}

//scout fight sequence, warm-up for leader fight, might have some special mechanic
bool level4::scout(user * p)
{
	player * pl = p->get_player();
	monster scout(40, 7, 10, "Bandit Scout");
	combat arena(pl, scout);
	//could somehow prompt user if they want to fight or run and use input in leader duel
	slow_print("\n\tYou see the bandit leader through the flaming trees and run towards him.\n");
	arena.op_turn();
	return arena.control();
}

//simple timed puzzle, might edit so event(like jump over log->up, branch falls->duck, etc.) output in 
//	random order and only allow {x} number failed movements before function returns false
bool level4::trap_escape()
{
	//current simple challenge
	using namespace std::chrono;

	slow_print("\n\tBurning trees fall around you as you continue to pursue the bandit leader. "
		   "\nDodge around them by entering the correct sequence before time runs out. "
		   "\nType:" + BOLD + " up \tleft \troll " + RESET + "\n\tYou have " + BOLD + UNDERLINE +
		   "15 seconds." + RESET + '\n');
	std::string input;
	auto start = high_resolution_clock::now();
	std::getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	auto end = high_resolution_clock::now();
	duration<double> elapsed = end - start;
	if (elapsed.count() > 15.0)
	{
		slow_print(RED + "\n\tToo slow... the flames engulf your body..." + RESET + '\n');
		return false;
	}
	if (input == "up left roll")
	{
		slow_print(GREEN + "\n\tYou successfully dodge the falling debris and continue to run after "
			   "after the bandit leader." + RESET + '\n');
		return true;
	}
	else
	{
		slow_print(RED + "\n\tWrong sequence... the flames engulf your body..." + RESET + '\n');
		return false;
	}
}

//final boss fight
bool level4::leader(user * p)
{
	player * pl = p->get_player();
	monster boss(65, 13, 17, "Bandit Leader");
	combat arena(pl, boss);
	slow_print("\n\n\tThe bandit leader emerges from the smoke, sword drawn.\n");
	return rage_clarity(pl, boss, arena);
}

//rage/clarity mechanic, might edit so that different outputs and effects for rage vs clarity choice randomly
//	print/execute
bool level4::rage_clarity(player * pl, monster & boss, combat & arena)
{
	if (!pl)
		return false;
	//mimic turns/combat::control logic
	while (pl->get_curr_hp() > 0 && boss.hp.get_current() > 0)
	{
		arena.show_stats();
		slow_print("\nDo you fight in RAGE or CLARITY this turn? <rage/clarity>: ");
		std::string choice;
		std::getline(std::cin, choice);
		std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

		if (choice == "rage")
		{
			slow_print("\n\tYou swing recklessly, dealing more damage but injuring yourself. "
				   "\nYou lose <3> HP.\n");
			pl->damage(3);
			boss.hp.reduce(5);
		}
		else if (choice == "clarity")
		{
			slow_print("\n\tYou fight with precision and are able to regain <4> HP but your "
				   "strikes are slower and do less damage.\n");
			pl->heal(4);
			boss.hp.increase(2);
		}
		if (!arena.player_turn())
			return false;
		if (boss.hp.get_current() > 0)
			arena.op_turn();
		pl->get_class()->dec_cd();
	}
	return pl->get_curr_hp() > 0;
}

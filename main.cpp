/* Ben Rohman, benrohman3@gmail.com, 7/3/25
 * THIS IS THE SOURCE FILE
 * Continuation of 'I'm bored lemme make a game' 
 *
 */

#include <iostream>
#include "mechanics.h"		// Game mechanics header file
#include "user.h"		// Player header file
#include "game.h"		// Frontend gameplay header file
#include "levels.h"		// header file with the level1 class declaration and combat prototype
#include "items.h"		// items header file
#include "types.h"		// just to test leveling up mechanic

int main()
{
	clear_screen();		//Clear text from screen
	
	user * mc = intros(); 	
	if (!validate_user(mc))	
		return 1;	//error if 'mc' not properly set
	
	player * pc = mc->get_player();
	if (!validate_player(pc, mc))
		return 1;	//error if 'pc' not properly set

	//set starter abilities/weapons 
	std::cout << "\n\tAttempting to add starter weapon/ability... " << std::endl;
	if (pc->get_class()->set_starters())
		std::cout << "WAHOO SUCCESS! " << std::endl;
	
	//tutorial combat
//	if (tutorial_fight(mc))
//		std::cout << "\n\n\t\t TUTORIAL FIGHT WON!! " << std::endl;
//	else
//		std::cout << "\n\n\t\t TUTORIAL FIGHT LOST... " << std::endl;
	wait();
	clear_screen();
	//player joins party
	pc->get_class()->join_party();
//	wait();

	//game lll built
	progression * game = progression::build();
	//game starts
	game->play_all(mc);




	delete mc;
	delete game;



/************************************ TESTING *********************************************/
  
/*
	//display base info
	std::cout << "\n--------- Character Info ---------\n";
	display_stats(pc);

	//display list of abilities
	std::cout << "\n--------- ABILITIES ---------\n";
	display_abils(pc);

	//display list of buffs
	std::cout << "\n--------- BUFFS ---------\n";
	display_buffs(pc);

	//add some armor and a weapon
	equip_test(pc);

	//hopefully display backpack contents
	std::cout << "\n--------- INVENTORY ---------\n";
	display_backpack(pc);

	//display before and after of player taking damage
	simulate(pc);

	//now try to display backpack again to make sure 1 less potion in it
	std::cout << "\n--------- UPDATED INVENTORY ---------\n";
	display_backpack(pc);


	//test level up abilities/armor/weapons correctly added
	for (int i = 0; i <= 8; ++i)
	{	
		display_stats(pc);
		display_abils(pc);
		display_backpack(pc);
		display_weap(pc);
		display_arm(pc);

		exp_type needed = pc->get_exp_to_next();
		pc->get_class()->give_exp(needed);
		wait();
	}	
	clear_screen();
*/

	return 0;
}

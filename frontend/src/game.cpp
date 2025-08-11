/* Ben Rohman, benrohman3@gmail.com
 *
 * Implementations of member functions for the classes in the 'derived stage types' and 'game progression' */

#include "game.h"
#include "flow_control.h"

/************************************** Derived Stage Types ************************************/

/****************************************** 'level' class **************************************/

/*destructor
level::~level()
{
	node * curr {head};
	while (curr)
	{
		delete curr->step;
		node * tmp = curr;
		curr = curr->next;
		delete tmp;
	}
	
	head = tail = nullptr;

}

//adds substages to levels
void level::add_step(stage * step)
{
	//error check
	if (!step)
		return;
	node * new_node = new node(step);
	if (!head)
		head = tail = new_node;
	else
	{
		tail->next = new_node;
		tail = new_node;
	}
}

//determines if player moves onto next stage(next node)
bool level::play(user * player)
{
	//variables
	node * curr {head};

	//error check
	if (!player)
	{
		std::cerr << "\n[ERROR] Null player passed to level::play " << std::endl;
		return false;
	}

	slow_print("\nStarting Level " + std::to_string(number) + "...", 80);

	while (curr && player->is_alive())
	{
		if (!curr->step)
		{
			std::cerr << "\n[ERROR] Null stage in level progression " << std::endl;
			return false;
		}

		curr->step->play(player);
		curr = curr->next;
	}

	completed = player->is_alive();
	return completed;

}
*/
/*************************************** 'interim' class **************************************/
/*
bool interim::play(user * play) 
{
	//Variables
//	bool found {false};			//checks if the player found/got an item from side quest

	//error check:
	if (!play)
	{
		std::cerr << "\n[ERROR] Null user passed to interim::play " << std::endl;
		return false;
	}
	
	//get the actual player object
	player * pc = play->get_player();

	//1. Display header and description of whatever the side quest is
	std::string header = 
		"\n--------- Interim Journey ---------\n";
	slow_print(header, 50);
	slow_print(description, 55);

	//where function calls for the actual side quest called
	found = BINGBONG();

	//sample outcome
	if (found)
	{
		std::string pot =
			MAGENTA + "\nYou found a potion! " + RESET + '\n';
		slow_print(pot);

	//2. create a potion
		item * potion = manager::create_potion("Healing Potion", 3u, 3u);

	//3. try to move it to player's backpack
		if (manager::move_to_backpack(potion, pc))
		{
			slow_print("\nYou pocket the Healing Potion. It might come in handy later...\n");
			return 1;		//success
		}
		else
		{
			slow_print("\nYou try to pocket the potion, but something feels wrong... \nYou "
				   "leave it...\n");
			delete potion;		//NO MEMORY LEEEAAAKKKSS
			return 0;		//failure
		}
	}

	return true;	//auto success?
}
*/
/*************************************** 'display' class **************************************/
/*
bool display::play(user * player)
{
	if (!player)
	{
		std::cerr << "\n[DISPLAY] Null player passed " << std::endl;
		return false;
	}
	slow_print(message);
	return true;
}
*/

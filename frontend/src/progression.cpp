/* Ben Rohman, benrohman3@gmail.com
 * 
 * Progression class implementations
 */

#include "game.h"
#include "levels.h"

//constructor
progression::progression() : head(nullptr), tail(nullptr) {}

//destructor
progression::~progression() 
{
	node * curr = head;
	while (curr)
	{
		node * tmp = curr;
		curr = curr->next;
		delete tmp->step;
		delete tmp;
	}
}

//add a stage/level
void progression::add_stage(stage * phase)
{
	node * new_node = new node(phase);
	if (!head)
		head = tail = new_node;
	else
	{
		tail->next = new_node;
		tail = new_node;
	}
}

//begin gameplay
void progression::play_all(user * player)
{
	node * curr = head;
	while (curr && player->is_alive())
	{
		wait();
		clear_screen();
		if (!curr->step->play(player))
		{
			std::cout << "\nLevel failed or incomplete. " << std::endl;
			return;
		}
		//Level up after a level successfully completed
		player->get_player()->get_class()->req_lvlup();
		player->get_player()->get_class()->give_exp(200);
		std::cout << "\n\n\t\tYou have leveled up! You are now level " 
			  << player->get_player()->get_class()->get_lvl() << std::endl;

		curr = curr->next;
	}
	std::cout << "\nGame over or player is dead. " << std::endl;
}

//builds the LLL gameflow
progression * progression::build()
{
	progression * game = new progression();

//	game->add_stage(new level1());
	game->add_stage(new level2());
//	game->add_stage(new level3());
//	game->add_stage(new level4());
//	game->add_stage(new level5());
//	game->add_stage(new level6());
//	game->add_stage(new level7());
//	game->add_stage(new level8());
//	game->add_stage(new level9());

	return game;
}

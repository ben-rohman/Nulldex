/* Ben Rohman, benrohman3@gmail.com
 * 
 * This is where class(es?) for monsters/opponents faced in the game will be declared
 * 
 */

#pragma once
#include <memory>			//for unique pointers
#include <cstdlib>			//for rand()
#include "types.h"
#include "mechanics.h"
#include "user.h"
#include "flow_control.h"

//#include "game.h"
//#include "flow_control.h"

/************************************ Creates and Maintains Monsters **********************************/
class monster
{
	public:
		monster(well_type h, damage_type min, damage_type max, std::string n);
		point_well hp;
		[[nodiscard]] const damage_type attack() const;
		[[nodiscard]] const damage_type get_min() const noexcept;
		[[nodiscard]] const damage_type get_max() const noexcept;
		std::string get_name() const;

	private:
		damage_type min;
		damage_type max;
		std::string nam;
		monster() = delete;
		monster(const monster &) = delete;
		monster(const monster &&) = delete;
};

/************************************ Maintains Combat Sequences **************************************/
class combat
{
	public:			//constructor
		combat(player * play, monster & monst);
		bool control();	//controls combat loop until either the player or monster are defeated
		//public wrappers
		void show_stats();
		bool player_turn();
		void op_turn();
	private:
		void disp_stats();
		bool play_turn();
		int choose_act();
		bool use_weap();
		bool cast_spell();
		bool use_item();
		void enemy_turn();

		player * pl;
		monster & mon;

};







/************************************ Helper Functions for Combat *************************************/
//		DICE ROLLS
int roll_d20();				//simulates rolling a 20 sided die
int roll_d12();			//simulates rolling a 12 sided die
int roll_d10();			//simulates rolling a 10 sided die
int roll_d8();			//simulates rolling a 8 sided die
int roll_d6();			//simulates rolling a 6 sided die
int roll_d4();			//simulates rolling a 4 sided die

//		ACTIONS
//Checks if an action reliant on agility is successful
bool agility_success(player * pl, int diff);
//Checks if an action reliant on strength is successful
bool strength_success(player * pl, int diff);
//Checks if an action reliant on intellect is successful
bool intellect_success(player * pl, int diff);

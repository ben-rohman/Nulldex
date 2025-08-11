/* Ben Rohman, benrohman3@gmail.com
 * All declarations and function prototypes */

#pragma once

#include <iostream>					//input/output
#include <string>					//string type
#include <vector>					//inventory or party members
#include <unordered_map>				//fast lookups for values using keys
#include <functional>					//for std::function (used in maps or callbacks)
#include <algorithm>					//for std::find, std::sort, etc
#include <memory>					//for smart pointers
#include <cctype>					//for std::tolower
#include <random>					//for std::mt19937, std::random_device
#include <unordered_set>				//only contains keys
#include "user.h"
#include "combat.h"
#include "flow_control.h"

/******************************* classes and structs ************************************/

//user wrapper class
class user
{
	public:
		explicit user(delegate * d) : us(d) {} 

		bool is_alive() { return (us.get_curr_hp() > 0); }
							//for non-const user objects
		player * get_player() { return &us; }
							//for const user objects
		const player * get_player() const { return &us; }

	private:
		player us;
};

//base stage class
class stage
{
	public:
		virtual bool play(user * pl) = 0;	//each derived stage will implement fxn
		virtual ~stage() = default;		//destructor
							//assumes level not completed
		virtual bool is_complete() const { return false; }
};

//node struct for the LLL
struct node
{
	stage * step;					//pointer to 'stage' class
	node * next;					//pointer to next phase of game
							//constructor
	explicit node(stage * s) : step(s), next(nullptr) {}	

};

/************************************* derived stage types ****************************
class level : public stage
{
	public:						//constructor
		explicit level(int num) : number(num), completed(false), head(nullptr), tail(nullptr) {}
		~level();				//destructor
		void add_step(stage * step);		//adds substages
		bool play(user * player) override;	//each derived stage will implement fxn
							//checks if player can move on
		bool is_complete() const override { return completed; }

	private:
		int number;				//player's current level
		bool completed;				//which levels are completed
		node * head;				//front of LLL
		node * tail;				//rear of LLL

};

//interim phase
class interim : public stage
{
	public:						//constructor
		interim(const std::string & desc) : description(desc) {}
		bool play(user * play) override;	//each derived stage will implement fxn

	private:
		std::string description;

};

//helper class for text display
class display : public stage
{
	public:						//constructor
		display(const std::string & msg) : message(msg) {}
		bool play(user * play) override;	//each derived stage will implement fxn
	
	private:
		std::string message;

};
*/
/****************************** game progression list **********************************/
class progression
{
	public:
		progression();				//constructor
		~progression();				//destructor
		void add_stage(stage * phase);		//add level to end of LLL
		void play_all(user * player);		//play through all stages in order
		static progression * build();		//builds the LLL
	private:
		node * head;
		node * tail;

};


/****************************** prototypes **********************************************/

/************************* game intro/description ***************************************/
//static std::string to_lower(std::string s);
/************************* game intro/description ***************************************/
//Game introduction/description
void welcome();
//TEMP QUIT FUNCTION TO SEE IF SHIT EXITS RIGHT
void quit();

/************************* character selection ******************************************/
//starts the character selection
user * intros();
//outputs which 1-9 = char
std::string char_menu();
//handles the logic of creating the character class variable
delegate * select_char();
//Actually creates the character class variable
delegate * create_del(const std::string & name);

/********************************* Tutorial Combat ***************************************/
//intro to scene and combat start/control
bool tutorial_fight(user * mc);
//display stats
void show_stats(player * p, monster & thug);
//action menu selection
bool char_act(player * p, monster & thug);
//helper to choose action
int choose_act(player * p, bool mag);
//option 1
bool use_weap(player * p, monster & thug);
//option 2
bool cast_spell(player * p, monster & thug);
//option 3
bool use_item(player * p);
//opponent's turn
void dummy_turn(player * p, monster & thug);
/********************************* Testers ***********************************************/
	//basic character info
//validates user * mc was properly set
bool validate_user(user * mc);
//validate that player * pc was properly set
bool validate_player(player * pc, user * mc);
//displays the character's info/stats
void display_stats(player * pc);
	//for inventory/backpack
//equips armor, weapons, and potions
void equip_test(player * pc);
//simulates the player taking damage and healing by using a potion
void simulate(player * pc);
//helper function to display backpack's content
void display_backpack(player * pc);
//Reusable item description function, determines the type of item currently being evaluated
std::string  describe_item(const item * it);
//handles the logic of using a potion and (if used) displaying its name
bool first_used(player * pc); 
//displays the player's equipped weapons
void display_weap(const player * pc);
//displays the player's equipped armor
void display_arm(const player * pc);
	//For 'abilities' list
//displays the player's entire list of abilities
void display_abils(const player * pc);
//searches for and displays a specified ability
bool specif_abil(const player * pc, const std::string & find);
	//For the 'buffs' list
//displays the player's active buffs
void display_buffs(const player * pc);
//search and display a specified buff
bool specif_buff(const player * pc, const std::string & find);



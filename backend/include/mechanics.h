/* Ben Rohman, benrohman3@gmail.com, 7/3/25
 *
 * This is where the game mechanic classes will be declared. */

	//Preprocessor directive so that this .h file is only included once per compilation
#pragma once
#include "types.h"
#include <vector>
#include <string> 

// HP class
class point_well
{
	public:
		point_well();			//Default constructor
						//Parametrized constructor
		point_well(well_type curr, well_type most);	
						//Gets the character's max hp	
		[[nodiscard]] const well_type get_max() const noexcept;
						//Gets the player's current hp	
		[[nodiscard]] const well_type get_current() const noexcept;	
						//Checks if the player's hp is full
		[[nodiscard]] const bool is_full() const noexcept;			
						//True if set successfully, false otherwise	
		void set_max(well_type new_max) noexcept;
						//If the player takes damage	
		void reduce(well_type damage) noexcept;
						//If the player's hp is being replenished
		void increase(well_type amount) noexcept;

	private: 
		well_type current;		//current hp
		well_type max;			//max hp	

};

//struct for the values of the player's stats and functions that modify them
struct core
{
	//Variables
	stat_type strength;
	stat_type intellect;
	stat_type agility;
	stat_type armor;
	stat_type elem_res;
	
	core();					//default constructor
						//parametrized constructor passed indiv variables
	core(stat_type s, stat_type i, stat_type ag, stat_type arm, stat_type eres);
	core(stat_type all);			//parametrized constructor, all var = all	
	//Functions(operator overload)
	core & operator+=(const core & rhs);
	core & operator-=(const core & rhs);
	core & operator=(const stat_type & rhs);
};

//More stat stuff -> for when they get 'buffed'
struct buff
{
	//Variables	
	std::string name;
	uint16_t duration;
	core buffed;	
	bool is_debuff;

	//Functions
	buff();					//default constructor
						//parametrized constructor with individual variables
	buff(const char * n, stat_type str = 0, stat_type intel = 0, stat_type agi = 0, 
	     stat_type arm = 0, stat_type elem_res = 0, uint16_t dur = 2u, bool debuff = false);
       						//parametrized constructor using 'core' object
	buff(const char * n, core cs, uint16_t dur = 2u, bool debuff = false);	
	buff & operator=(const char * name);	//operator overload function
};

//'stats' class
class statblock
{
	public:
						
		statblock(stat_type s = 1, stat_type i = 1, stat_type a = 1, stat_type arm = 0, 
			stat_type e = 0);
		//getter functions for base stats
		stat_type get_bstr();		
		stat_type get_bint();		
		stat_type get_bagi();		
		stat_type get_barm();		
		stat_type get_belem_res();		
		//getter functions for total stats from buffs
		stat_type get_tstr();		
		stat_type get_tint();		
		stat_type get_tagi();		
		stat_type get_tarm();		
		stat_type get_telem_res();		
	protected:
		//Variables
		std::vector<buff> buffs;	//records a players buffs
		//functions
		void add_or_refresh(buff b);	//adds a buff	
						//Function to increase stats
		void increase_stats(stat_type s = 0, stat_type i = 0, stat_type a = 0, 
				    stat_type arm = 0, stat_type e = 0);
		void increase_stats(core cs);	//Function to increase stats that is passed 
						//	'core' object

	private:
		//Variables
		core base;			//'core' object for base stats
		core total;			//'core' object for buffed stats

		//Functions
		void recalculate();

};

//defines who the ability affects
enum class abil_target
{
	SELF,			//player
	ALLY,			//party member
	ENEMY			//monster
};

//ability scalers
enum class abil_scaler
{
	NONE,			//ability doesn't scale with stats
	STR,			//strength
	INT,			//intellect
	AGI			//agility
};

class ability
{
	public:
		ability(std::string name = "unnamed", uint32_t hpe = 1u, buff * b = nullptr,
			uint32_t cost = 0u, uint32_t cd = 1u, abil_target t = abil_target::SELF,
			abil_scaler s = abil_scaler::NONE);
		~ability();

		uint32_t remain_cd;

		[[nodiscard]] const std::string get_name() const noexcept;
		[[nodiscard]] const uint32_t get_cd() const noexcept;
		[[nodiscard]] const uint32_t get_hpe() const noexcept;
		[[nodiscard]] const buff * get_buff() const noexcept;
		[[nodiscard]] const uint32_t get_cost() const noexcept;
		[[nodiscard]] const abil_target get_target() const noexcept;
		[[nodiscard]] const abil_scaler get_scaler() const noexcept;

	private:
		std::string name;
		uint32_t hpe;
		buff * given;
		uint32_t cost;
		uint32_t cd;
		abil_target target;
		abil_scaler scaler;

};

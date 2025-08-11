/* Ben Rohman, benrohman3@gmail.com
 *
 * This is where all the player/user mechanic classes will be
 */

#pragma once
#include "items.h"
#include "mechanics.h"
#include "types.h"
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

/****************************************** MACROS *****************************************************/

//Constructor macro
#define CONSTRUCT \
hp = std::make_unique<point_well>(base_hp, base_hp); \
hp->set_max(base_hp); \
hp->increase(base_hp); \
mp = std::make_unique<point_well>(base_mp, base_mp); \
mp->set_max(base_mp); \
mp->increase(base_mp); \
increase_stats(base_str, base_int, base_agi);

//Level up macro
#define LEVEL_UP \
hp->set_max((well_type)((base_hp / 2.f) + hp->get_max())); \
hp->increase((well_type)(base_hp / 2.f)); \
if (mp) \
{ \
	mp->set_max((well_type)((base_mp / 2.f) + hp->get_max())); \
	mp->increase((well_type)(base_mp / 2.f)); \
} \
increase_stats((stat_type)((base_str + 1u) / 2.f), (stat_type)((base_int + 1u) / 2.f), \
	       (stat_type)((base_agi + 1u) / 2.f));


/****************************************** CLASSES ****************************************************/

//Level up system class
class delegate : public statblock
{
	public:
		//Variables
					//Reach level 2 with 100 EXP
		static constexpr exp_type lvl2 = 100u;
					//Unique 'point_well' pointers
		std::unique_ptr<point_well> hp;
		std::unique_ptr<point_well> mp;
		std::vector<ability*> abilities;
		std::vector<buff> buf;
		//Functions
		delegate();		//Default constructor
		
		//overrides		destructor	
		virtual ~delegate() = 0;
					//Ensures character previews displayed when called
		virtual std::string get_name() const = 0;
					//Ensure's that the character's preview is read
		virtual void intro() const = 0;
					//Ensures that a backstory is displayed for chosen character
		virtual void disp_backstory() const = 0;
					//Equips starter weapons or abilities
		virtual bool set_starters() = 0;
					//Ensures that each character's dialogue joining the quest is displayed
		virtual void join_party() const = 0;
					//Ensures that each character's good ending is displayed
		virtual void good_ending() const = 0;
					//Ensures that each character's bad ending is displayed
		virtual void bad_ending() const = 0;
					
		//getters
		[[nodiscard]] lvl_type get_lvl() const noexcept;
		[[nodiscard]] exp_type get_exp() const noexcept;
		[[nodiscard]] exp_type get_exp_to_next()const noexcept;

		//Modifiers
		void give_exp (const exp_type amot) noexcept;

		//Functions for ability cooldowns
					//Starts the ability cooldown
		void start_cd(const std::string & sp, int cd_dur);
		void dec_cd();		//Decrements the ability's cooldown
					//Checks if ability is on cooldown
		bool is_cooling(const std::string & sp) const;
					//Returns the number of turns until ability can be used.
		int cd_left(const std::string & sp) const;
		
		//Functions so that a templated wrapper can add starter weap/abil in character constructors
		void set_owner(player * p) {owner = p;}
		player * get_owner() const {return owner; }

		//Public 'level_up' wrapper
		void req_lvlup() noexcept;
	protected:
		player * owner;		//added so starter weapons/abilities added in character constructors

	private:	
		//Variables	
		lvl_type current_level;	//Player's current level
		exp_type current_exp;	//Player's current amount of EXP
		exp_type exp_to_next;	//EXP needed to level up
					//Stores ability names and how long until they can be used
		std::unordered_map<std::string, int> cds;
		//Functions	
		virtual void level_up() noexcept = 0;
		[[nodiscard]] const bool check_level() noexcept;
		
};

//Class for the actual user
class player final 
{
	public:
		player(delegate * pc);	//Parametrized constructor
		~player();		//Destructor
		//An excessive amount of 'getter functions	
		[[nodiscard]] const lvl_type get_lvl() const noexcept;	
		[[nodiscard]] const exp_type get_exp() const noexcept;	
		[[nodiscard]] const exp_type get_exp_to_next() const noexcept;
		[[nodiscard]] const bool is_maxhp() const noexcept;	
		[[nodiscard]] const well_type get_curr_hp() const noexcept;
		[[nodiscard]] const well_type get_maxhp() const noexcept;	
		[[nodiscard]] const well_type get_curr_mp() const noexcept;
		[[nodiscard]] const well_type get_maxmp() const noexcept;	
		[[nodiscard]] const std::string get_name() const noexcept;
		delegate * get_class() const { return pcclass; }
		//base stat getter functions	
		[[nodiscard]] const stat_type get_bstr() const noexcept;	
		[[nodiscard]] const stat_type get_bint() const noexcept;	
		[[nodiscard]] const stat_type get_bagi() const noexcept;	
		[[nodiscard]] const stat_type get_barm() const noexcept;
		[[nodiscard]] const stat_type get_belem_res() const noexcept;
		//total stat getter functions
		[[nodiscard]] const stat_type get_tstr() const noexcept;
		[[nodiscard]] const stat_type get_tint() const noexcept;
		[[nodiscard]] const stat_type get_tagil() const noexcept;
		[[nodiscard]] const stat_type get_tarm() const noexcept;
		[[nodiscard]] const stat_type get_telem_res() const noexcept;
		//item getter functions
		[[nodiscard]] const std::vector<ability*> get_abil_list() const noexcept;
		[[nodiscard]] const std::vector<buff> get_buff_list() const noexcept;	
		[[nodiscard]] const std::vector<item*> get_backpack_list() const noexcept;
		[[nodiscard]] const armor * get_equip_armor(unsigned long long i) const noexcept;
		[[nodiscard]] const weapon * get_equip_weapon(unsigned long long i) const noexcept;
		[[nodiscard]] const damage_type melee_attack() const noexcept;
		[[nodiscard]] const damage_type ranged_attack() const noexcept;
		//modifiers		
		void gain_exp(exp_type amt);
		void damage(well_type amt);
					//Adjusts player's HP if healed
		void heal(well_type amt);
		void apply_buff(buff b);//Uses 'delegate' pointer to access 'statblock' and 'buff'
	private:
		delegate * pcclass;	//pointer to 'delegate' class
					//array for equipped armor
		item * equipped_armor[(unsigned long long)ARMORSLOT::NUM_SLOTS];
					//array for equipped weapons
		item * equipped_weapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];	
					//lil sack for knickknacks
		std::vector<item*> backpack;
					//moves an item to the character's backpack
		void move_to_backpack(item * to_move) noexcept;
		void cleanup() noexcept;//option to get rid of items/stuff in the sack
		
		//prevent DEFAULT, MOVE, and COPY constructors
		player() = delete;
		player(const player &) = delete;
		player(const player &&) = delete;
		friend class manager;	

};

//Gray
class rogue : public delegate
{
	public:
		//Base stats
		inline static constexpr well_type base_hp = (well_type) 12u;
		inline static constexpr well_type base_mp = (well_type) 8u;	
		static const stat_type base_str = (stat_type) 3u;
		static const stat_type base_int = (stat_type) 4u;
		static const stat_type base_agi = (stat_type) 5u;

		rogue();		//Default constructor
					//Returns the 'rogue' class name	
		std::string get_name() const override;
					//Display's Gray's preview
		void intro() const override;
					//Displays Gray's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Gray's dialogue joining the party
		void join_party() const override;
					//Displays Gray's good ending
		void good_ending() const override;
					//Displays Gray's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};

//Aurora
class wizard : public delegate
{
	public:
		//Base stats
		inline static constexpr well_type base_hp = (well_type) 10u;
		inline static constexpr well_type base_mp = (well_type) 11u;
		static const stat_type base_str = (stat_type) 2u;
		static const stat_type base_int = (stat_type) 4u;
		static const stat_type base_agi = (stat_type) 2u;

		wizard();		//Default constructor
					//Returns the 'wizard' class name
		std::string get_name() const override;
					//Display's Aurora's preview
		void intro() const override;
					//Display's Aurora's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Aurora's dialogue joining the party
		void join_party() const override;
					//Displays Aurora's good ending
		void good_ending() const override;
					//Displays Aurora's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};

//Annie
class cleric : public delegate
{
	public:
			
		//Base stats
		inline static constexpr well_type base_hp = (well_type) 14u;
		inline static constexpr well_type base_mp = (well_type) 9u;
		static const stat_type base_str = (stat_type) 1u;
		static const stat_type base_int = (stat_type) 3u;
		static const stat_type base_agi = (stat_type) 1u;

		//Functions
		cleric();		//Default constructor
					//Returns the character name
		std::string get_name() const override;
					//Display's Annie's preview	
		void intro() const override;
					//Display's Annie's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Annie's dialogue joining the party
		void join_party() const override;
					//Displays Annie's good ending
		void good_ending() const override;
					//Displays Annie's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};

//Tav
class paladin : public delegate
{
	public:
		//base stats
		inline static constexpr well_type base_hp = (well_type) 18u;
		inline static constexpr well_type base_mp = (well_type) 3u;
		static const stat_type base_str = (stat_type) 6u;
		static const stat_type base_int = (stat_type) 4u;
		static const stat_type base_agi = (stat_type) 3u;

		//Functions
		paladin();		//default constructor
					//returns the character name
		std::string get_name() const override;
					//Displays Tav's preview	
		void intro() const override;
					//Displays Tav's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Tav's dialogue joining the party
		void join_party() const override;
					//Displays Tav's good ending
		void good_ending() const override;
					//Displays Tav's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};

//Sky
class sorcerer : public delegate
{
	public:
		//base stats
		inline static constexpr well_type base_hp = (well_type) 12u;
		inline static constexpr well_type base_mp = (well_type) 14u;
		static const stat_type base_str = (stat_type) 3u;
		static const stat_type base_int = (stat_type) 4u;
		static const stat_type base_agi = (stat_type) 4u;

		//Functions
		sorcerer();		//default constructor
					//returns the character name
		std::string get_name() const override;
					//Displays Sky's preview	
		void intro() const override;
					//Displays Sky's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Sky's dialogue joining the party
		void join_party() const override;
					//Displays Sky's good ending
		void good_ending() const override;
					//Displays Sky's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};

//Maeve
class bard : public delegate
{
	public:
		//base stats
		inline static constexpr well_type base_hp = (well_type) 13u;
		inline static constexpr well_type base_mp = (well_type) 5u;
		static const stat_type base_str = (stat_type) 4u;
		static const stat_type base_int = (stat_type) 3u;
		static const stat_type base_agi = (stat_type) 3u;

		//Functions
		bard();			//base constructor
					//returns the character name
		std::string get_name() const override;
					//Displays Maeve's preview	
		void intro() const override;
					//Display's Maeve's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Maeve's dialogue joining the party
		void join_party() const override;
					//Displays Maeve's good ending
		void good_ending() const override;
					//Displays Maeve's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};

//Ivy
class monk : public delegate
{
	public: 
		//base stats
		inline static constexpr well_type base_hp = (well_type) 8u;
		inline static constexpr well_type base_mp = (well_type) 3u;
		static const stat_type base_str = (stat_type) 3u;
		static const stat_type base_int = (stat_type) 2u;
		static const stat_type base_agi = (stat_type) 4u;

		//Functions
		monk();			//base constructor
					//returns the character name
		std::string get_name() const override;
					//Displays Ivy's preview	
		void intro() const override;
					//Display Ivy's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Ivy's dialogue joining the party
		void join_party() const override;
					//Displays Ivy's good ending
		void good_ending() const override;
					//Displays Ivy's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};

//Rory
class barbarian : public delegate
{
	public:
		//Variables	
			//Base stats
		inline static constexpr well_type base_hp = (well_type) 16u;
		inline static constexpr well_type base_mp = (well_type) 1u;
		static const stat_type base_str = (stat_type) 6u;
		static const stat_type base_int = (stat_type) 2u;
		static const stat_type base_agi = (stat_type) 2u;
	
		//Functions	
		barbarian();		//Default constructor
					//Returns the 'barbarian' class name
		std::string get_name() const override;
					//Displays Rory's preview	
		void intro() const override;
					//Displays Rory's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Rory's dialogue joining the party
		void join_party() const override;
					//Displays Rory's good ending
		void good_ending() const override;
					//Displays Rory's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;
};

//Ben
class artificer : public delegate
{
	public:
		//base stats
		inline static constexpr well_type base_hp = (well_type) 9u;
		inline static constexpr well_type base_mp = (well_type) 4u;
		static const stat_type base_str = (stat_type) 3u;
		static const stat_type base_int = (stat_type) 9u;
		static const stat_type base_agi = (stat_type) 3u;

		//functions
		artificer();		//default constructor
					//returns the character name
		std::string get_name() const override;
					//Displays Ben's preview
		void intro() const override;
					//Displays Ben's backstory
		void disp_backstory() const override;
					//Sets starter weapon/ability
		bool set_starters() override;
					//Displays Ben's dialogue joining the party
		void join_party() const override;
					//Displays Ben's good ending
		void good_ending() const override;
					//Displays Ben's bad ending
		void bad_ending() const override;

	private:
		void level_up() noexcept override;

};


/********************************* Helper Prototypes *************************************************/
//overload for player *
inline player * extract_player(const player * p)
{
	return const_cast<player *>(p);
}

//overload for delegate *
inline player * extract_player(const delegate * d)
{
	return d ? const_cast<player *>(d->get_owner()) : nullptr;
}

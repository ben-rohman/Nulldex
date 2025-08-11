/* Ben Rohman, benrohman3@gmail.com
 *
 * This is where all of the declarations for the 'items' aspect of the game will be
 *
 */

#pragma once
#include <typeinfo>			//inspects TYPE of object at RUNTIME and its relationships
					//	good for INHERITANCE, pointers, or references to base
					//	classes
#include "mechanics.h"

class player;


/************************************ ENUMS **********************************************************/

//user-defined armor class(type of armor)
enum class ARMORSLOT
{
	HELMET,
	CHEST,
	LEGS,
	BOOTS,
	ARMS,
	RING1,			//gay people and they rings am i right fellas?
	RING2,
	NECK,
	NUM_SLOTS		//number of slots for arrays of armor slots

};

//user-defined weapons class(type of weapon)
enum class WEAPONSLOT
{
	MELEE,
	RANGED,
	NUM_SLOTS
};

/************************************ ITEMS **********************************************************/
//maintainer class for items
class item_delegate
{
	public:
		//Variables
		std::string name;
	
	protected:
		virtual ~item_delegate() = 0; 
		item_delegate(std::string nam) : name(nam) {}
		friend class item;

};


//potions items
class potion final: public item_delegate
{
	public:
		//Variables	
		well_type heal_amount;
		item_count quantity;
		//Functions
		~potion();		//destructor
		const buff * get_bufs() const;
		void set_buff(buff * new_buff);
	private:
		buff * bufs;
					//parametrized constructor
		potion(std::string n, well_type hp_heal = 1u, item_count num = 1u, 
		       buff * b = nullptr); 
		friend class manager;
};

//item class
class item final
{
	public:
					//Returns a pointer to a 'item_delegate' object
		const item_delegate * get_data() const {return data; }
		bool mark_to_delete() const;
		bool ref_gone() const { return marked_gone; }
	private:
		//Variables
		item_delegate * data;	//'item_delegate' pointer
		bool marked = false;	//items to get rid of in backpack	
		bool marked_gone = false;	
		//Functions
		~item();		//Destructor
		item(item_delegate * item) : data(item) {}
		//Friends
		friend class manager;
		
		//friend std::ostream & operator<<(std::ostream & os, const item & t);

};

//maintainer class for equipment
class equipment : public item_delegate
{
	public:
		//Variables
		const std::uint32_t unique_id;
		core stats;		//'core' struct object
	
	protected:
		virtual ~equipment() = 0; 
		equipment(std::string name, core cs);

};

//creates the actual armor
class armor final : public equipment
{
	public:
		//Variables
				//'ARMOR' object
		ARMORSLOT slot;

	private:
				//constructor
		armor(std::string name, core cs, ARMORSLOT s);
				//prevents the DEFAULT constructor
		armor() = delete;	
				//prevents the COPY constructor
		armor(const armor &) = delete;
				//prevents the MOVE constructor
		armor(const armor &&) = delete;
		~armor();
		friend class manager;
};

//creates the actual weapon
class weapon final : public equipment
{
	public:
		//Variableg
				//'WEAPONSLOT' object
		WEAPONSLOT slot;
				//min damage weapon can do
		damage_type min_damage;
				//max damage weapon can do
		damage_type max_damage;
		bool is_2h;	//is it 2 handed?
	private:
		weapon(std::string name, core cs, WEAPONSLOT s, damage_type min, damage_type max,
		       bool two_handed = false);

		weapon() = delete;
		weapon(const weapon &) = delete;
		weapon(const weapon &&) = delete;
		~weapon();	
		friend class manager;

};

//creates the items for the 'item' class
class manager
{
	public:
					//create armor
		static item * create_armor(std::string name, core cs, ARMORSLOT slot);
					//dynamic casts armor
		static void cast_to_armor(const item * in, armor *& out);
					//checks if an item is armor
		static bool is_armor(const item * in);
					//create weapon
		static item * create_weapon(std::string name, core cs, WEAPONSLOT slot, damage_type min,
					    damage_type max, bool two_handed = false);
					//dynamic casts weapon
		static void cast_to_weapon(const item * in, weapon *& out);
					//checks if item weapon
		static bool is_weapon(const item * in);
					//make at least 1 potion
		static item * create_potion(std::string name, well_type = 1u, item_count num = 1u,
			       		    buff * b = nullptr);
					//dynamic casts a potionf
		static void cast_to_potion(const item * in, potion *& out);
					//checks if item is a potion
		static bool is_potion(const item * in);	
					//equip armor/weapon, if prev equipped -> move to backpack
		static bool equip_item(item * to_equip, player * p_char);
					//use the item
		static bool use(item * to_use, player * p_char);
					//move the item to the character's backpack
		static bool move_to_backpack(item * item, player * p_char);
					//deletes an item from player's backpack
		static void delete_item(item *& to_delete);
		template <typename T>	//template wrapper
		static bool equip(item * to_equip, T * entity)
		{
			player * p = extract_player(entity);
			if (!p)
				return false;
			return equip_item(to_equip, p);
		}
};


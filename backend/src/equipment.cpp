/* Ben Rohman, benrohman3@gmail.com
 *
 * Where all the member functions in 'items.h' will be implemented
 *
 */

#include "items.h"
#include "user.h"
#include "mechanics.h"

/********************************* 'potion' CLASS ************************************************/
//constructor
potion::potion(std::string n, well_type hp_heal, item_count num, buff * b)
	: item_delegate(n), heal_amount(hp_heal), quantity(num), bufs(b) {}

//destructor
potion::~potion()
{
	if (bufs)
	{
		delete bufs;
		bufs = nullptr;
	}
}

//buff getter function
const buff * potion::get_bufs() const 
{
	return bufs;
}

//sets a new buff
void potion::set_buff(buff * new_buff)
{
	if (bufs)
	{
		delete bufs;
		bufs = nullptr;
	}
	bufs = new_buff;
}

/********************************* 'manager' CLASS ***********************************************/
//create armor
[[nodiscard]] item * manager::create_armor(std::string name, core cs, ARMORSLOT slot)
{
	item * temp = new item(new armor(name, cs, slot));
	return temp;
}

//helper function, dynamic casts stuff
void manager::cast_to_armor(const item * in, armor *& out)
{
	if (!in)
		return;
	out = dynamic_cast<armor*>(in->data);
}

//checks if item is armor
bool manager::is_armor(const item * in)
{
	if (dynamic_cast<armor*>(in->data))
		return true;
	return false;
}

//create a weapon
[[nodiscard]] item * manager::create_weapon(std::string name, core cs, WEAPONSLOT slot, damage_type min, 
				     damage_type max, bool two_handed)
{
	item * temp = new item(new weapon(name, cs, slot, min, max, two_handed));
	return temp;
}

//dynamic cast to weapon
void manager::cast_to_weapon(const item * in, weapon *& out)
{
	if (!in)
		return;
	out = dynamic_cast<weapon*>(in->data);
}

//checks if an item is a weapon
bool manager::is_weapon(const item * in)
{
	if (dynamic_cast<weapon*>(in->data))
		return true;
	return false;
}

//create a potion
[[nodiscard]] item * manager::create_potion(std::string name, well_type heal, item_count quant, 
					    buff * buf)
{
	item * temp = new item(new potion(name, heal, (quant == 0) ? 1 : quant, buf));
	return temp;
}

//dynamic cast to potion
void manager::cast_to_potion(const item * in, potion *& out)
{
	if (!in)
		return;
	out = dynamic_cast<potion*>(in->data);
}

//check if an item is a potion
bool manager::is_potion(const item * in)
{
	if (dynamic_cast<potion*>(in->data))
		return true;
	return false;
}

//equips a weapon or piece of armor, returns true if successful and failure otherwise
//	if item previously equipped in that slot, it's moved to the character's backpack
bool manager::equip_item(item * to_equip, player * p_char)
{	//bad data passed to fxn
	if (!to_equip->get_data() || !to_equip || !p_char)
		return false;
	//if potion don't equip
	if (is_potion(to_equip))
		return false;
	//if item = armor
	armor * arm = dynamic_cast<armor*>(to_equip->data);
	if (arm)
	{
		unsigned long long slot_num = (unsigned long long)arm->slot;
		if (p_char->equipped_armor[slot_num])
		{				
						//mark as backpack ref gone
			p_char->equipped_armor[slot_num]->marked_gone = false;
						//move old item to backpack
			move_to_backpack(p_char->equipped_armor[slot_num], p_char);
						//equip new item
			p_char->equipped_armor[slot_num] = to_equip;
			to_equip->marked_gone = true;
		}
		else				//if item not recently equipped just equip immediately
		{
			p_char->equipped_armor[slot_num] = to_equip;
			to_equip->marked_gone = true;
		}
		p_char->cleanup();
		return true;
	}

	weapon * weap = dynamic_cast<weapon*>(to_equip->data);
	if (weap)
	{
		unsigned long long slot_num = (unsigned long long)weap->slot;
		if (p_char->equipped_weapons[slot_num])
		{
			p_char->equipped_weapons[slot_num]->marked_gone = false;
			move_to_backpack(p_char->equipped_weapons[slot_num], p_char);
			p_char->equipped_weapons[slot_num] = to_equip;
			to_equip->marked_gone = true;
		}
		else
		{
			p_char->equipped_weapons[slot_num] = to_equip;
			to_equip->marked_gone = true;
		}
		p_char->cleanup();
		return true;
	}

	return false;
}

//uses a potion
bool manager::use(item * to_use, player * p_char)
{
	if (!to_use->get_data() || !to_use || !p_char)
		return false;

	potion * pot {nullptr};
	cast_to_potion(to_use, pot);

	if (pot)
	{	//apply buff if it has one
		if (pot->bufs)
		{
			if (pot->bufs->is_debuff)
				p_char->damage(pot->heal_amount);
			p_char->apply_buff(*pot->bufs);
		}
		else
		{
			if (p_char->is_maxhp())
				return false;
			else
				p_char->heal(pot->heal_amount);
		}
		//potion used -> reduce quantity
		pot->quantity--;

		//if last one used, mark it to be deleted then get rid of it
		if (pot->quantity == 0)
		{
			to_use->marked = true;
			p_char->cleanup();
		}
		return true;
	}
	return false;
}

//move an item to the character's backpack
bool manager::move_to_backpack(item * to_move, player * p_char)
{
	if (!to_move->get_data() || !to_move || !p_char)
		return false;
	p_char->move_to_backpack(to_move);
	return true;
}

//deletes item from backpack
void manager::delete_item(item *& to_delete)
{
	delete to_delete;
	to_delete = nullptr;
}

/*template wrapper
template <typename T>
bool manager::equip(item * to_equip, T * entity)
{
	player * p = extract_player(entity);
	if (!p)
		return false;
	return equip_item(to_equip, p);
}
*/
/************************************* 'item' CLASS ***********************************************/
//destructor
item::~item()
{
	if (data)
	{
		delete data;
		data = nullptr;
	}
}

//marks an item as good to be deleted
bool item::mark_to_delete() const
{
	return marked;
}

/************************************* 'equipment' CLASS ******************************************/

static std::uint32_t EQUIP_IDITERATOR = 0u;

equipment::equipment(std::string name, core cs)
	: item_delegate(name), unique_id(++EQUIP_IDITERATOR), stats(cs) {}
equipment::~equipment() 
{}

/************************************* 'armor' CLASS **********************************************/
//constructor
armor::armor(std::string name, core cs, ARMORSLOT s)
	: equipment(name, cs), slot(s) {}

//destructor
armor::~armor() {}

/************************************* 'weapon' CLASS *********************************************/
//constructor
weapon::weapon(std::string name, core cs, WEAPONSLOT s, damage_type min, damage_type max, 
		bool two_handed)
	: equipment(name, cs), slot(s), min_damage(min), max_damage(max), is_2h(two_handed) {}

weapon::~weapon()
{}

/**********************************'item_delegate' CLASS ******************************************/
//virtual default constructor
item_delegate::~item_delegate() {}
	
/************************************* output format *********************************************/
/*std::ostream & operator<<(std::ostream & os, const item & t)
{
	armor * temp1 = dynamic_cast<armor*>(t.data);
	if (temp1)
		return os << temp1->name << "(Armor: " << temp1->stats.armor << ", Resistance: " 
			  << temp1->stats.elem_res <<')';

	weapon * temp2 = dynamic_cast<weapon*>(t.data);
	if (temp2)
		return os << temp2->name << "(Damage: " << temp2->min_damage << '-' << temp2->max_damage
			  << ')';

	potion * temp3 = dynamic_cast<potion*>(t.data);
	if (temp3)
		return os << temp3->name << '(' << temp3->quantity << ')';

	return os;
}*/

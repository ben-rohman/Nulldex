/* Ben Rohman, benrohman3@gmail.com
 *
 * Implementation of the 'player' class functions
 */

#include "user.h"
#include "items.h"

//Parametrized constructor
player::player(delegate * pc) : pcclass(pc)
{
	//set delegate's back reference ptr
	if (pcclass)
		pcclass->set_owner(this);

	auto i = 0;
	for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++)
		equipped_armor[i] = nullptr;
	for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
		equipped_weapons[i] = nullptr;
}

//Destructor
player::~player()
{
	delete pcclass;
	pcclass = nullptr;

	auto i = 0;
	for (i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++)
	{
		if (equipped_armor[i])
			manager::delete_item(equipped_armor[i]);
	}
	for (i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
	{
		if (equipped_weapons[i])
			manager::delete_item(equipped_weapons[i]);
	}
}

/********************* An unholy amount of 'get' functions ***************************************/

//Function that returns the user's current level
const lvl_type player::get_lvl() const noexcept
{
	return pcclass->get_lvl();
}

//Function that returns the user's current amount of EXP
const exp_type player::get_exp() const noexcept
{
	return pcclass->get_exp();
}

//Function that returns the amount of EXP needed to level up
const exp_type player::get_exp_to_next() const noexcept
{
	return pcclass->get_exp_to_next();
}

const bool player::is_maxhp() const noexcept
{
	return pcclass->hp->is_full();
}

//Function that returns the player's current amount of HP
const well_type player::get_curr_hp() const noexcept
{
	return pcclass->hp->get_current();
}

//Function that returns the player's chosen 'class's max HP
const well_type player::get_maxhp() const noexcept
{
	return pcclass->hp->get_max();
}

//Function that returns the player's current amount of MP
const well_type player::get_curr_mp() const noexcept
{
	if (pcclass->mp)
		return pcclass->mp->get_current();
	return 0;
}

//Function that returns the player's chosen 'class's max MP
const well_type player::get_maxmp() const noexcept
{
	if (pcclass->mp)
		return pcclass->mp->get_max();
	return 0;
}

//Returns the name of the character
const std::string player::get_name() const noexcept
{
	return pcclass->get_name();
}

//Function that returns the player's current 'Strength' stat
const stat_type player::get_bstr() const noexcept
{
	return pcclass->get_bstr();
}

//Function that returns the player's current 'Intellect' stat
const stat_type player::get_bint() const noexcept
{
	return pcclass->get_bint();
}

//Function that return's the player's current 'Agility' stat
const stat_type player::get_bagi() const noexcept
{
	return pcclass->get_bagi();
}

//Function that return's the player's current 'Armor' stat
const stat_type player::get_barm() const noexcept
{
	return pcclass->get_barm();
}

//Function that returns the player's current 'Elemental Resistance' stat
const stat_type player::get_belem_res() const noexcept
{
	return pcclass->get_belem_res();
}

//Function that returns the player's total 'Strength' stat after buffs
const stat_type player::get_tstr() const noexcept
{
	//Variables
	stat_type from_armor {0};
	stat_type from_weapons {0};
	
	{
		armor * ar = nullptr;
		for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++)
		{
			manager::cast_to_armor(equipped_armor[i], ar);
			if (ar)
				from_armor += ar->stats.strength;	
			ar = nullptr;
		}
	}
	{
		weapon * we {nullptr};
		for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
		{		
			manager::cast_to_weapon(equipped_weapons[i], we);	
			if (we)
				from_weapons += we->stats.strength;
			we = nullptr;	
		}	
	}
	return pcclass->get_tstr() + from_armor + from_weapons;
}

//Function that returns the player's total 'Intellect' stat after buffs
const stat_type player::get_tint() const noexcept
{
	//Variables
	stat_type from_armor {0};
	stat_type from_weapons {0};
	
	{
		armor * ar {nullptr};
		for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++)
		{
			manager::cast_to_armor(equipped_armor[i], ar);
			if (ar)
				from_armor += ar->stats.intellect;	
			ar = nullptr;
		}
	}
	{
		weapon * we {nullptr};
		for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
		{		
			manager::cast_to_weapon(equipped_weapons[i], we);	
			if (we)
				from_weapons += we->stats.intellect;
			we = nullptr;	
		}	
	}
	return pcclass->get_tint() + from_armor + from_weapons;
}

//Function that returns the player's total 'Agility' stat after buffs
const stat_type player::get_tagil() const noexcept
{
	//Variables
	stat_type from_armor {0};
	stat_type from_weapons {0};

	{
		armor * ar {nullptr};
		for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++)
		{
			manager::cast_to_armor(equipped_armor[i], ar);
			if (ar)
				from_armor += ar->stats.agility;	
			ar = nullptr;
		}
	}
	{
		weapon * we {nullptr};
		for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
		{		
			manager::cast_to_weapon(equipped_weapons[i], we);	
			if (we)
				from_weapons += we->stats.agility;
			we = nullptr;	
		}	
	}
	return pcclass->get_tagi() + from_armor + from_weapons;
}

//Function that returns the player's total 'Armor' stat after buffs
const stat_type player::get_tarm() const noexcept
{
	//Variables
	stat_type from_armor {0};
	stat_type from_weapons {0};

	{
		armor * ar {nullptr};
		for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++)
		{
			manager::cast_to_armor(equipped_armor[i], ar);
			if (ar)
				from_armor += ar->stats.armor;	
			ar = nullptr;
		}
	}
	{
		weapon * we {nullptr};
		for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
		{		
			manager::cast_to_weapon(equipped_weapons[i], we);	
			if (we)
				from_weapons += we->stats.armor;
			we = nullptr;	
		}	
	}
	return pcclass->get_tarm() + from_armor + from_weapons;
}

//Function that returns the player's total 'Elemental Resistance' stat after buffs
const stat_type player::get_telem_res() const noexcept
{
	//Variables
	stat_type from_armor {0};
	stat_type from_weapons {0};

	{
		armor * ar {nullptr};
		for (auto i = 0; i < (unsigned long long)ARMORSLOT::NUM_SLOTS; i++)
		{
			manager::cast_to_armor(equipped_armor[i], ar);
			if (ar)
				from_armor += ar->stats.elem_res;	
			ar = nullptr;
		}
	}
	{
		weapon * we {nullptr};
		for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
		{		
			manager::cast_to_weapon(equipped_weapons[i], we);	
			if (we)
				from_weapons += we->stats.elem_res;
			we = nullptr;	
		}	
	}
	return pcclass->get_telem_res() + from_armor + from_weapons;
}

//Function that adjusts the player's amount of EXP if any gained
void player::gain_exp(exp_type amt) 
{
	pcclass->give_exp(amt);
}

//Function that adjusts the player's HP if damage taken
void player::damage(well_type amt) 
{
	pcclass->hp->reduce(amt);
}

//Function that adjusts the player's HP if they are healed
void player::heal(well_type amt)
{
	pcclass->hp->increase(amt);
}

//Returns a list of the player's abilities
[[nodiscard]] const std::vector<ability*> player::get_abil_list() const noexcept
{
	return pcclass->abilities;
}

//Returns a list of the buffs applied to the character
const std::vector<buff> player::get_buff_list() const noexcept
{
	return pcclass->buf;
}

//Returns a list of items/things in the player's backpack
const std::vector<item*> player::get_backpack_list() const noexcept
{
	return backpack;
}

//Returns something about armor idefk
const armor * player::get_equip_armor(unsigned long long i) const noexcept
{
	if (!equipped_armor[i])
		return nullptr;
	return (dynamic_cast<const armor*>(equipped_armor[i]->get_data()));
}

//Returns something about weapons ig
const weapon * player::get_equip_weapon(unsigned long long i) const noexcept
{
	if (!equipped_weapons[i])
		return nullptr;
	return (dynamic_cast<const weapon*>(equipped_weapons[i]->get_data()));
}

//Modifies hp if damage taken from melee weapon
const damage_type player::melee_attack() const noexcept
{
	damage_type dmg {0};

	const weapon * equipped = get_equip_weapon((unsigned long long)WEAPONSLOT::MELEE);
	//if weapon exists get damage else b dmg = 0
	if (equipped)
		dmg = Random::NTK(equipped->min_damage, equipped->max_damage);
	//add 1/4 of str as bonus melee dmg
	dmg += damage_type(get_tstr() / 4.f);
	if (dmg < 1)
		dmg = 1;

	return dmg;
}

const damage_type player::ranged_attack() const noexcept
{
	damage_type dmg {0};

	const weapon * equipped = get_equip_weapon((unsigned long long)WEAPONSLOT::RANGED);
	if (equipped)
	{
		dmg = Random::NTK(equipped->min_damage, equipped->max_damage);
		dmg += damage_type(get_tagil() / 4.f);
	}
	
	if (dmg < 1)
		dmg = 1;

	return dmg;
}

//Uses delegate->statblock->core to apply buffs to stats
void player::apply_buff(buff b)
{
	pcclass->buf.push_back(b);
}

//Moves an item into the character's backpack
void player::move_to_backpack(item * to_move) noexcept
{
	backpack.push_back(to_move);
}

//Gives the player the option to get rid of item(s) in their backpack
void player::cleanup() noexcept
{
	const auto to_remove = std::stable_partition(backpack.begin(), backpack.end(),
			[] (const item * i)->bool { return !i->mark_to_delete(); });
	std::for_each(to_remove, backpack.end(), [](item *& i) { manager::delete_item(i); });
	backpack.erase(to_remove, backpack.end());

	const auto remove_ref = std::stable_partition(backpack.begin(), backpack.end(),
			[] (const item * i)->bool { return !i->ref_gone(); });
	backpack.erase(remove_ref, backpack.end());

}

/************************************** Helper Prototypes **********************************************/
/*template wrapper
template <typename T>
bool equip(item * to_equip, T * entity)
{
	player * p = extract_player(entity);
	if (!p)
		return false;
	return equip_item(to_equip, p);
}
/

//overload for player *
inline player * extract_player(player * p)
{
	return p;
}

//overload for delegate *
inline player * extract_player(delegate * d)
{
	return d ? d->get_owner() : nullptr;
}

*/

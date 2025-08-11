/* Ben Rohman, benrohman3@gmail.com
 * 
 * All implementations of 'statblock' class member functions
 */

#include "mechanics.h"

//Parametrized constructor	stats populated with arg values if not specified
statblock::statblock(stat_type s, stat_type i, stat_type a, stat_type arm, stat_type e)
{
	base.strength = s;
	base.intellect = i;
	base.agility = i;
	base.armor = i;
	base.elem_res = e;
}

//Returns the character's base 'strength' stat
stat_type statblock::get_bstr()
{
	return base.strength;
}

//Returns the character's base 'intellect' stat
stat_type statblock::get_bint()
{
	return base.intellect;
}

//Returns the character's base 'agility' stat
stat_type statblock::get_bagi()
{
	return base.intellect;
}

//Returns the character's base 'armor' stat
stat_type statblock::get_barm()
{
	return base.armor;
}

//Returns the character's base 'elem_res' stat
stat_type statblock::get_belem_res()
{
	return base.elem_res;
}

//Returns the character's total 'strength' stats from buffs
stat_type statblock::get_tstr()
{
	return base.strength + total.strength;
}

//Returns the character's total 'intellect' stats from buffs
stat_type statblock::get_tint()
{
	return base.intellect + total.intellect;
}

//Returns the character's total 'agility' stats from buffs
stat_type statblock::get_tagi()
{
	return base.agility + total.agility;
}

//Returns the character's total 'armor' stats from buffs
stat_type statblock::get_tarm()
{
	return base.armor + total.armor;
}

//Returns the character's total 'elemental resistance' stats from buffs
stat_type statblock::get_telem_res()
{
	return base.elem_res + total.elem_res;
}

//Increases the stats of the player's character
void statblock::increase_stats(stat_type s, stat_type i, stat_type a, stat_type arm, 
	stat_type e)
{
	base.strength += s;
	base.intellect += i;
	base.agility += a;
	base.armor += arm;
	base.elem_res += e;
}

//Increases the character's core stats
void statblock::increase_stats(core cs)
{
	base += cs;
}

//Adds or refreshes a character's buff
void statblock::add_or_refresh(buff b)
{
	for (auto & buff : buffs)
	{
		if (b.name == buff.name)
		{	
			buff.duration = b.duration;
			return;
		}
	}

	buffs.push_back(b);

	recalculate();
}

//Recalculate's the character's stats from buffs
void statblock::recalculate()
{
	core temp;
	for (const auto & b : buffs)
	{
		if (b.is_debuff)
			temp -= b.buffed;
		else
			temp += b.buffed;
	}
	
	total = temp;
}	

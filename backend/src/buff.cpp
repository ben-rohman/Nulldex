/* Ben Rohman, benrohman3@gmail.com
 *
 * This is where all the functions in the structs 'buff' and 'core' will be implemented
 *
 */

#include "mechanics.h"

/************************************ BUFF *******************************************************/
//default constructor
buff::buff()
{
	name = "undefined";
	duration = 2u;
	buffed = core();
	is_debuff = false;
}

//parametrized constructor that is passed stats individually
buff::buff(const char * n, stat_type str, stat_type intel, stat_type agi, stat_type arm, 
	   stat_type el_res, uint16_t dur, bool debuff) 
	: name(n), duration(dur), buffed(str, intel, agi, arm, el_res), is_debuff(debuff)
{
}

//parametrized constructor passed 'core' object
buff::buff(const char * n, core cs, uint16_t dur, bool debuff)
	: name(n), duration(dur), buffed(cs), is_debuff(debuff)
{
}

//operator overload function
buff & buff::operator=(const char * n)
{
	this->name = std::string(n);
	this->duration = 2u;
	this->buffed = core(0);
	this->is_debuff = false;
	return *this;
}

/*************************************** CORE **********************************************************/
//default constructor
core::core()
{
	strength = 0;
	intellect = 0;
	agility = 0;
	armor = 0;
	elem_res = 0;
}

//parametrized constructor passed all vars individually
core::core(stat_type s, stat_type i, stat_type ag, stat_type arm, stat_type eres) 
	: strength(s), intellect(i), agility(ag), armor(arm), elem_res(eres) {}

//parametrized constructor
core::core(stat_type all) : strength(all), intellect(all), agility(all), armor(all), elem_res(all) {}

core & core::operator+=(const core & rhs)
{
	strength += rhs.strength;
	intellect += rhs.intellect;
	agility += rhs.agility;
	armor += rhs.armor;
	elem_res += rhs.elem_res;

	return *this;
}

//subtracts from the player's stats or setting them to 0 if negative
core & core::operator-=(const core & rhs)
{
	core tmp = *this;

	strength -= rhs.strength;
	intellect -= rhs.intellect;
	agility -= rhs.agility;
	armor -= rhs.armor;
	elem_res -= rhs.elem_res;
	
	//error check
	if (strength > tmp.strength)
		this->strength = 0u;
	if (intellect > tmp.intellect)
		this->intellect = 0u;
	if (agility > tmp.agility)
		this->agility = 0u;
	if (armor > tmp.armor)
		this->armor = 0u;
	if (elem_res > tmp.elem_res)
		this->elem_res = 0u;

	return *this;
}

//set all stats to the same scalar value
core & core::operator=(const stat_type & rhs)
{
	this->strength = rhs;
	this->intellect = rhs;
	this->agility = rhs;
	this->armor = rhs;
	this->elem_res = rhs;

	return *this;
}

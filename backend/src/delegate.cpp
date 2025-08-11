/* Ben Rohman, benrohman3@gmail.com
 *
 * Where all the 'level_up' class functions will be implemented
 */

#include "user.h"

//Default constructor
delegate::delegate() : statblock(0u, 0u)
{
	current_level = (lvl_type) 0;
	current_exp = (exp_type) 0u;
	exp_to_next = lvl2;
}

//virtual destructor
delegate::~delegate() {}

//Checks if the player can level up
const bool delegate::check_level() noexcept
{
	static const lvl_type lvl_scaler = 2u;
	
	//check if can reach next lvl	
	if (current_exp >= exp_to_next)
	{
		current_level++;
		level_up();
		exp_to_next *= lvl_scaler;
		return true;	
	}
	return false;
}

//New version of level up process
void delegate::req_lvlup() noexcept
{
	++current_level;
	level_up();
}

//Increase in EXP
void delegate::give_exp(const exp_type amt) noexcept
{
	current_exp += amt;
	
}

//Returns the player's current level
lvl_type delegate::get_lvl() const noexcept
{
	return current_level;
}

//Returns the player's current EXP
exp_type delegate::get_exp() const noexcept
{
	return current_exp;
}

//Returns EXP needed to level up
exp_type delegate::get_exp_to_next() const noexcept
{
	return exp_to_next;
}

//Starts ability's cooldown after its used and adds it to the unordered map 'cds' 
void delegate::start_cd(const std::string & sp, int cd_dur)
{
	cds[sp] = cd_dur;
}

//Decrements the cooldown after each turn in combat
void delegate::dec_cd()
{
	for (auto it = cds.begin(); it != cds.end(); )
	{
		if (it->second > 1)
		{
			--(it->second);
			++it;
		}
		else
			it = cds.erase(it);	//erase returns the next valid iterator
	}
}

//Checks if the ability is still cooling down
bool delegate::is_cooling(const std::string & sp) const
{
	return cds.find(sp) != cds.end();
}

//Returns the amount of turns left in the ability's cooldown
int delegate::cd_left(const std::string & sp) const
{
	auto it = cds.find(sp);
	if (it != cds.end())
		return it->second;
	else
		return 0;
}

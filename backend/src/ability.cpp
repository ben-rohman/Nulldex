/* Ben Rohman, benrohman3@gmail.com
 *
 * Implementation of the 'ability' class's member functions
 *
 */

#include "mechanics.h"

//parametrized constructor
ability::ability(const std::string n, uint32_t h, buff * b, uint32_t c, uint32_t co, 
		 abil_target t, abil_scaler s)
	: name(n), hpe(h), given(b), cost(c), cd(co), target(t), scaler(s)
{
	remain_cd = 0u;
}

//destructor
ability::~ability()
{
	if (given)
	{
		delete given;
		given = nullptr;
	}
}

//getter functions
const std::string ability::get_name() const noexcept
{
	return name;
}

const uint32_t ability::get_cd() const noexcept
{
	return cd;
}

const uint32_t ability::get_hpe() const noexcept
{
	return hpe;
}

const buff * ability::get_buff() const noexcept
{
	return given;
}

const uint32_t ability::get_cost() const noexcept
{
	return cost;
}

const abil_target ability::get_target() const noexcept
{
	return target;
}

const abil_scaler ability::get_scaler() const noexcept
{
	return scaler;
}


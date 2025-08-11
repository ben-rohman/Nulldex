/* Ben Rohman, benrohman3@gmail.com 
 * All implementations of 'point_well' class member function 
 */

#include "mechanics.h"

//Default constructor
point_well::point_well()
{
	current = 1;
	max = 1;
}

//Parametrized constructor
point_well::point_well(well_type curr, well_type most)

{
	current = curr;
	max = most;
	//After hp values are set, error check to make sure 'current_hp' < 'max_hp'
	if (current > max)
		current = max;
}

//Sets the player's max hp
void point_well::set_max(well_type new_max) noexcept
{
	//Error check in case it is set to 0
	if (new_max < 1)
		max = 1;
	else 
		max = new_max;
	//Error check so player's hp can't ever be greater than their 'class's max
	if (current > max)
		current = max;
	
}

//Gets the player's max hp based on their chosen 'class'
[[nodiscard]] const well_type point_well::get_max() const noexcept
{
	return max;
}

//Gets the player's current hp
[[nodiscard]] const well_type point_well::get_current() const noexcept
{
	return current;
}

//Checks if the player's current hp is full(= max hp)
[[nodiscard]] const bool point_well::is_full() const noexcept
{
	return (current == max);
}

//Changes the player's current hp if they take damage
void point_well::reduce(well_type damage) noexcept
{
	
	//Error check if the player has died
		//if damage > current_hp then hp will become a huge +int since the private data types
		//are UNSIGNED INTS
	if (damage > current)
	{
		current = 0;
		return;
	}
	current -= damage;
}

//Changes the player's current hp if its replenished
void point_well::increase(well_type amount) noexcept
{
	//Error check so no overhealing can happen
	if (amount + current > max)
	{
		current = max;
		return;
	}
	
	current += amount;
}


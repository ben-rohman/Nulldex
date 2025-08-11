/* Ben Rohman, benrohman3@gmail.com
 *
 * All typedef declarations + 'random' def
 *
 */

#pragma once
#include <cstdint>

//'hitpoints' typedef
typedef std::uint16_t well_type;	//UNSIGNED 16 bit int
//'stat' typedef
typedef std::uint16_t stat_type;	//UNSIGNED 16 bit int
//'EXP' typedef
typedef std::uint64_t exp_type;		//UNSIGNED 64 bit int
//'level_system' typedef
typedef std::uint16_t lvl_type;		//UNSIGNED 16 bit int
//'damage' typedef
typedef std::uint16_t damage_type;
//number of items the player has
typedef std::uint16_t item_count;

namespace Random
{
	[[nodiscard]] uint32_t NTK(uint32_t n, uint32_t k);
}

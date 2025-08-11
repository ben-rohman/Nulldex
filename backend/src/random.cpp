/* Ben Rohman, benrohman3@gmail.com
 *
 * This is where the function that simulates a dice roll will be implemented */

#include "types.h"
#include <chrono>
#include <random>

namespace Random
{
	uint32_t NTK(uint32_t n, uint32_t k)
	{
		static uint64_t seed = 
			std::chrono::high_resolution_clock::now().time_since_epoch().count();
		static std::seed_seq ss{ uint32_t(seed & 0xffffffff), uint32_t(seed >> 32) };
		static std::mt19937 mgen(ss);

		//error check user input --> n<=k
		if (n <= k)
		{
			std::uniform_int_distribution<std::mt19937::result_type> ntkd(n, k);
			return ntkd(mgen);
		}
		else	//n > k but still functions as bounds k to n
		{
			std::uniform_int_distribution<std::mt19937::result_type> ntkd(k, n);
			return ntkd(mgen);
		}
	}
}
/*
	uint32_t NTK(uint32_t n, uint32_t k)
	{
		static uint64_t seed =
			std::chrome::high_resolution_clock::now().time_since_epoch().count();
		static std::seed_seq ss { uint32_t(seed & 0xffffffff), uint32_t(seed >> 32) };
		static std::mt19937 mgen(ss);

		if (n <= k)
		{
		
			std::uniform_int_distribution<std::mt19937::result_type> ntkd(n, k);
			return ntkd(mgen);
		}
		else	//n > k but still functions as bounds k to n
		{
			std::uniform_int_distribution<std::mt19937::result_type> ntkd(k, n);
			return ntkd(mgen);
		}
	}
}
*/

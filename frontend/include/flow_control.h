/* Ben Rohman, benrohman3@gmail.com
 *
 * This is the header file where the structures and whattnot will be declared that will be used to help
 *	control the flow of the game. */

#pragma once
//#include "game.h"
#include <chrono>
#include <thread>
#include <cstdlib>

//Some ANSI escape codes to make outputs more interesting
const std::string RESET		= "\033[0m";
const std::string BOLD 		= "\033[1m";
const std::string DIM		= "\033[2m";
const std::string ITALIC	= "\033[3m";
const std::string UNDERLINE	= "\033[4m";
const std::string INVERSE	= "\033[7m";
const std::string BLACK		= "\033[30m";
const std::string RED		= "\033[31m";
const std::string GREEN		= "\033[32m";
const std::string YELLOW	= "\033[33m";
const std::string BLUE		= "\033[34m";
const std::string MAGENTA	= "\033[35m";
const std::string CYAN		= "\033[36m";
const std::string WHITE		= "\033[37m";



//slows the output of info, so far just used for printing previews and backstories
void slow_print(const std::string & text, int delay = 20);
//clears screen of text
void clear_screen();
//asks user to press enter to continue
void wait();


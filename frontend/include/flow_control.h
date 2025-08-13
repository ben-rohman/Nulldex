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
	//font stuff
const std::string RESET		= "\033[0m";
const std::string BOLD 		= "\033[1m";
const std::string DIM		= "\033[2m";
const std::string ITALIC	= "\033[3m";
const std::string UNDERLINE	= "\033[4m";
const std::string INVERSE	= "\033[7m";
	//font colors
const std::string BLACK		= "\033[30m";
const std::string GRAY		= "\033[90m";
const std::string MAROON	= "\033[31m";
const std::string RED		= "\033[91m";	//Bright red
const std::string FOREST	= "\033[32m";
const std::string GREEN	 	= "\033[92m";	//Bright green
const std::string GOLD		= "\033[33m";
const std::string YELLOW	= "\033[93m";	//Bright yellow
const std::string BLUE		= "\033[34m";
const std::string LAVENDER	= "\033[94m";	//Bright blue
const std::string MAGENTA	= "\033[35m";
const std::string PINK		= "\033[95m";	//Bright magenta
const std::string SKY		= "\033[36m";
const std::string CYAN		= "\033[96m";	//Bright cyan
const std::string PEARL		= "\033[37m";
const std::string WHITE	 	= "\033[97m";	//Bright white
	//background colors
const std::string BGBLACK	= "\033[40m";
const std::string BGGRAY	= "\033[100m";
const std::string BGMAROON	= "\033[41m";
const std::string BGRED		= "\033[101m";
const std::string BGFOREST	= "\033[42m";
const std::string BGGREEN	= "\033[102m";
const std::string BGGOLD	= "\033[43m";
const std::string BGYELLOW	= "\033[103m";
const std::string BGBLUE	= "\033[44m";
const std::string BGLAVENDER	= "\033[104m";
const std::string BGMAGENTA	= "\033[45m";
const std::string BGPINK	= "\033[105m";
const std::string BGSKY		= "\033[46m";
const std::string BGCYAN	= "\033[106m";
const std::string BGPEARL	= "\033[47m";
const std::string BGWHITE	= "\033[48m";
//Unicode characters
const std::string BLOCK		= "\u2588";
const std::string DBLOCK	= "\u2593";
const std::string MBLOCK	= "\u2592";
const std::string LBLOCK	= "\u2591";
const std::string UPBLOCK	= "\u2580";
const std::string LOBLOCK	= "\u2584";
const std::string HLINE		= "\u2500";
const std::string VLINE 	= "\u2502";
const std::string DRCORNER	= "\u250C";
const std::string DLCORNER	= "\u2510";
const std::string URCORNER	= "\u2514";
const std::string ULCORNER	= "\u2518";
const std::string CROSS		= "\u253C";
const std::string UPTRIANGLE	= "\u25B2";
const std::string DOTRIANGLE	= "\u25BC";
const std::string RTRIANGLE	= "\u25BA";
const std::string LTRIANGLE	= "\u24C4";
const std::string SCIRCLE	= "\u25CF";
const std::string CIRCLE	= "\u25CB";
const std::string SSTAR		= "\u2605";
const std::string STAR		= "\u2606";
const std::string HEART		= "\u2665";
	//math
const std::string FORALL	= "\u2200";
const std::string THEREEXISTS	= "\u2203";
const std::string SUBSET	= "\u2282";
const std::string SUPERSET	= "\u2283";
const std::string ELEMENTOF	= "\u2208";
const std::string NOTELEMENTOF	= "\u2209";
const std::string IMPLY		= "\u21D2";
const std::string BICONDITIONAL	= "\u21D4";
const std::string LOWDELTA	= "\u2202";
const std::string CAPSIGMA	= "\u2211";
const std::string ALPHA		= "\u03B1";
const std::string EMPTYSET	= "\u2300";



//slows the output of info, so far just used for printing previews and backstories
void slow_print(const std::string & text, int delay = 20);
//clears screen of text
void clear_screen();
//asks user to press enter to continue
void wait();


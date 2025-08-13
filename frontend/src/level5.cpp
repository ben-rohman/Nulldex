/* Ben Rohman, benrohman3@gmail.com
 *
 * Implementations of class level5's member functions and any other helpers
 *
 */

#include "levels.h"

#if defined(_WIN32) || defined(_WIN64)
#	include <conio.h>
#else
#	include <termios.h>
#	include <unistd.h>
#endif

//constructor
level5::level5()
{
	completed = false;
	range = 2;		//sentry can see 3 tiles ahead
	load_map();
}

//returns the 'completed' flag
bool level5::is_complete() const 
{
	return completed;
}

//level control function
bool level5::play(user * pl) 
{
	slow_print("\n\n\t\t" + ITALIC + "========= Level 5: The Weight of the Hand =========\n\n" + 
		   RESET + "\tThe monastery walls tremble as the as the 'Peace Eternal' surrounds "
		   "it...\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	if (!stealth(pl))
	{
		slow_print("\n\tYou were captured before reaching the monastery gates...\n");
		return false;
	}
	if (!confront(pl))
	{
		slow_print("\n\tYou fall as the cult overruns the monastery...\n");
		return false;
	}
	completed = true;
	return true;
}

//stealth aspect control
bool level5::stealth(user * pl)
{
	while (ppos != exit)
	{
		draw_map();
		char c = get_input();
		if (!c)
			continue;
		std::pair<int, int> mov = movement(c);
		if (mov == std::pair<int, int>{0, 0})
			continue;
		if (!try_move(ppos, mov))
			continue;
		update_sentries();
		if (check_detection())
		{
			slow_print("\n\tA sentry spots you! You've been caught by the cult...\n");
			return false;
		}
	}
	return true;
}

//final fight
bool level5::confront(user * pl)
{
	//variables
	char ch {' '};		//user's choice
	bool success {false};	//if the player convinces cult to leave
	player * p = pl->get_player();
	if (!p)
	{
		std::cerr << RED << BOLD << "[ERROR] Null pointer found in level5::confrontation "
			  << RESET << std::endl;
		return false;
	}
	
	slow_print("\n\n\t\t" + ITALIC + "You stand before the cult leader. His followers surround "
		   "you...\n\t(1) Surrender to them \n\t(2) Persuade them to leave \n\t(3) Attack "
		   + RESET + "Enter your choice here: ");
	do
	{
		std::cin >> ch;
		std::cin.ignore(10, '\n');
		if (ch == '1')
		{
			slow_print("\n\n\tYou kneel and accept their 'peace'. The siege ends without "
				   "bloodshed...");
			return false;
		}
		else if (ch == '2')
		{
			success = intellect_success(pl->get_player(), 15);
			if (success)
			{
				slow_print("\n\tYour words break through their fanaticism. They "
					   "withdraw peacefully...");
				return true;
			}
			else
			{
				slow_print("\n\tYou are unable to convince them. The leader steps "
					   "forward, brandishing his weapon...");
				monster cult(67, 4, 8, "Cult Leader");
				combat fight(p, cult);
				return fight.control();
			}
		}
		else if (ch == '3')
		{
			monster cult(51, 3, 8, "Cult Leader");
			combat fight(p, cult);
			return fight.control();
		}
		if (ch != '1' || ch != '2' || ch != '3')
			std::cout << BOLD << RED << "[ERROR] Invalid input. Try again " << RESET 
				  << std::endl;
	}	while (ch != '1' || ch != '2' || ch != '3');
	return false;
}

/****************************** Helpers For Stealth Phase **************************************/
//map design and player(P), exit(E), and sentry(S) positions and sentry paths set
void level5::load_map()
{
	map = 
	{
		"############################",
/*S1*/		"#P.........S..#..S.......S.E",//S12 and S13
/*S2*/		"##S...........#S...........#",//S11
		"#.............#............#",
		"#....######.###...#######..#",
/*S3 and S4*/	"#S.........#.S#S...........#",//S10
/*S5*/		"#.....S.......#S...........#",//S9
/*S6*/		"#......#S.....#............#",
		"#......#......#.S........S.#",//S8
		"#......#......#............#",
		"#......#..................S#",//S7
		"############################"
	};
	//format is {row, col} = {y, x}...
	ppos = {1, 1};
	exit = {1, 27};
	sentries.clear();
	//Sentry 1: Vertical, (1, 11) to (4, 11)
	sentries.push_back(patrol{{ {1, 11}, {2, 11}, {3, 11}, {4, 11}, {3, 11}, {2, 11} }, 0});
	//Sentry 2: Horizontal, (2, 2) to (2, 10)
	sentries.push_back(patrol{{ {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, {2, 9},
				    {2, 10}, {2, 9}, {2, 8}, {2, 7}, {2, 6}, {2, 5}, {2, 4}, {2, 3} },
				  0});
	//Sentry 3: Horizontal, (5, 1) to (5, 10)
	sentries.push_back(patrol{{ {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8},
				    {5, 9}, {5, 10}, {5, 9}, {5, 8}, {5, 7}, {5, 6}, {5, 5}, {5, 4}, 
				    {5, 3}, {5, 2} }, 0});
	//Sentry 4: Vertical, (5, 13) to (10, 13)
	sentries.push_back(patrol{{ {5, 13}, {6, 13}, {7, 13}, {8, 13}, {9, 13}, {10, 13}, {9, 13},
				    {8, 13}, {7, 13}, {6, 13} }, 0});
	//Sentry 5: Vertical, (6, 6) to (10, 6)
	sentries.push_back(patrol{{ {6, 6}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {9, 6}, {8, 6}, {7, 6} },
				  0});
	//Sentry 6: Horizontal, (7, 8) to (7, 12)
	sentries.push_back(patrol{{ {7, 8}, {7, 9}, {7, 10}, {7, 11}, {7, 12}, {7, 11}, {7, 10}, 
				    {7, 9} }, 0});
	//Sentry 7: Vertical, (10, 26) to (4, 26)
	sentries.push_back(patrol{{ {10, 26}, {9, 26}, {8, 26}, {7, 26}, {6, 26}, {5, 26}, {4, 26},
				    {5, 26}, {6, 26}, {7, 26}, {8, 26}, {9, 26} }, 0});
	//Sentry 8: Horizontal, (8, 25) to (8, 16)
	sentries.push_back(patrol{{ {8, 25}, {8, 24}, {8, 23}, {8, 22}, {8, 21}, {8, 20}, {8, 19},
				    {8, 18}, {8, 17}, {8, 16}, {8, 17}, {8, 18}, {8, 19}, {8, 20},
				    {8, 21}, {8, 22}, {8, 23}, {8, 24} }, 0});
	//Sentry 9: Vertical, (6, 15) to (10, 15)
	sentries.push_back(patrol{{ {6, 15}, {7, 15}, {8, 15}, {9, 15}, {10, 15}, {9, 15}, {8, 15}, 
				    {7, 15} }, 0});
	//Sentry 10: Horizontal, (5, 15) to (5, 25)
	sentries.push_back(patrol{{ {5, 15}, {5, 16}, {5, 17}, {5, 18}, {5, 19}, {5, 20}, {5, 21},
				    {5, 22}, {5, 23}, {5, 24}, {5, 25}, {5, 24}, {5, 23}, {5, 22},
				    {5, 21}, {5, 20}, {5, 19}, {5, 18}, {5, 17}, {5, 16} }, 0});
	//Sentry 11: Horizontal, (2, 15) to (2, 24)
	sentries.push_back(patrol{{ {2, 15}, {2, 16}, {2, 17}, {2, 18}, {2, 19}, {2, 20}, {2, 21},
				    {2, 22}, {2, 23}, {2, 24}, {2, 23}, {2, 22}, {2, 21}, {2, 20},
				    {2, 19}, {2, 18}, {2, 17}, {2, 16} }, 0});
	//Sentry 12: Vertical, (1, 17) to (4, 17)
	sentries.push_back(patrol{{ {1, 17}, {2, 17}, {3, 17}, {4, 17}, {3, 17}, {2, 17} }, 0});
	//Sentry 13: Vertical, (1, 25) to (4, 25)
	sentries.push_back(patrol{{ {1, 25}, {2, 25}, {3, 25}, {4, 25}, {3, 25}, {2, 25} }, 0});

}

//renders the map
void level5::draw_map() const
{
	clear_screen();
	const int rows {static_cast<int>(map.size())};
	if (rows == 0)
		return;
	const int cols {static_cast<int>(map[0].size())};
	//precompute a quick grid for centries and their current steps
	std::vector<std::vector<bool>> here(rows, std::vector<bool>(cols, false));
	for (const auto & s : sentries)
	{
		if (!s.route.empty())
		{
			auto & spos = s.route[s.step % s.route.size()];
			if (spos.first >= 0 && spos.first < rows && spos.second < cols)
				here[spos.first][spos.second] = true;
		}
	}
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < cols; ++x)
		{
			std::string cell;
			if (ppos.first == y && ppos.second == x)
			{
				std::cout << BLUE << SKY << BOLD << BGPEARL << " P " << RESET;
				continue;
			}
			if (exit.first == y && exit.second == x)
			{
				std::cout << FOREST << BOLD << BGPEARL << " E " << RESET;
				continue;
			}
			if (here[y][x])
			{
				std::cout << RED << BOLD << BGPEARL << " S " << RESET;
				continue;
			}
			char t = map[y][x];
			if (t == '#')
				std::cout << BGGRAY << BLACK << " # " << RESET;
			else
				std::cout << BGPEARL << BLACK  << " . "  << RESET;
		}
		std::cout << '\n';
	}
}

//gets direction player wants to move in, cross platform single char input (blocking)
char level5::get_input() const
{
#if defined(_WIN32) || defined(_WIN64)
	int ch = _getch();
	if (ch == 0 || ch == 0xE0)
	{
		int ch2 = _getch();
		if (ch2 == 72)
			return 'w';
		if (ch2 == 80)
			return 's';
		if (ch2 == 75)
			return 'a';
		if (ch2 == 77)
			return 'd';
	}
	return static_cast<char>(ch);
#else
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	char ch = 0;
	if (read(STDIN_FILENO, &ch, 1) < 0)
		ch = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	if (ch == '\x1b')
	{
		char seq[2];
		if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1)
		{
			if (seq[0] == '[')
			{
				if (seq[1] == 'A')
					return 'w';
				if (seq[1] == 'B')
					return 's';
				if (seq[1] == 'C')
					return 'd';
				if (seq[1] == 'D')
					return 'a';
			}
		}
		return 0;
	}
	return ch;
#endif
}

//returns actual direction vector based on input from get_input
std::pair<int, int> level5::movement(char c) const
{
	c = static_cast<char>(std::tolower(c));
	if (c == 'w')
		return {-1, 0};
	else if (c == 's')
		return {1, 0};
	else if (c == 'a')
		return {0, -1};
	else if (c == 'd')
		return {0, 1};
	else
		return {0, 0};
}

//checks if player movement is valid
bool level5::try_move(std::pair<int, int> & pos, const std::pair<int, int> & mov)
{
	int ny = pos.first + mov.first;
	int nx = pos.second + mov.second;

	if (ny < 0 || ny >= (int)map.size() || nx < 0 || nx >= (int)map[0].size())
		return false;
	if (map[ny][nx] == '#')
		return false;
	pos = {ny, nx};
	return true;
}

//updates the sentries position based on their routes
void level5::update_sentries()
{
	for (auto & sentry : sentries)
		sentry.step = (sentry.step + 1) % sentry.route.size();
}

//checks if the player is within the detection range of a sentry
bool level5::check_detection() const
{
	for (const auto & sentry : sentries)
	{
		if (sentry.route.size() < 2)
			continue;
		auto spos = sentry.route[sentry.step];
		auto next = sentry.route[(sentry.step + 1) % sentry.route.size()];
		int sy = spos.first;
		int sx = spos.second;
		int ny = next.first;
		int nx = next.second;
		int py = ppos.first;
		int px = ppos.second;
		int dy = ny - sy;
		int dx = nx - sx;
		if (dy == 0 && dx != 0)	//horizontal route
		{
			if (py != sy)
				continue;//player not in same row
			if ((dx > 0 && px > sx && px <= nx) || (dx < 0 && px < sx && px >= nx))
			{
				bool blocked {false};
				for (int x = sx + ((dx > 0) ? 1 : -1); x != px; x += (dx > 0 ? 1 : -1))
				{
					if (map[sy][x] == '#')
					{
						blocked = true;
						break;
					}
				}
				if (!blocked)
					return true;//detected
			}
		}
		else if (dx == 0 && dy != 0)//vertical route
		{
			if (px != sx)
				continue;//player not in same column
			if ((dy > 0 && py > sy && py <= ny) || (dy < 0 && py < sy && py >= ny))
			{
				bool blocked {false};
				for (int y = sy + ((dy > 0) ? 1 : -1); y != py; y += (dy > 0 ? 1 : -1))
				{
					if (map[y][sx] == '#')
					{
						blocked = true;
						break;
					}
				}
				if (!blocked)
					return true;//detected
			}
		}
	}
	return false;
}

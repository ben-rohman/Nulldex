/* Ben Rohman, benrohman3@gmail.com
 *
 * level3 class member function implementations			*/

#include "levels.h"

#if defined(_WIN32) || defined(_WIN64)
#	include <conio.h>
#else
#	include <termios.h>
#	include <unistd.h>
#endif

//constructor
level3::level3()
{
	completed = false;
	remain = 3;
	part.clear();
	prev.clear();
	exit.clear();
	soul.clear();
	dist_map.clear();
	load_default();			//load first maze
}

//returns 'completed' flag
bool level3::is_complete() const 
{ 
	return completed;
}

//main flow control 
bool level3::play(user * pl)
{
	remain = static_cast<int>(soul.size());

	print_intro();

	while(remain > 0)
	{
		draw_maze();
		char c = get_input();
		std::pair<int, int> mov = play_direction(c);
		if (mov == std::pair<int, int>{0, 0})
			continue;
		if (try_move(part[0], mov))
			interact(pl);
	}
	return check_end(pl) && remain == 0;
}

//prints level intro
void level3::print_intro()
{
	slow_print("\n\n\t\t" + ITALIC + UNDERLINE + "========= Level 3: Lullaby of the Departed "
		   "=========\n\n" + RESET, 60);
	slow_print("\tA graveyard of restless spirits beckons. Guide three souls to peace.\n\n", 60);
	slow_print(BOLD + "\n\tUse WASD (or arrow keys) to move. Reach 'S' to interact with a "
		   "soul. " + UNDERLINE + "\nSouls remaining: " + RESET + std::to_string(remain) + '\n');
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
}

//if P lands on an S tile->find which soul->handles removing S tile from maze and spirit vector
bool level3::interact(user * pl)
{
	//variables
	bool success {0};
	int loc = souls_index(part[0]);
	if (loc < 0)
		return false;
	int type = spirit[loc];
	if (type == 0)
		success = peaceful(pl, loc);
	else if (type == 1)
		success = logic(pl, loc);
	else
		success = chase(pl, loc);
	if (success)
	{
		maze[part[0].first][part[0].second] = ' ';
		soul.erase(soul.begin() + loc);
		spirit.erase(spirit.begin() + loc);
		remain = static_cast<int>(soul.size());
		slow_print("\n\n\tSoul is laid to rest...\n");
	}
	else
		slow_print("\n\n\tThe soul resists your aid... for now...\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	return success;
}

//win/lose messages and conditions
bool level3::check_end(user * pl)
{
	if (remain == 0)
	{
		slow_print("\n\tA lullaby whispers through the stone. The graveyard quiets...\n");
		completed = true;
		std::this_thread::sleep_for(std::chrono::milliseconds(600));
		return true;
	}
	if (!pl->is_alive())
	{
		slow_print("\nYou fall in the graveyard... darkness consumes you.\n");
		return false;
	}
	return false;
}

/***************************************** MAZE FUNCTIONS *******************************************/
//basic maze layout	# = wall, . = floor, S = soul, P = player starting position
void level3::load_default()
{
	maze = 
	{
		"############################",
		"#P....##.....S....#....#...#",
		"#.##..##.##.###.#####.##.###",
		"#....###....#.........#...##",
		"##.#####.#####.###.###..#.##",
		"#......#.....#...#.....#..##",
		"#.####...###.#.#.#.###.#.###",
		"#..S..##..#...#.#...#...####",
		"###.#####.#.###.#.#.#.######",
		"#....#.....#.......##.....S#",
		"############################"
	};
	for (int y = 0; y < (int)maze.size(); ++y)
	{
		for (int x = 0; x < (int)maze[y].size(); ++x)
		{
			if (maze[y][x] == 'P')
			{
				part.emplace_back(y, x);
				prev.emplace_back(y, x);
				maze[y][x] = '.';
			}
			else if (maze[y][x] == 'S')
			{	
				soul.emplace_back(y, x);
				spirit.emplace_back(static_cast<int>(spirit.size()));
			}
		}
	}
}

//mirrored maze layout for chase sequence
void level3::mirror_maze()
{
	maze = 
	{
		"############################",
		"#S...P##.......#.....#....##",
		"#####.#.#.#.###.#.#####.####",
		"###...#...#.#...#..##.....##",
		"##.#.###.#.#.#.###...####.##",
		"#..#.....#...#.....#......##",
		"#.#..###.###.#####.#####.###",
		"#...#.........#....###....##",
		"##.##.#####.###.##.##..##.##",
		"#..#....#..........##.....E#",
		"############################"
	};
	//clear previous positions
	part.clear();
	prev.clear();
	exit.clear();
	soul.clear();
	for (int y = 0; y < (int)maze.size(); ++y)
	{
		for (int x = 0; x < (int)maze[y].size(); ++x)
		{
			if (maze[y][x] == 'P')
			{
				part.emplace_back(y, x);
				prev.emplace_back(y, x);
				maze[y][x] = '.';
			}
			else if (maze[y][x] == 'S')
			{	
				soul.emplace_back(y, x);
				spirit.emplace_back(static_cast<int>(spirit.size()));
			}
			else if (maze[y][x] == 'E')
				exit.emplace_back(y, x);
		}
	}
}

//Render the maze
void level3::draw_maze() const
{
	clear_screen();
	for (int y = 0; y < (int)maze.size(); ++y)
	{
		for (int x = 0; x < (int)maze[y].size(); ++x)
		{
			if (!part.empty() && y == part[0].first && x == part[0].second)
				std::cout << CYAN << BOLD << 'P' << RESET << "   ";
			else if (!soul.empty() && y == soul[0].first && x == soul[0].second)
				std::cout << MAGENTA << BOLD << 'S' << RESET << "   ";
			else if (!exit.empty() && y == exit[0].first && x == exit[0].second)
				std::cout << GREEN << BOLD << 'E' << RESET << "   ";
			else
				std::cout << maze[y][x] << "   ";
		}
		std::cout << "\n\n";
	}

}

//cross platform single char input (blocking)
char level3::get_input() const
{
#if defined(_WIN32) || defined(_WIN64)
	int ch = _getch();
	//windows arch: arrow keys return 0 or 0xE0 then a code
	if (ch == 0 || ch == 0xE0)
	{
		int ch2 = _getch();
		//map arrow keys to WASD
		if (ch2 == 72)
			return 'w';	//up
		if (ch2 == 80)
			return 's';	//down
		if (ch2 == 75)
			return 'a';	//left
		if (ch2 == 77)
			return 'd';	//right
	}
	return static_cast<char>(ch);
#else
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);//disable buffering and echo
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	char ch = 0;
	if (read(STDIN_FILENO, &ch, 1) < 0)
		ch = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	//handle escapt sequences for arrows
	if (ch == '\x1b')		//start of escape
	{
		//attempt to read 2 more bytes
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

//try moving player (true if moved
bool level3::try_move(std::pair<int, int> & pos, const std::pair<int, int> & mov)
{
	int ny = pos.first + mov.first;
	int nx = pos.second + mov.second;

	if (ny < 0 || ny >= (int)maze.size() || nx < 0 || nx >= (int)maze[0].size())
		return false;
	if (maze[ny][nx] == '#')
		return false;
	//move permitted
	pos = {ny, nx};
	return true;
}

//return index into soul vector or -1 if none
int level3::souls_index(const std::pair<int, int> & pos) const
{
	for (size_t i = 0; i < soul.size(); ++i)
	{	
		if (soul[i] == pos)
			return static_cast<int>(i);
	}
	return -1;
}

//returns movement vector for player input or empty vector if input is invalid
std::pair<int, int> level3::play_direction(char c)
{
	c = static_cast<char>(std::tolower(c));
	if (c == 'w')		//up
		return {-1, 0};
	else if (c == 's')	//down
		return {1, 0};
	else if (c == 'a')	//left
		return {0, -1};
	else if (c == 'd')	//default
		return {0, 1};
	else			//invalid/no move
		return {0, 0};
}

//tries to move 'S' during the chase sequence
bool level3::try_soul()
{
	std::pair<int, int> dir = soul_path(soul[0]);
	if (dir == std::pair<int, int>{0, 0} || !try_move(soul[0], dir))
	{
		dir = soul_path(prev[0]);
		if (!try_move(soul[0], dir))
		{
			std::cout << RED << BOLD << "\n[ERROR] Soul movement failed with poth part and prev " 
				  << RESET << std::endl;
			return false;
		}
	}
	return true;
}

//if S catches up to P updates pl health and returns damage dealt(0 or 5)
int level3::collision(user * pl)
{
	if (soul[0] == part[0])
	{
		pl->get_player()->damage(5);
		slow_print("\n\tThe spirit caught you. You lose 5 HP.\n");
		return 5;
	}
	return 0;
}

//checks if player has reached 'E'
bool level3::check_exit()
{
	if (part[0] == exit[0])
	{
		completed = true;
		slow_print("\n\t" + BOLD + GREEN + "You escaped from the maze!" + RESET + '\n');
		return true;
	}
	return false;
}

//chase helper that updates the player's distance from cells
std::vector<std::vector<int>> level3::update_map(const std::pair<int, int> & start)
{
	//variables
	int rows {static_cast<int>(maze.size())};
	int cols {static_cast<int>(maze[0].size())};
	std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, -1));
	std::queue<std::pair<int, int>> q;
	int sy {start.first};
	int sx {start.second};

	dist[sy][sx] = 0;
	q.push({sy, sx});

	//direction vectors for up, down, left, right
	const int dy[4] = {-1, 1, 0, 0};
	const int dx[4] = {0, 0, -1, 1};

	while (!q.empty())
	{
		auto [y, x] = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < rows && nx >= 0 && nx < cols && maze[ny][nx] != '#' && 
			    dist[ny][nx] == -1)
			{
				dist[ny][nx] = dist[y][x] + 1;
				q.push({ny, nx});
			}
		}
	}
	return dist;
}

//function that gets the direction soul should move
std::pair<int, int> level3::soul_path(const std::pair<int, int> & pos)
{
	//variables
	int sy {pos.first};
	int sx {pos.second};
	int rows {static_cast<int>(dist_map.size())};
	int cols {static_cast<int>(dist_map[0].size())};
	const int dy[4] = {-1, 1, 0, 0};
	const int dx[4] = {0, 0, -1, 1};
	std::pair<int, int> best{0, 0};
	int opt {dist_map[sy][sx]};	//current soul cell distance

	for (int i = 0; i < 4; ++i)
	{
		int ny = sy + dy[i];
		int nx = sx + dx[i];

		if (ny >= 0 && ny < rows && nx >= 0 && nx < cols)
		{
			int tmp = dist_map[ny][nx];
			if (tmp != -1 && tmp < opt)
			{
				opt = tmp;
				best = {dy[i], dx[i]};
			}
		}
	}
	return best;
}
	

/*************************************** SOUL INTERACTIONS ******************************************/
//peaceful dialogue choice handler
bool level3::peaceful(user * pl, int soul_id)
{
	int choice {0};
	std::string name = (soul_id < 0 || soul_id >= (int)soul.size()) ? "A restless spirit" : "Elandra";
	clear_screen();
	slow_print("\n\tYou kneel before " + name + ". Their voice trembles with sorrow. \n(1) Speak "
		   "of forgiveness and release\n(2) Share a fond memory you invent to comfort them "
		   "\n(3) Offer a brief prayer\nChoice: ");
	
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (choice == 1)
	{
		slow_print("\n\tTheir shoulders relax. A soft light light spills from their form. They "
			   "pass on peacefully.\n");
		pl->get_player()->get_class()->give_exp(100);
		return true;
	}
	else if (choice == 2)
	{
		slow_print("\n\tThough the memory is not real, it gives them comfort. They drift away "
			   "with a bittersweet smile.\n");
		pl->get_player()->get_class()->give_exp(50);
		return true;
	}
	else if (choice == 3)
	{
		slow_print("\n\tThe prayer seems to settle the noise in their mind. They nod and fade.\n");
		return true;
	}

	slow_print("\n\tThey remain unconvinced.\n");
	return false;

}

//logic/riddle handler
bool level3::logic(user * pl, int soul_id)
{
	clear_screen();
	std::string ans;
	slow_print("\n\tA voice whispers: 'Answer this and I will go... " + ITALIC + "\n\t'I hold "
		   "what you have lost without taking it. \n\tI am returned, but never given. \n\tWhat "
		   "am I?'\nYour answer: ");
	std::getline(std::cin, ans);
	std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);

	if (ans == "memory" || ans == "memories")
	{
		slow_print("\n\tYes... The spirit relaxes, a smile breaking through. \n\tThank you..\n");
		pl->get_player()->get_class()->give_exp(50);
		return true;
	}
	else
	{
		slow_print("\n\tThe spirit shakes their head and returns to the maze.\n");
		return false;
	}
}

//chase handler
bool level3::chase(user * pl, int soul_id)
{
	mirror_maze();
	int lag {0};
	dist_map = update_map(part[0]);

	slow_print(ITALIC + "\n\tThe soul's eyes snap open and as it screams, something in the maze "
		   "awakens..." + RESET + "\n\n\tNavigate back through the maze and reach the exit 'E' "
		   "before it reaches you");

	while (true)
	{
		draw_maze();
		char c = get_input();
		prev[0] = part[0];
		if (!c)
			continue;
		std::pair<int, int> mov = play_direction(c);
		if (try_move(part[0], mov))
			dist_map = update_map(part[0]);
		else
			continue;
		if (lag > 0)
			--lag;
		else
			try_soul();
		int dmg = collision(pl);
		if (dmg > 0 && !pl->is_alive())
		{
				slow_print("\n\tThe spirit dragged you, unable to find the exit, back "
					   "further into the maze...\n");
				return false;
		}
		if (check_exit())
			return true;
		if (dmg > 0)
			lag = 2;
	}
	return false;
}

/*
bool level3::chase(user * pl, int soul_id)
{
	mirror_maze();			//load 2nd maze and get soul, player, and exit positions
	//variables
	bool pursue {true};
	dist_map = update_map(part[0]);	//set dist_map
	int lag {0};

	slow_print(ITALIC + "\n\tThe soul's eyes snap open and as it screams, something in the maze "
		   "awakens..." + RESET + "\n\n\tNavigate back through the maze and reach the exit 'E' "
		   "before it reaches you");
	while (pursue)
	{
		draw_maze();
		char c = get_input();
		std::pair<int, int> mov {0, 0};
		prev[0] = part[0];	//save old position before mov since prev holds last loop's old pos

		if (!c)
			continue;		//restart loop
		c = static_cast<char>(std::tolower(c));
		if (c == 'w')			//up
			mov = {-1, 0};
		else if (c == 's')		//down
			mov = {1, 0};
		else if (c == 'a')		//left
			mov = {0, -1};
		else if (c == 'd')		//right
			mov = {0, 1};
		else
			continue;		//restart loop

		if (try_move(part[0], mov))
			dist_map = update_map(part[0]);
		else
			continue;
		if (lag > 0)
			--lag;
		else
		{
			std::pair<int, int> dir = soul_path(soul[0]);
			if (dir == std::pair<int, int>{0, 0} || !try_move(soul[0], dir))
			{
				dir = soul_path(prev[0]);
				if (!try_move(prev[0], dir))
					std::cout << RED << BOLD << "\n\n[ERROR] Soul movement failed with "
						  << "both part and prev " << RESET << std::endl;
			}
		}
		if (soul[0] == part[0])
		{
			lag = 2;
			pl->get_player()->damage(5);
			slow_print("\n\tThe spirit caught up to you. You lose 5 HP.\n");

			if (!pl->is_alive())
			{
				slow_print("\n\tThe spirit dragged you, unable to find the exit, back "
					   "further into the maze...\n");
				return false;
			}
		}
		if (part[0] == exit[0])
		{
			completed = true;
			slow_print("\n\t" + BOLD + GREEN + "You escaped the maze!\n");
			return true;
		}
	}
	return false;
}
*/

/* Ben Rohman, benrohman3@gmail.com
 * All declarations and function prototypes for the 9 levels 	*/

#pragma once

#include <queue>			//record movement
#include <climits>			//defines parameters that characterize ints
#include <iomanip>			//for setw(), used in output
#include "game.h"

/************************************* CLASS DECLARATIONS *****g**************************************/

//Level 1; Gray, Emotional Hook/Psychic Bond
class level1 : public stage
{
	public:
		level1();		//constructor
		bool play(user * play) override;
		bool is_complete() const override;

	private:
		bool completed;	
		bool mem_puzzle(const std::string & prompt, const std::string & ans);
		bool fight_wraith(user * player, monster & wraith);
};

//Level 2; Sky: Fate/Destiny
class level2 : public stage
{
        public:
                level2();               //constructor
                                        //level start point
                bool play(user * play) override;
                                        //check if completed
                bool is_complete() const override;

        private:
                //structs 
		enum TRIALID		//trial ids
		{
			TRUTH = 0,
			MEMORY,
			LIGHT
		};
		struct trial		//used to track if trials are attempted/completed so 
		{			//others can be made more difficult
			std::string name;
			bool passed;
			bool attempted;
		};
		struct truth_riddle	//used in truth trial
		{
			std::string question;
			std::string answer;
		};
		struct frag		//used in memory trial
		{
			std::string focus;
			std::string memory;
			std::string part;
		};
		struct poem		//used in light trial
		{
			std::string text;
			std::string answer;
			std::unordered_map<std::string, std::string> clust;
		};
		//control variables
                bool completed;         //has the level been completed
		int num; 		//trials completed
		std::vector<trial> trials;
		//trial helpers
                bool truth_trial();     //riddle challenge
                bool mem_trial();       //memory match challenge
                bool light_trial();      //hidden word challenge
		//internal riddle helpers
		truth_riddle riddle;
		std::vector<std::string> hints;
		std::string guess() const;
		bool check(const std::string & gs, const std::string & ans) const;
		void give_hint(int attempt, int lim) const;
                //internal memory puzzle tools
                std::vector<frag> frags;
                void display_frags();
                bool match_choices();
		//internal hidden words in poems helpers, also uses 'guess' and 'check'
		std::vector<poem> poems;
		const poem& select();
		void display_poem(const poem & po, int attempt);
		void print_hint(int attempt);
};

//Level 3; Annie: Mercy
class level3 : public stage
{
	public:
		level3();
		bool play(user * pl) override;
		bool is_complete() const override;

	private:
		//control variables
		bool completed;		//has the level been completed successfully
		int remain;		//how many stages/souls are left
		//vectors for the maze and position of stuff inside it
		std::vector<std::string> maze;
					//keyed by (x, y) coords
		std::vector<std::pair<int, int>> part;//player's position
		std::vector<std::pair<int, int>> prev;//player's previous position
		std::vector<std::pair<int, int>> exit;//position of the maze's 'exit'
		std::vector<std::pair<int, int>> soul;//soul's position
		std::vector<std::vector<int>> dist_map;//BFS distance map cache for chase
		//core maze functions
		void load_default();
		void mirror_maze();	//chase helper with mirrored default maze and only 1 'S'
		void draw_maze() const;
		char get_input() const;
		bool try_move(std::pair<int, int> & pos, const std::pair<int, int> & mov);
		int souls_index(const std::pair<int, int> & pos) const;
		//event handlers
		std::vector<int> spirit;//soul/encounter type
		bool peaceful(user * pl, int soul_id);
		bool logic(user * pl, int soul_id);
		bool chase(user * pl, int soul_id);
		//helpers		//returns direction of player's next tile
		void print_intro();	//level intro message
		bool interact(user * pl);//handles which spirit encountered
		bool check_end(user * pl);//win/lose conditions/messages
		std::pair<int, int> play_direction(char c);
		bool try_soul();	//tries to move S
		int collision(user * pl);//if S catches up to P
		bool check_exit();	//checks if player has reached the exit
					//for bfs movement towards the player
		std::vector<std::vector<int>> update_map(const std::pair<int, int> & start);
		std::pair<int, int> soul_path(const std::pair<int, int> & pos);
};

//Level 4; Rory: Vengeance
class level4 : public stage
{
	public:
		level4();
		bool play(user * play) override;
		bool is_complete() const override;
	
	private:
		bool completed;		//has the level been completed
		bool scout(user * p);	//fight against scout
		bool trap_escape();	//esccape a trap(simple puzzle)
		bool leader(user * p);	//final boss fight
					//helper for rage/clarity mechanic in leader fight
		bool rage_clarity(player *p, monster & boss, combat & arena);

};

//Level 5; Ivy: Balance
class level5 : public stage
{
	public:
		level5();
		bool play(user * pl) override;
		bool is_complete() const override;
	
	private:
		//variables
		bool completed;		//has the level been completed
					//monastery map
		std::vector<std::string> map;
					//player's position in the map
		std::pair<int, int> ppos;
					//position of the exit
		std::pair<int, int> exit;
		struct patrol		//sentry patrols
		{			//routes/list of patrol path tiles
			std::vector<std::pair<int, int>> route;
			int step;	//current position index
		};
		std::vector<patrol> sentries;
		int range;		//how far a sentry can see in a straight line
		//functions
		void load_map();	//defines the monastery map and sets positions/routes
		void draw_map() const;	//outputs the map
					//decides which direction player moves in based on char c
		std::pair<int, int> movement(char c) const;
		bool try_move(std::pair<int, int> & pos, const std::pair<int, int> & mov);
		void update_sentries();
		bool check_detection() const;
		bool stealth(user * pl);
		char get_input() const;
		bool confront(user * pl);

};

//Level 6; Maeve: Truth
class level6 : public stage
{
	public: 
		level6();
		bool play(user * pl) override
		bool is_complete() const override;

	private:
		bool completed;		//has the level been completed
		int score;
		//witnesses and their stories
		std::vector<std::string> names;		//size = 3
		std::vector<std::vector<int>> stories;	//per witness sequence of fact IDs
		//facts and notebook
		std::map<int, std::string> facts;	//fact id and display text
							//fact id and list of ids it contradicts(
		std::map<int, std::vector<int>> contradicts;//(symmetric)
		std::map<int, int> notebook;		//fact id and 0: unknown, 1: true, 2: false
		std::map<int, int> claimed;		//fact id and witness index
		int truth;				//correct story, 0-2 = specific witness's story
							//	3 = composite reconstruction is correct
		//setup
		void load_case();
		void add_contradiction(int a, int b);
		//UI/Flow
		void intro();
		void menu();
		void show_witness(int idx) const;
		void show_notebook() const;
		void list_facts() const;
		void mark_fact();
		void mark_contradict(int id, int state);
		void explain(int id) const;
		//resolution
		int choose() const;
		int tally_score() const;
//		int award(user * pl, int score, bool verdict);

};
/*
//Level 7; Tav: Morality
class level7 : public stage
{
	public:
		level7();
		bool play(user * play) override;
		bool is_complete() const override;
	
	private:
		bool completed;		//has the level been completed
		//functions...

};

//Level 8; Aurora: Altruism VS Ambition
class level8 : public stage
{
	public:
		level8();
		bool play(user * play) override;
		bool is_complete() const override;
	
	private:
		bool completed;		//has the level been completed
		//functions

};

//Level 9; Ben: Decide-- the End
class level9 : public stage
{
	public:
		level9();
		bool play(user * play) override;
		bool is_complete() const override;

	private:
		bool completed;		//has the level been completed
		//functions...

};
*/

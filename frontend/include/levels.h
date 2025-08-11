/* Ben Rohman, benrohman3@gmail.com
 * All declarations and function prototypes for the 9 levels 	*/

#pragma once

#include <queue>			//record movement
#include <climits>			//defines parameters that characterize ints
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
		//combat helpers
		void display_stats(player * p, monster & wraith);
		bool player_action(player * p, monster & wraith);
		int choose_action(player * p, bool mag);
		bool weap_action(player * p, monster & wraith);
		bool spell_action(player * p, monster & wraith);
		bool item_action(player * p);
		void wraith_action(player * p, monster & wraith);
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
		char get_input()  const;
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



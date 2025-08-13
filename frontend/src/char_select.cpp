/* Ben Rohman, benrohman3@gmail.com
 *
 * Implementation of the functions used to allow the user to select a character to play as   */

#include "game.h"
#include "flow_control.h"

//starts the process of character selection, should return a 'player' pointer
user * intros()
{
	//variables
	delegate * tmp {nullptr};
	std::string input;
	
	std::cout << "\nSelect the character you want to preview. \nEnter 'ready' when you're ready "
		  << "to make your final selection. " << std::endl;

	while (true)
	{
		input = char_menu();	//display character options and make them lowercase

		if (input == "ready")
		{
			tmp = select_char();	//character selection phase
			return new user(tmp);	//return wrapped player character
		}

		tmp = create_del(input);	//map name to character object

		if (tmp)
		{
			tmp->intro();		//call character class's member function intro
			delete tmp;		//clean up temp object
			tmp = nullptr;
		}
		else
			std::cout << "Invalid class name. Try again. " << std::endl;
	}

}

//Menu to view character backgrounds/base stats & when ready to select one to play as
std::string char_menu()
{
	//variables
	std::string name;	//record user input

	std::cout << "\nChoose a class by typing its name: \n(1) Paladin \n(2) Cleric \n(3) Rogue \n(4) "
		  << "Wizard \n(5) Bard \n(6) Monk \n(7) Sorcerer \n(8) Barbarian \n(9) Artificer "
		  << "\nEnter class name here: ";
	std::getline(std::cin, name);
	
	//ensure string is lowercase for easy look up
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	return name;
}

//reads in which character the user wants to play as and sends it over to make a char class object
delegate * select_char()
{
	//variables
	std::string input;	//which class the user wants to play as	
	char res {' '};		//user confirmation of choice
	delegate * tmp {nullptr};

	std::cout << "\nSelect the character you want to play as: ";

	do
	{
		input = char_menu();		//get user input

		tmp = create_del(input);	//create character object

		if (tmp)
		{
			std::cout << "You chose <" << tmp->get_name() << "> Do you want to "
				  << "play as this character? (y/n): ";
			std::cin >> res;
			std::cin.ignore(100, '\n');
			res = static_cast<char>(std::tolower(res));

			if (res == 'y')		//if user confirms character selection, display backstory
			{			//	and return the tmp pointer
				clear_screen();	
				std::cout << "\n--------- " << tmp->get_name() << "'s Backsstory "
				          << "--------- \n";
				tmp->disp_backstory();
				std::cout << "\n --------- End --------- \n";
				return tmp;
			}

			std::cout << "\nLets try again... " << std::endl;

			delete tmp;
			tmp = nullptr;
		}
		else
			std::cout << "Invalid input. Try again. " << std::endl;
	}	while (true);
}

//alt version of create_del using an unordered map
delegate * create_del(const std::string & input)
{
	static const std::unordered_map<std::string, std::function<delegate*()>> factory = 
	{
		{"paladin", 	[]() { return new paladin(); }},
		{"cleric", 	[]() { return new cleric(); }},
		{"rogue", 	[]() { return new rogue(); }},
		{"wizard", 	[]() { return new wizard(); }},
		{"bard",	[]() { return new bard(); }},
		{"monk",	[]() { return new monk(); }},
		{"sorcerer",	[]() { return new sorcerer(); }},
		{"barbarian",	[]() { return new barbarian(); }},
		{"artificer",	[]() { return new artificer(); }}
	};
	//store user input in temp string
	std::string name = input;
	//find it in the unordered map
	auto it = factory.find(name);
	if (it != factory.end())
		return it->second();		//call constructor function
	return nullptr;

}


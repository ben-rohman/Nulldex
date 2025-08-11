/* Ben Rohman, benrohman3@gmail.com
 * 
 * These will be tester functions to make sure my program/functions are doing what they are supposed 
 * 	to. 
 */

#include "game.h"

//validates that 'user * mc' is set correctly
bool validate_user(user * mc)
{
	if (!mc)
	{
		std::cerr << "Failed to create character.\n";
		return false;
	}
	return true;
}

//validates that 'player * pc' is set correctly
bool validate_player(player * pc, user * mc)
{
	if (!pc)
	{
		std::cerr << "Failed to get player from user.\n";
		delete mc;
		return false;
	}
	return true;
}

//displays the player's info/stats
void display_stats(player * pc)
{
	std::cout << "\nName: " << pc->get_name() << "\nLevel: " << pc->get_lvl() 
	          << "\nEXP: " << pc->get_exp() << "\nEXP Needed to Level Up: " 
	          << pc->get_exp_to_next() << "\nHP: " << pc->get_curr_hp() << '/' 
	          << pc->get_maxhp() << "\nMP: " << pc->get_curr_mp() << '/' << pc->get_maxmp() 
	          << "\nTotal Strength: " << pc->get_tstr() << "\nTotal Intelligence: " << pc->get_tint()
		  << "\nTotal Agility: " << pc->get_tagil() << "\nTotal Armor: " << pc->get_tarm()
		  << "\nTotal Elemental Resistance: " << pc->get_telem_res() 
		  << std::endl;
}

//equips items and adds others to player's inventory
void equip_test(player * pc)
{
	//create and equip armor

/******************************** Mega Powerful Armor and Weapon **************************************
	item * cp = manager::create_armor("Diamond Plate Armor", core(9, 9, 9, 9, 9), ARMORSLOT::CHEST);
	item * he = manager::create_armor("Diamond Helmet", core(9, 9, 9, 9, 9), ARMORSLOT::HELMET);
	manager::equip(cp, pc);
	manager::equip(he, pc);

	item * sword = manager::create_weapon("Big Ahh Sword", core(9, 9, 9, 9, 9), WEAPONSLOT::MELEE, 10, 20);
	manager::equip(sword, pc);
*/		
/********************************* Mid Armor and Weapon ***************************************************/	
	item * plate = manager::create_armor("Shiny Plate Armor", core(0, 0, 0, 5, 3), 
					     ARMORSLOT::CHEST);
	item * helm = manager::create_armor("Leather Helmet", core(0, 0, 0, 2, 1),
					    ARMORSLOT::HELMET);
	manager::equip_item(plate, pc);
	manager::equip_item(helm, pc);
	//create and equip weapons
	item * sword = manager::create_weapon("Long Sword", core(), WEAPONSLOT::MELEE, 3, 9);
	manager::equip_item(sword, pc);

/********************************* Basically Naked *****************************************************
	item * pap = manager::create_armor("Paper Shawl", core(0, 1, 0, 1, 0), ARMORSLOT::CHEST);
	item * lef = manager::create_armor("Dead Leaf", core (1, 0, 1, 0, 1), ARMORSLOT::HELMET);
	manager::equip(pap, pc);
	manager::equip(lef, pc);
	item * stick = manager::create_weapon("Small Stick", core(1, 1, 1, 1, 1), WEAPONSLOT::MELEE, 2, 3);
	manager::equip(stick, pc);

*/
/************************************** Other Mechanics ***************************************************
	manager::move_to_backpack(manager::create_weapon("Rusty Hand Axe", core(), 
				  WEAPONSLOT::MELEE, 2, 4), pc);//extra moved to backpack
*/
	//create and store potions
	item * pot = manager::create_potion("Heal Potion", 3u, 3u);
	manager::move_to_backpack(pot, pc);

}

//simulates the player taking damage and
void simulate(player * pc)
{
	//HP before taking damage
	std::cout << "\nHP Before Damage: " << pc->get_curr_hp() << '/' << pc->get_maxhp() 
		  << std::endl;
	//player takes damage
	pc->damage(5);
	//HP after damage
	std::cout << "HP After Damage: " << pc->get_curr_hp() << '/' << pc->get_maxhp() 
		  << std::endl;
	//Try to heal using a potion
	if (!first_used(pc))	//failure
		std::cout << "No potion used (either not needed or not available)\n";
	//success
	std::cout << "HP After Healing: " << pc->get_curr_hp() << '/' << pc->get_maxhp() 
		  << std::endl;

}

//Begins process of displaying player's backpack and all items
void display_backpack(player * pc)
{
	//temp vector
	std::vector<item*> bag = pc->get_backpack_list();
	if (bag.empty())
		std::cout << "\n\n[ Backpack is empty ] ";
	else
	{
		for (size_t i = 0; i < bag.size(); ++i)
			std::cout << i + 1 << ". " << describe_item(bag[i]) << '\n';
	}
}

//This function will attempt to figure out what an item in the player's backpack is and output it
std::string describe_item(const item * it)
{
	if (!it || !it->get_data())	//error check
		return " [INVALID ITEM] ";
	
	const item_delegate * data = it->get_data();
	
	armor * arm {nullptr};		//temp pointers
	weapon * weap {nullptr};
	potion * pot {nullptr};

	//is it armor?
	manager::cast_to_armor(it, arm);
	if (arm)
	{	
		return "Armor: " + arm->name + " (Slot: " + 
		       std::to_string(static_cast<int>(arm->slot)) + ")";
	}
	//not armor, is it a weapon?
	manager::cast_to_weapon(it, weap);
	if (weap)
	{
		return "Weapon: " + weap->name + " (Damage: " + std::to_string(weap->min_damage) +
		       "-" + std::to_string(weap->max_damage) + ")";
	}
	//not armor AND not a weapon, is it a potion?
	manager::cast_to_potion(it, pot);
	if (pot)
	{
		return "Potion: " + pot->name + " (Qty: " + std::to_string(pot->quantity) +
		       ", Heals: " + std::to_string(pot->heal_amount) + ")";
	}
	//item isn't armor, a weapon or potion so something went wrong
	return " [UNKNOWN ITEM] " + data->name;
}

//helper function for using a potion, uses first one found
bool first_used(player * pc)
{
	for (item * it : pc->get_backpack_list())
	{
		if (!it || !it->get_data())
			continue;

		potion * pot {nullptr};
		manager::cast_to_potion(it, pot);
		if (pot && pot->quantity > 0 && manager::use(it, pc))
		{
			std::cout << "\n---------- Potion Used: " << pot->name << "---------\n";
			return true;
		}
	}
	return false;
}

//helper function to display the player's equipped weapons
void display_weap(const player * pc)
{
	std::cout << "\n[ Equipped Weapons ] " << std::endl;
	for (unsigned long long i = 0; i < static_cast<unsigned long long>(WEAPONSLOT::NUM_SLOTS); ++i)
	{
		const weapon * wp = pc->get_equip_weapon(i);
		if (wp)
			std::cout << "\nSlot: " << i << ": " << wp->name << " | Min Damage: "
				  << wp->min_damage << ", Max Damage: " << wp->max_damage
				  << ", Two Handed: " << (wp->is_2h ? "Yes" : "No") << std::endl;
		else
			std::cout << "\nSlot " << i << ": [Empty] " << std::endl;
	}
}

//helper function to display the player's equipped armor
void display_arm(const player * pc)
{
	std::cout << "\n [ Equipped Armor ] " << std::endl;
	for (unsigned long long i = 0; i < static_cast<unsigned long long>(ARMORSLOT::NUM_SLOTS); ++i)
	{
		const armor * ar = pc->get_equip_armor(i);
		if (ar)
			std::cout << "\nSlot " << i << ": " << ar->name << " | Slot Type: " 
				  << static_cast<int>(ar->slot) << " | Core Stats -- Strength: "
				  << ar->stats.strength << ", Intellect: " << ar->stats.intellect
				  << ", Agility: " << ar->stats.agility << ", Armor: " 
				  << ar->stats.armor << ", Elemental Resistance: " << std::endl;
		else
			std::cout << "Slot " << i << ": [Empty] " << std::endl;
	}
}

//displays the player's entire list of abilities
void display_abils(const player * pc)
{
	if (!pc)		//error check
		return;
	const std::vector<ability*> abil = pc->get_abil_list();

	if (abil.empty())
	{
		std::cout << "No abilities learned.\n";
		return;
	}

	for (size_t i = 0; i < abil.size(); ++i)
	{
		const ability * a = abil[i];
		if (!a)
			continue;

		std::cout << '\n' << i + 1 << ". " << a->get_name() << " | HP Effect: " << a->get_hpe()
			  << " | Cost: " << a->get_cost() << " | Cooldown: " << a->get_cd()
			  << " | Target: " << static_cast<int>(a->get_target()) << " | Scaler: "
			  << " | Scaler: " << static_cast<int>(a->get_scaler());
		
		const buff * b = a->get_buff();
		if (b)
		{
			std::cout << " | Buff: " << b->name << " (Duration: " << b->duration
				  << ", Debuff: " << (b->is_debuff ? "Yes" : "No") << ')'
				  << std::endl;
		}
	}
}

//searches for and (if found) displays a specified ability
bool specif_abil(const player * pc, const std::string & find)
{
	if (!pc)
		return false;
	
	const std::vector<ability*> abil = pc->get_abil_list();
	for (const ability * a : abil)
	{
		if (a && a->get_name() == find)
			return true;
	}
	return false;
}

//displays the player's entire list of active buffs
void display_buffs(const player * pc)
{
	if (!pc)
		return;

	const std::vector<buff> buffs = pc->get_buff_list();

	if (buffs.empty())
	{
		std::cout << "No active buffs.\n";
		return;
	}

	for (size_t i = 0; i < buffs.size(); ++i)
	{
		const buff & b = buffs[i];
		std::cout << i + 1 << ". " << b.name << " | STR: " << b.buffed.strength
			  << " | INT: " << b.buffed.intellect << " | AGI: " << b.buffed.agility
			  << " | ARM: " << b.buffed.armor << " | Elemental Resistance: "
			  << b.buffed.elem_res << " | Duration: " << b.duration << " | "
			  << (b.is_debuff ? "[DEBUFF]" : "[BUFF]") << std::endl;
	}
}

//searches for and (if found) displays a specified ability
bool specif_buff(const player * pc, const std::string & find)
{
	if (!pc)
		return false;
	
	const std::vector<buff> buffs = pc->get_buff_list();
	for (const buff & b : buffs)
	{
		if (b.name == find)
			return true;
	}
	return false;
}

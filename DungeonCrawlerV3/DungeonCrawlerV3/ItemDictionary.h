#pragma once

#include "Item.h"
#include "Potion.h"
#include "Enchantment.h"

#include <map>
#include <vector>


class ItemDictionary {
	using ItemMap = std::map<const char*,Item*>;

private:
	static ItemDictionary* _instance;
	Item NullItem = Item("Null", 0);

	ItemMap _itemsInterface{ {"Null", &NullItem} };
	
	//potions
	HealPotion _healPotion = HealPotion("Heal Potion", 10);
	LifeStealPotion _lifeStealPotion = LifeStealPotion("Life Steal Potion", 15);
	RegenPotion _regenPotion = RegenPotion("Regeneration Potion", 20);

	ItemMap _potionsInterface{ 
		{"Heal", &_healPotion}, 
		{"Life Steal", &_lifeStealPotion}, 
		{"Regeneration", &_regenPotion} };

	ItemMap _enchanmentsInterface{ {"Null", &NullItem} };

private:
	ItemDictionary() = default;

public:
	static ItemDictionary Instance();

	inline ItemMap GetItems() { return _itemsInterface; }
	inline ItemMap GetPotions() { return _potionsInterface; }
	inline ItemMap GetEnchants() { return _enchanmentsInterface; }
};
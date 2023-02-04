#pragma once

#include "Item.h"
#include "Potion.h"
#include "Enchantment.h"

#include <map>


class ItemDictionary {
	using ItemMap = std::map<const char*,Item*>;

private:
	static ItemDictionary* _instance;
	Item NullItem = Item("Null", 0);
	//Items
	Item _bone = Item("Bone", 2);
	Item _scrapCloth = Item("Scrap Cloth", 1);
	Item _rustedSword = Item("Rusted Sword", 5);
	ItemMap _itemsInterface{ 
		{"Bone", &_bone},
		{"Scrap Cloth", &_scrapCloth},
		{"Rusted Sword", &_rustedSword}
	};
	
	//potions
	HealPotion _healPotion = HealPotion("Heal Potion", 10);
	LifeStealPotion _lifeStealPotion = LifeStealPotion("Life Steal Potion", 15);
	RegenPotion _regenPotion = RegenPotion("Regeneration Potion", 20);

	ItemMap _potionsInterface{ 
		{"Heal", &_healPotion}, 
		{"Life Steal", &_lifeStealPotion}, 
		{"Regeneration", &_regenPotion} };


	//enchantments
	Enchantment _skeletonEnchant = Enchantment("Skeleton Enchantment", 50, Enchant("Skeleton Enchant", 0.1, &Character::_attackModifier));

	ItemMap _enchanmentsInterface{ {"Null", &NullItem} };

private:
	ItemDictionary() = default;

public:
	static ItemDictionary Instance();

	inline ItemMap GetItems() { return _itemsInterface; }
	inline ItemMap GetPotions() { return _potionsInterface; }
	inline ItemMap GetEnchants() { return _enchanmentsInterface; }
};
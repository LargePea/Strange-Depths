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

	ItemMap _itemsInterface{
		{"Gel", new Item("Gel", 1)},
		{"Purified Gel", new Item("Purified.Gel", 4)},
		{"Crystalized Gel", new Item("Crystalized.Gel", 8)},
		{"Bone", new Item("Bone", 2)},
		{"Scrap Cloth", new Item("Scrap.Cloth", 1)},
		{"Rusted Sword", new Item("Rusted.Sword", 5)},
		{"Tattered Photo", new Item("Tattered.Photo", 3)},
		{"Ectoplasm", new Item("Ectoplasm", 4)},
		{"Lost Soul", new Item("Lost.Soul", 10)},
		{"Club", new Item("Club", 3)},
		{"Ogre Skin", new Item("Ogre.Skin", 5)},
		{"Onion", new Item("Onion", 7)},
		{"KeyStone", new Item("KeyStone", 500)}
	};
	
	//potions

	ItemMap _potionsInterface{ 
		{"Heal", new HealPotion("Heal.Potion", 10)},
		{"Life Steal", new LifeStealPotion("Life.Steal.Potion", 15)},
		{"Regeneration", new RegenPotion("Regeneration.Potion", 20)}
	};

	//enchantments

	ItemMap _enchantmentsInterface{
		{"Slime", new Enchantment("Slime.Enchantment", 50, Enchant("Slime.Enchant", 0.1f, Enchant::EnchanmentTypes::CritRate))},
		{"Skeleton", new Enchantment("Skeleton.Enchantment", 50, Enchant("Skeleton.Enchant", 0.1f, Enchant::EnchanmentTypes::Attack))},
		{"Banshee", new Enchantment("Banshee.Enchantment", 65, Enchant("Banshee.Enchant", 0.55f, Enchant::EnchanmentTypes::Speed))},
		{"Ogre", new Enchantment("Ogre.Enchantment", 70, Enchant("Ogre.Enchant", 0.1f, Enchant::EnchanmentTypes::Defense))}
	};

private:
	ItemDictionary() = default;

public:
	static ItemDictionary Instance();

	inline ItemMap GetItems() { return _itemsInterface; }
	inline ItemMap GetPotions() { return _potionsInterface; }
	inline ItemMap GetEnchants() { return _enchantmentsInterface; }

	inline Item*& GetItem(const char* itemKey) { return _itemsInterface[itemKey]; }
	inline Item*& GetPotion(const char* itemKey) { return _potionsInterface[itemKey]; }
	inline Item*& GetEnchant(const char* itemKey) { return _enchantmentsInterface[itemKey]; }
};
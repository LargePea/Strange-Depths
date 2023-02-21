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
	Item _gel = Item("Gel", 1);
	Item _purifiedGel =Item("Purified Gel", 4);
	Item _crystalizedGel = Item("Crystalized Gel", 8);
	Item _bone = Item("Bone", 2);
	Item _scrapCloth = Item("Scrap Cloth", 1);
	Item _rustedSword = Item("Rusted Sword", 5);
	Item _tatteredPhoto = Item("Tattered Photo", 3);
	Item _ectoplasm = Item("Ectoplasm", 4);
	Item _lostSoul = Item("Lost Soul", 10);
	Item _club = Item("Club", 3);
	Item _ogreSkin = Item("Ogre Skin", 5);
	Item _onion = Item("Onion", 7);
	Item _key = Item("KeyStone", 5);

	ItemMap _itemsInterface{
		{"Gel", &_gel},
		{"Purified Gel", &_purifiedGel},
		{"Crystalized Gel", &_crystalizedGel},
		{"Bone", &_bone},
		{"Scrap Cloth", &_scrapCloth},
		{"Rusted Sword", &_rustedSword},
		{"Tattered Photo", &_tatteredPhoto},
		{"Ectoplasm", &_ectoplasm},
		{"Lost Soul", &_lostSoul},
		{"Club", &_club },
		{"Ogre Skin", &_ogreSkin},
		{"Onion", &_onion},
		{"KeyStone", &_key}
	};
	
	//potions
	HealPotion _healPotion = HealPotion("Heal Potion", 10);
	LifeStealPotion _lifeStealPotion = LifeStealPotion("Life Steal Potion", 15);
	RegenPotion _regenPotion = RegenPotion("Regeneration Potion", 20);

	ItemMap _potionsInterface{ 
		{"Heal", &_healPotion}, 
		{"Life Steal", &_lifeStealPotion}, 
		{"Regeneration", &_regenPotion} 
	};

	//enchantments
	Enchantment _slimeEnchant = Enchantment("Slime Enchantment", 50, Enchant("Slime Enchant", 0.1f, Enchant::EnchanmentTypes::CritRate));
	Enchantment _skeletonEnchant = Enchantment("Skeleton Enchantment", 50, Enchant("Skeleton Enchant", 0.1f, Enchant::EnchanmentTypes::Attack));
	Enchantment _bansheeEnchant = Enchantment("Banshee Enchantment", 65, Enchant("Banshee Enchant", 0.55f, Enchant::EnchanmentTypes::Speed));
	Enchantment _ogreEnchant = Enchantment("Ogre Enchantment", 70, Enchant("Ogre Enchant", 0.1f, Enchant::EnchanmentTypes::Defense));

	ItemMap _enchantmentsInterface{
		{"Slime", &_slimeEnchant},
		{"Skeleton", &_skeletonEnchant},
		{"Banshee", &_bansheeEnchant},
		{"Ogre", &_ogreEnchant}
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
#include "Ogre.h"
#include "ItemDictionary.h"

Ogre::Ogre() : 
	Enemy(20, 4.5f, 8, 0.1f, 2, "Ogre", 45, 0.5, Image(OGRE, 2, { 46, 9 })) {
	static ItemDictionary instance = ItemDictionary::Instance();
	static LootTable ogreLootTable({
		{instance.GetItem("Club"), 35},
		{instance.GetItem("Ogre Skin"), 30},
		{instance.GetItem("Onion"), 5},
		{instance.GetPotion("Heal"), 15},
		{instance.GetPotion("Life Steal"), 10},
		{instance.GetEnchant("Ogre"), 1}
		});

	_possibleDrops = ogreLootTable;
}
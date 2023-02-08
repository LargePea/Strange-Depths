#include "Slime.h"
#include "ItemDictionary.h"

Slime::Slime() : 
	Enemy(10, 2, 2, 0.3f, 6, "Slime", 15, 0.6f) {
	static ItemDictionary instance = ItemDictionary::Instance();
	static LootTable slimeLootTable({
		{instance.GetItem("Gel"), 40},
		{instance.GetItem("Purified Gel"), 25},
		{instance.GetItem("Crystalized Gel"), 8},
		{instance.GetPotion("Heal"), 10},
		{instance.GetEnchant("Slime"), 1}
		});

	_possibleDrops = slimeLootTable;
}
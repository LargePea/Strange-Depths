#include "Banshee.h"
#include "ItemDictionary.h"

Banshee::Banshee() :
	Enemy(12, 8, 0, 0.35f, 7.5f, "Banshee", 30, 0, Image(BANSHEE, 2, { 35, 18 }))
{
	static ItemDictionary instance = ItemDictionary::Instance();
	static LootTable bansheeLootTable({
		{instance.GetItem("Tattered Photo"), 30},
		{instance.GetItem("Ectoplasm"), 40},
		{instance.GetItem("Demonic Essence"), 8},
		{instance.GetPotion("Heal"), 15},
		{instance.GetPotion("Life Steal"), 10},
		{instance.GetEnchant("Banshee"), 1}
		});

	_possibleDrops = bansheeLootTable;
}
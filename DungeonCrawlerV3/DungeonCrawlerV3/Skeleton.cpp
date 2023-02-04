#include "Skeleton.h"
#include "ItemDictionary.h"

Skeleton::Skeleton() : 
	Enemy(15, 5, 2, .2f, 5.5f, "Skeleton", 20, 0.4) {
	static ItemDictionary instance = ItemDictionary::Instance();
	static LootTable skeletonLootTable({
		{instance.GetItems()["Bone"], 10},
		{instance.GetItems()["Scrap Cloth"], 20},
		{instance.GetItems()["Rusted Sword"], 5},
		{instance.GetPotions()["Heal"], 6},
		{instance.GetPotions()["Life Steal"], 3}

		});

	_possibleDrops = skeletonLootTable;
}
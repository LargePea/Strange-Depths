#include "Slime.h"
#include "ItemDictionary.h"
#include "SpriteAtlas.h"

Slime::Slime() : 
	Enemy(10, 3, 2, 0.3f, 6, "Slime", 15, 0.6f, Image(SLIME, 2, { 37, 18 })) {
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
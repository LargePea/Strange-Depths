#include "Mimic.h"
#include "ItemDictionary.h"

Mimic::Mimic(LootTable _chestLootTable, int mimicValue) :
	Enemy(1, 5, 0, 0, 10, "Mimic", mimicValue, 0, Image(MIMIC, 2, { 42, 20 })) {

	_possibleDrops = _chestLootTable;
}
#include "LootTable.h"

LootTable::LootTable(std::initializer_list<std::pair<Item*, float>> startingLoot) {
	for (auto& pair : startingLoot) {
		_lootList.insert(pair);
		_totalTableWeight += pair.second;
	}
}
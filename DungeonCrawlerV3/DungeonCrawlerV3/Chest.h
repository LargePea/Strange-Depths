#pragma once

#include "LootTable.h"

class Chest {
private:
	LootTable _chestLootTable;
	int _maxChestValue;
	float _mimicSpawnChance;

public:
	Chest(LootTable lootTable, int maxChestValue, float mimicSpawnChance);
	void OpenChest();
	void RejectChest();
};
#pragma once

#include "LootTable.h"
#include "Image.h"

class Chest {
private:
	LootTable _chestLootTable;
	int _maxChestValue;
	float _mimicSpawnChance;
	Image _chestImage;

public:
	Chest(LootTable lootTable, int maxChestValue, float mimicSpawnChance);
	void OpenChest();
	void RejectChest();
	void DisplayChest();
	void HideChest();

	~Chest() { HideChest(); }
};
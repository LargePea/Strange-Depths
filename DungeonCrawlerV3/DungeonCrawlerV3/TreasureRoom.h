#pragma once

#include "Room.h"
#include "LootTable.h"
#include "Player.h"

class TreasureRoom : public Room {
	friend class Room;

	int _maxChestValue = 40;
	float _mimicSpawnChance = (float)GetCurrentDifficulty() / (float)2;
	float const _chestSpawnChance = 10;

	LootTable _chestLootTable;

protected:
	TreasureRoom();

private:
	void OpenChest(Player& player);
};
#pragma once

#include "Room.h"
#include "LootTable.h"
#include "TreasureRoomAM.h"
#include "Chest.h"

class TreasureRoom : public Room {
friend class Room;
friend class TreasureRoomAM;

	int _maxChestValue = 40;
	float _mimicSpawnChance = (float)GetCurrentDifficulty() / (float)2;
	float const _chestSpawnChance = 10;

	TreasureRoomAM _actionMap;
	Chest _chest;
	
private:
	Chest GenerateChest();

protected:
	TreasureRoom();

public:
	~TreasureRoom() override = default;
};
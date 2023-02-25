#include "TreasureRoom.h"
#include "ItemDictionary.h"
#include "TreasureRoomAM.h"

TreasureRoom::TreasureRoom() 
	: _chest(GenerateChest()), _actionMap(TreasureRoomAM(&_chest)) 
{
	ActionMap::AddActionMap(&_actionMap);
	_chest.DisplayChest();
}

Chest TreasureRoom::GenerateChest() {
	static ItemDictionary instance = ItemDictionary::Instance();

	LootTable chestLoot = LootTable({
		{instance.GetPotion("Heal"), 10 + (float)GetCurrentDifficulty() / (float)2},
		{instance.GetPotion("Life Steal"), 5 + GetCurrentDifficulty()},
		{instance.GetPotion("Regeneration"), 2 + GetCurrentDifficulty() + (float)GetCurrentDifficulty() / (float)2}
		});

	float chestValue = _maxChestValue * (1 + (float)GetCurrentDifficulty() / (float)2);

	float mimicSpawnChance = _mimicSpawnChance / (_mimicSpawnChance + _chestSpawnChance);

	return Chest(chestLoot, chestValue, mimicSpawnChance);
}
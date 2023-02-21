#include "Chest.h"
#include "ActionMap.h"
#include "Mimic.h"
#include "GameManager.h"
#include "InventoryMenu.h"
#include <random>
#include <array>

Chest::Chest(LootTable lootTable, int maxChestValue, float mimicSpawnChance)
	: _chestLootTable(lootTable), _maxChestValue(maxChestValue), _mimicSpawnChance(mimicSpawnChance) {}

void Chest::OpenChest() {
	ActionMap::PopCurrentMap(); //pop the treasure actionmap off
	static std::default_random_engine engine;

	std::bernoulli_distribution spawnMimic(_mimicSpawnChance);
	std::normal_distribution<float> coinsGenerated(_maxChestValue / 2, 1.5f);

	if (spawnMimic(engine)) {
		Mimic mimic{ _chestLootTable, (int)coinsGenerated(engine) };
		GameManager::BeginCombat(&mimic);
	}
	else {
		std::array<Item*, 5> createdLoot;
		_chestLootTable.CreateLoot(createdLoot);

		for (auto& item : createdLoot) {
			InventoryMenu::AddItem(item);
		}
		int coins = coinsGenerated(engine);
		InventoryMenu::AddCoins(coins);
	}
}

void Chest::RejectChest() {
	ActionMap::PopCurrentMap();
}
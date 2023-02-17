#include "TreasureRoom.h"
#include "ItemDictionary.h"
#include "InventoryMenu.h"
#include "Mimic.h"
#include "GameManager.h"
#include <random>
#include <array>

TreasureRoom::TreasureRoom() {
	static ItemDictionary instance = ItemDictionary::Instance();
	_chestLootTable = LootTable({
		{instance.GetPotion("Heal"), 10 + (float)GetCurrentDifficulty() / (float)2},
		{instance.GetPotion("Life Steal"), 5 + GetCurrentDifficulty()},
		{instance.GetPotion("Regen"), 2 + GetCurrentDifficulty() + (float) GetCurrentDifficulty() / (float)2}
		});
}

void TreasureRoom::OpenChest(Player& player) {
	static std::default_random_engine engine;

	std::bernoulli_distribution spawnMimic(_mimicSpawnChance / (_mimicSpawnChance + _chestSpawnChance));
	std::normal_distribution<float> coinsGenerated(_maxChestValue / 2, 1.5f);

	if (spawnMimic(engine)) {
		GameManager::BeginCombat(Mimic(_chestLootTable, coinsGenerated(engine)));
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
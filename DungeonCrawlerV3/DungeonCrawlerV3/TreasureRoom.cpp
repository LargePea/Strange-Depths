#include "TreasureRoom.h"
#include "ItemDictionary.h"
#include "Mimic.h"
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
		//spawn mimic and start combat
	}
	else {
		std::array<Item*, 5> createdLoot;
		_chestLootTable.CreateLoot(createdLoot);

		for (auto& item : createdLoot) {
			player.GetInventory()->AddItem(item);
		}
		int coins = coinsGenerated(engine);
		player.GetInventory()->AddCoins(coins);
	}
}
#include "Chest.h"
#include "ActionMap.h"
#include "Mimic.h"
#include "GameManager.h"
#include "InventoryMenu.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "Screen.h"
#include "ChestAnimator.h"
#include <random>
#include <array>

Chest::Chest(LootTable lootTable, int maxChestValue, float mimicSpawnChance)
	: _chestLootTable(lootTable), _maxChestValue(maxChestValue), _mimicSpawnChance(mimicSpawnChance), _chestImage(CLOSEDCHEST, 2, {42, 22}) {}

void Chest::DisplayChest() {
	Screen::AddImages({ &_chestImage });
}

void Chest::HideChest() {
	Screen::RemoveImages({ &_chestImage });
	if (_chestAnimator != nullptr) delete _chestAnimator;
}

void Chest::OpenChest() {
	ActionMap::PopCurrentMap(); //pop the treasure actionmap off
	static std::default_random_engine engine;

	std::bernoulli_distribution spawnMimic(_mimicSpawnChance);
	std::normal_distribution<float> coinsGenerated(_maxChestValue / 2, 1.5f);

	if (spawnMimic(engine)) {
		HideChest();
		Mimic mimic{ _chestLootTable, (int)coinsGenerated(engine) };
		mimic.LoadEnemyImage();
		GameManager::BeginCombat(&mimic);
	}
	else {
		std::array<Item*, 5> createdLoot;
		_chestLootTable.CreateLoot(createdLoot, true);

		for (auto& item : createdLoot) {
			InventoryMenu::AddItem(item);
		}
		int coins = coinsGenerated(engine);
		InventoryMenu::AddCoins(coins);

		_chestAnimator = new ChestAnimator(&_chestImage);
		_chestAnimator->ActivateAnimator();
	}
}

void Chest::RejectChest() {
	ActionMap::PopCurrentMap();
}
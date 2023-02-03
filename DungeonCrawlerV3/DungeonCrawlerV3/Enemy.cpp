#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemDictionary.h"
#include <random>
#include <array>

Enemy::Enemy(const char* name) : _name(name), _enemyInventory(*this, CreateStartingItems()) {
}

void Enemy::ChooseAction(Character &other) {

}

void Enemy::UseItem() {

}

void Enemy::Death(Character* killer) {
	Inventory* playerInventory = (static_cast<Player*>(killer))->GetInventory();

	std::array<Item*, _maxDropsPossible> droppedLoot{ nullptr };
	//generate loot
	_possibleDrops.CreateLoot<_maxDropsPossible>(droppedLoot);

	for (auto& loot : droppedLoot) {
		if (loot == nullptr) break;
		playerInventory->AddItem(loot);
	}
}

std::vector<Item*> Enemy::CreateStartingItems() {

	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> randomInventorySize(0, _maxInventoryStartingSize);
	static Item*& healPotion = ItemDictionary::Instance().GetPotions()["Heal"];

	int generatedSize = randomInventorySize(generator);

	std::vector<Item*> startingItems;
	startingItems.reserve(generatedSize);

	for (int i = 0; i < generatedSize; i++) {
		startingItems.emplace_back(healPotion);
	}

	return startingItems;
}
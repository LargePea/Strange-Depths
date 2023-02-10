#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "ItemDictionary.h"
#include <random>
#include <array>

Enemy::Enemy(float maxHealth, float attack, float defense, float critRate, float speed, const char* name, int value, float healingThreshold) :
	Character(maxHealth, attack, defense, critRate, speed), _name(name), _enemyValue(value), _healThreshold(healingThreshold), _enemyInventory(*this, CreateStartingItems()) {
}

void Enemy::ChooseAction(Character& other) {
	Character::ChooseAction(other);

	//attack player if can kill this turn
	if (other.GetCurrentHealth() - _attack < 0)
		Attack(other);
	//heal only if its past heal threshold and there are items to heal
	else if (_currentHealth / _maxHealth < _healThreshold && _enemyInventory.Size() != 0)
		UseItem();
	else 
		Attack(other);
}

void Enemy::UseItem() {
	if ((_enemyInventory.GetItems()[_enemyInventory.Size() - 1])->TryUseItem(*this))
		_enemyInventory.RemoveOrSellItem(_enemyInventory.Size() - 1, false);
}

void Enemy::Death(Character* killer) {
	Character::Death(killer);
	Inventory* playerInventory = (static_cast<Player*>(killer))->GetInventory();
	std::array<Item*, _maxDropsPossible> droppedLoot{ nullptr };
	//generate loot
	_possibleDrops.CreateLoot(droppedLoot);

	for (auto& loot : droppedLoot) {
		if (loot == nullptr) break;
		playerInventory->AddItem(loot);
	}

	playerInventory->AddCoins(_enemyValue);
}

std::vector<Item*> Enemy::CreateStartingItems() {

	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> randomInventorySize(0, _maxInventoryStartingSize);
	static Item*& healPotion = ItemDictionary::Instance().GetPotion("Heal");

	int generatedSize = randomInventorySize(generator);

	std::vector<Item*> startingItems;
	startingItems.reserve(generatedSize);

	for (int i = 0; i < generatedSize; i++) {
		startingItems.emplace_back(healPotion);
	}

	return startingItems;
}
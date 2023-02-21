#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "InventoryMenu.h"
#include "ItemDictionary.h"
#include "Screen.h"
#include <random>
#include <array>

Enemy::Enemy(float maxHealth, float attack, float defense, float critRate, float speed, const char* name, int value, float healingThreshold) :
	Character(maxHealth, attack, defense, critRate, speed), _name(name), _enemyValue(value), _healThreshold(healingThreshold), _enemyInventory(*this, CreateStartingItems()), _enemyStats(_enemyStatsBase) {
}

Enemy::Enemy(const Enemy& enemy)
	: Character(enemy._maxHealth, enemy._baseAttack, enemy._baseDefense, enemy._baseCritRatePercent, enemy._baseSpeed), 
	_name(enemy._name), _enemyValue(enemy._enemyValue), _healThreshold(enemy._healThreshold), _enemyInventory(enemy._enemyInventory), _possibleDrops(enemy._possibleDrops), _enemyStats(_enemyStatsBase) {

}

void Enemy::LoadEnemyImage() {
	UpdateStatsMenu();
	Screen::AddImages({ &_enemyStats });
}

void Enemy::UpdateStatsMenu() {
	std::vector<std::string> stats{std::to_string((int)_currentHealth), "", "", "", std::to_string((int)_defense), "", "", "", std::to_string((int)_attack)};

	_enemyStats = _enemyStatsBase + Image(stats, 2, {12, 9});
}

void Enemy::Damage(const float& incomingDamage, Character& attacker) {
	Character::Damage(incomingDamage, attacker);

	UpdateStatsMenu();
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
	if ((_enemyInventory.GetItems()[_enemyInventory.Size() - 1])->TryUseItem(this))
		_enemyInventory.RemoveOrSellItem(_enemyInventory.Size() - 1, false);
}

void Enemy::Death(Character* killer) {
	Screen::RemoveImages({ &_enemyStats });

	std::array<Item*, _maxDropsPossible> droppedLoot{ nullptr };
	//generate loot
	_possibleDrops.CreateLoot(droppedLoot);

	for (auto& loot : droppedLoot) {
		if (loot == nullptr) break;
		InventoryMenu::AddItem(loot);
	}

	InventoryMenu::AddCoins(_enemyValue);
	Character::Death(killer);
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
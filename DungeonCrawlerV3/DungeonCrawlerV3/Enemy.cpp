#include "Enemy.h"
#include "Player.h"
#include "Inventory.h"
#include "InventoryMenu.h"
#include "ItemDictionary.h"
#include "Screen.h"
#include "Notification.h"
#include <random>
#include <array>

Enemy::Enemy(float maxHealth, float attack, float defense, float critRate, float speed, const char* name, int value, float healingThreshold, Image baseImage) :
	Character(maxHealth, attack, defense, critRate, speed), 
	_name(name), _enemyValue(value), _healThreshold(healingThreshold), _enemyInventory(*this, CreateStartingItems()), _enemyStats(_enemyStatsBase), _baseImage(baseImage) {
}

Enemy::~Enemy() {
	Screen::RemoveImages({ &_enemyStats, &_baseImage });
	if (_enemyAnimator != nullptr) delete _enemyAnimator;
}

void Enemy::HideEnemy() {
	Screen::RemoveImages({ &_enemyStats, &_baseImage });
	if (_enemyAnimator != nullptr) delete _enemyAnimator;
}

void Enemy::LoadEnemyImage() {
	UpdateStatsMenu();
	_enemyAnimator->ActivateAnimator();
	Screen::AddImages({ &_enemyStats, &_baseImage });
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
	if (other.GetCurrentHealth() - _attack < 0) {
		_enemyAnimator->SetTrigger("Attack");
		_enemyAnimator->WaitForNextClipCompletion();
		Attack(other);
	}	
	//heal only if its past heal threshold and there are items to heal
	else if (_currentHealth / _maxHealth < _healThreshold && _enemyInventory.Size() != 0)
		UseItem();
	else
	{
		_enemyAnimator->SetTrigger("Attack");
		_enemyAnimator->WaitForNextClipCompletion();
		Attack(other);
	}
}

void Enemy::UseItem() {
	if ((_enemyInventory.GetItems()[_enemyInventory.Size() - 1])->TryUseItem(this))
		_enemyInventory.RemoveOrSellItem(_enemyInventory.Size() - 1, false);
}

void Enemy::Death(Character* killer) {
	Screen::RemoveImages({ &_enemyStats, &_baseImage });
	if (_enemyAnimator != nullptr) {
		delete _enemyAnimator;
		_enemyAnimator = nullptr;
	}
	std::array<Item*, _maxDropsPossible> droppedLoot{ nullptr };
	//generate loot
	_possibleDrops.CreateLoot(droppedLoot);

	{
		Notification deathNotif({
			".You.just.killed.the." + (std::string)_name + ".",
			droppedLoot[0] == nullptr ? ".It.dropped.no.items." : ".It.dropped.some.items!.",
			".Press.Any.Key.To.Continue."
			}, {42, 38});
	}

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
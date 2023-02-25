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
	_name(name), _enemyValue(value), _healThreshold(healingThreshold), _enemyStats(_enemyStatsBase), _baseImage(baseImage) {
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
	_enemyAnimator->SetTrigger("Attack");
	_enemyAnimator->WaitForNextClipCompletion();
	Attack(other);
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
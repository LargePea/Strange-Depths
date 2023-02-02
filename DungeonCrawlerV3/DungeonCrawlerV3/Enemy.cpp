#include "Enemy.h"
#include <random>
#include <array>

void Enemy::ChooseAction(Character &other) {

}

void Enemy::UseItem() {

}

void Enemy::Death(Character& killer) {

	for (auto& loot : _possibleDrops.CreateLoot<_maxDropsPossible>()) {

	}
}
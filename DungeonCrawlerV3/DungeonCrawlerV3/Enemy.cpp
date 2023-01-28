#include "Enemy.h"
#include <random>
#include <array>

void Enemy::ChooseAction(Character &other) {

}

void Enemy::UseItem() {

}

void Enemy::Death(Character& killer) {
	//TO:DO add possible rare drop when dying
	static std::default_random_engine generator;
	static std::uniform_int_distribution<size_t> distributor(1, _maxDropsPossible);

	const size_t amountToDrop = distributor(generator);
	std::array<Item*, amountToDrop> droppedItems = _possibleDrops.CreateLoot<amountToDrop>();

	for (auto& loot : ) {

	}
}
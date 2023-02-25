#pragma once

#include "Enemy.h"

class Mimic : public Enemy {
public:
	Mimic(LootTable _chestLootTable, int mimicValue);

	Mimic(const Mimic&) = default;

	virtual ~Mimic() = default;
};
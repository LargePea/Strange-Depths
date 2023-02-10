#pragma once

#include "Enemy.h"

class Mimic : public Enemy {
public:
	Mimic(LootTable _chestLootTable, int mimicValue);

	virtual ~Mimic() = default;
};
#pragma once

#include "Enemy.h"

class Slime : public Enemy {
public:
	Slime();

	Slime(const Slime&) = default;

	virtual ~Slime() = default;
};
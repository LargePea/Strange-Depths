#pragma once

#include "Enemy.h"

class Banshee : public Enemy {
public:
	Banshee();

	Banshee(const Banshee&) = default;

	virtual ~Banshee() = default;
};
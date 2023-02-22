#pragma once
#include "Enemy.h"

class Skeleton : public Enemy {
public:
	Skeleton();

	Skeleton(const Skeleton&) = default;

	virtual ~Skeleton() = default;
};
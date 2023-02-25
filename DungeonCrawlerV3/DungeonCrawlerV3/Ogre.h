#pragma once

#include "Enemy.h"

class Ogre : public Enemy {
public:
	Ogre();

	Ogre(const Ogre&) = default;

	virtual ~Ogre() = default;
};
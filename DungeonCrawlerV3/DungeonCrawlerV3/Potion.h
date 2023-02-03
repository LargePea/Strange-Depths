#pragma once
#include "Item.h"
#include "Buff.h"
#include "Character.h"

class LifeStealPotion : public Item {
	const int _buffDuration = 1;
	const float _lifeStealStrength = 0.5f;

public:
	LifeStealPotion(const char* name, int value) : Item(name, value) { _usableGameStates = (int)GameStateMask::Combat; }
	~LifeStealPotion() override = default;

	void UseItem(Character& user) override;
};

class RegenPotion : public Item {
	const int _buffDuration = 3;
	const float _regenTotalPercentage = 0.5f;

public:
	RegenPotion(const char* name, int value) : Item(name, value) { _usableGameStates = (int)GameStateMask::Combat; }
	~RegenPotion() override = default;

	void UseItem(Character& user) override;
};

class HealPotion : public Item {
	const float _healStrength = 3;

public:
	HealPotion(const char* name, int value) : Item(name, value) { _usableGameStates = (int)GameStateMask::Combat + (int)GameStateMask::Normal; }
	~HealPotion() override = default;

	void UseItem(Character& user) override;
};
#pragma once
#include "GameState.h"
#include "Character.h"

class Buff {
private:
	int _activeGameStates;
	int _usesRemaining;

public:
	bool TryUseBuff(Character& user);
	virtual void UseBuff(Character& user) {}
};
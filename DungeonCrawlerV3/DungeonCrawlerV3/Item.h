#pragma once

#include "Character.h"
#include "GameState.h"

class Item {
protected:
	const char* _name;
	int _value;
	int _usableGameStates;

public:
	Item(const char* name, int value)
		: _name(name), _value(value) {}

	virtual ~Item() = default;

	//Getters
	const char* GetName();

	int GetValue();

	bool TryUseItem(Character& user);

	virtual void UseItem(Character& user) {};
};

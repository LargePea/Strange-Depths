#pragma once

#include <string>
#include "Character.h"

class Item {
protected:
	std::string _name;
	int _value;
	int _usableGameStates;

public:
	Item(std::string name, int value)
		: _name(name), _value(value) {}

	virtual ~Item() = default;

	//Getters
	std::string GetName();

	int GetValue();

	bool TryUseItem(Character& user);

	virtual void UseItem(Character& user) {};
};

#pragma once
#include <string>

class Item {
protected:
	std::string _name;
	int _value;
	int _usableGameStates;

public:
	Item(std::string name, int value, int useableGameStates)
		: _name(name), _value(value), _usableGameStates(useableGameStates)
	{

	};

	//Getters
	std::string GetName();

	int GetValue();

	bool TryUseItem();

	virtual void UseItem() {};
};

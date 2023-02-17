#pragma once

#include "Character.h"
#include "GameState.h"

enum class ItemType {
	Item,
	Enchantment,
	Potion
};

class Item {
protected:
	const char* _name;
	int _value;
	int _usableGameStates;
	ItemType _itemType;

public:
	Item(const char* name, int value, ItemType itemType = ItemType::Item, int usableGameStates = 0)
		: _name(name), _value(value), _itemType(itemType), _usableGameStates(usableGameStates) {}

	virtual ~Item() = default;

	//Getters
	inline const char* GetName() { return _name; }

	inline int GetValue() { return _value; }

	inline ItemType GetType() { return _itemType; }

	//fuctional functions
	bool TryUseItem(Character& user);

	virtual void UseItem(Character& user) {};
};

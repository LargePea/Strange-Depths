#pragma once

#include "Item.h"
#include "Character.h"
#include <vector>

#define MAX_INVENTORY_SIZE 50

class Inventory {
	typedef std::vector<Item*> ItemList;

private:
	Character* _owner;

	ItemList _items;
	int _coins;
	ItemList::iterator _currentSize;

public:
	Inventory(Character &owner);
	Inventory(Character& owner, std::initializer_list<Item*>);
	Inventory(Character& owner, ItemList startingItems);

	Inventory(const Inventory& other);
	Inventory& operator=(const Inventory& other);

	//Getters
	inline Character GetOwner() { return *_owner; }

	inline std::vector<Item*> GetItems(){ return _items; }

	inline int GetCoins() { return _coins; }

	inline size_t Size() { return _currentSize - _items.begin(); }

	//Functional methods
	bool AddItem(Item* item);

	bool RemoveOrSellItem(int index, bool sellItem);

	void AddCoins(int& amount);

	bool RemoveCoins(int& amount);
};
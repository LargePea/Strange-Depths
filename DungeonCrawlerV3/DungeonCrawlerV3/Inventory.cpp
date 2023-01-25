#include "Inventory.h"
#include <iostream>

Inventory::Inventory(Character& owner) : _owner(owner) {
	_items = ItemList(MAX_INVENTORY_SIZE);
	_currentSize = _items.begin();
	_coins = 0;
}

Inventory::Inventory(Character& owner, std::initializer_list<Item*> startingItems) : _owner(owner) {
	_items.reserve(startingItems.size());
	for (Item* item : startingItems)
		_items.push_back(item);
	_currentSize = _items.end();
	_coins = 0;
}

//Inventory Functionality
bool Inventory::AddItem(Item* item) {

	if (_currentSize == _items.end()) return false;

	//add item to list and shift over for the next one
	*_currentSize = item;
	++_currentSize;
	return true;
}

bool Inventory::RemoveOrSellItem(int index, bool sellItem) {
	if (index >= _items.size()) return false;


	if (sellItem)
	{
		int itemValue = _items[index]->GetValue();
		AddCoins(itemValue);
	}
	
	//shift items down to delete item
	ItemList::iterator itemToShift = _items.begin() + index + 1;
	while (itemToShift != _currentSize) 
		*(itemToShift - 1) = *itemToShift;
	--_currentSize;
	*_currentSize = nullptr;

	return true;
}

void Inventory::AddCoins(int& amount) {
	_coins += amount;
}

bool Inventory::RemoveCoins(int& amount) {
	if (amount > _coins) return false;

	_coins -= amount;
	return true;
}
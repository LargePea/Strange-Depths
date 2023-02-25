#include "Inventory.h"
#include "InventoryMenu.h"
#include <iostream>

Inventory::Inventory(Character& owner) : _owner(&owner) , _coins(0) {
	_items = ItemList(MAX_INVENTORY_SIZE);
	_currentSize = _items.begin();
}

Inventory::Inventory(Character& owner, std::initializer_list<Item*> startingItems) : _owner(&owner), _coins(0) {
	_items.reserve(startingItems.size());
	for (Item* item : startingItems)
		_items.push_back(item);
	_currentSize = _items.end();
}

Inventory::Inventory(Character& owner, ItemList startingList) : _owner(&owner), _items(startingList), _coins(0) {
	_currentSize = _items.end();
}

Inventory::Inventory(const Inventory& other) : _owner(other._owner), _items(other._items), _coins(other._coins) {
	_currentSize = _items.begin();
}

Inventory& Inventory::operator=(const Inventory& other) {
	_owner = other._owner;
	_items = other._items;
	_currentSize = other._currentSize;
	_coins = other._coins;

	return *this;
}

//Inventory Functionality
bool Inventory::AddItem(Item* item) {

	//TO:DO alert when inventory is full
	if (IsFull()) return false;

	//add item to list and shift over for the next one
	*_currentSize = item;
	++_currentSize;
	return true;
}

bool Inventory::RemoveOrSellItem(int index, bool sellItem) {
	if (index >= Size()) return false;


	if (sellItem)
	{
		int itemValue = _items[index]->GetValue();
		AddCoins(itemValue);
	}
	
	//shift items down to delete item
	ItemList::iterator itemToShift = _items.begin() + index + 1;
	while (itemToShift != _currentSize) {
		*(itemToShift - 1) = *itemToShift;
		++itemToShift;
	}
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
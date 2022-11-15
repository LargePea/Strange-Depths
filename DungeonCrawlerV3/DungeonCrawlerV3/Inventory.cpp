#include "Inventory.h"
#include <iostream>

Inventory::Inventory() {
	_inventory.reserve(MAX_INVENTORY_SIZE);
	_coins = 0;
}

std::vector<Item>* Inventory::GetInventory() {
	return &_inventory;
}

int Inventory::GetCoins() {
	return _coins;
}

//Inventory Functionality
bool Inventory::AddItem(Item& item) {

	if (_inventory.size() == MAX_INVENTORY_SIZE) return false;

	_inventory.push_back(item);
	return true;
}

bool Inventory::RemoveOrSellItem(int& index, bool& sellItem) {
	if (index >= _inventory.size()) return false;


	if (sellItem)
	{
		int itemValue = _inventory[index].GetValue();
		AddCoins(itemValue);
	}
	_inventory.erase(_inventory.begin() + index);
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
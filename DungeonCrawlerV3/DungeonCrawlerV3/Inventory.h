#pragma once

#include "Item.h"
#include <vector>

#define MAX_INVENTORY_SIZE 50

class Inventory {
private:
	std::vector<Item> _inventory;
	int _coins;

public:
	Inventory();

	//Getters
	std::vector<Item>* GetInventory();

	int GetCoins();

	//Functional methods
	bool AddItem(Item& item);

	bool RemoveOrSellItem(int& index, bool& sellItem);

	void AddCoins(int& amount);

	bool RemoveCoins(int& amount);
};
#pragma once

#include "Image.h"
#include "Character.h"
#include "LootTable.h"
#include "Inventory.h"
#include <array>
#include <iostream>

class Enemy : public Character {
protected:
	//Display
	std::array<std::string, MAX_IMAGE_HEIGHT> _imageDisplay;

	static const int _maxDropsPossible = 1;
	static const int _maxInventoryStartingSize = 5;

	LootTable _possibleDrops;
	//TO:DO Inventory
	Inventory _enemyInventory;
	//Special drop

public:
	const char* _name;
	Enemy(const char* name);

	void ChooseAction(Character& other) override;

protected:
	void UseItem() override;
	
	void Death(Character* killer) override;

private:
	std::vector<Item*> CreateStartingItems();
};
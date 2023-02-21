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
	const char* _name;

	//AI
	const float _healThreshold;

	//Drops
	LootTable _possibleDrops;
	static const int _maxDropsPossible = 5;
	static const int _maxInventoryStartingSize = 5;
	int _enemyValue;

	//TO:DO Inventory
	Inventory _enemyInventory;

public:
	Enemy(float maxHealth, float attack, float defense, float critRate, float speed, const char* name, int value, float healingThreshold);

	Enemy(const Enemy&);

	virtual ~Enemy() = default;

	void ChooseAction(Character& other) override;

	void UseItem() override;
	
	void Death(Character* killer) override;

private:
	std::vector<Item*> CreateStartingItems();
};
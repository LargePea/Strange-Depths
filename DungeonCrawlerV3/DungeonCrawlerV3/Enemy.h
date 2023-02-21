#pragma once

#include "Image.h"
#include "SpriteAtlas.h"
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

	Inventory _enemyInventory;

	Image _enemyStatsBase = Image(ENEMY_STAT_BASE, 2, { 5, 5 });
	Image _enemyStats;

public:
	Enemy(float maxHealth, float attack, float defense, float critRate, float speed, const char* name, int value, float healingThreshold);

	Enemy(const Enemy&);

	virtual ~Enemy() = default;

	void ChooseAction(Character& other) override;

	void UseItem() override;
	
	void Death(Character* killer) override;

	void Damage(const float& incomingDamage, Character& attacker) override;

	void LoadEnemyImage();

	void UpdateStatsMenu();

private:
	std::vector<Item*> CreateStartingItems();
};
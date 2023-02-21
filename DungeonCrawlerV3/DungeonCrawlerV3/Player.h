#pragma once
#include "Character.h"
#include "Inventory.h"
#include "InventoryMenu.h"
#include <vector>

class Player : public Character {
friend class InventoryMenu;
friend class CombatAM;

private:
	Inventory _playerInventory{ *this };

	//combat
	bool _playerCombatTurn = false;

public:
	Player();

	Player(const Player&);

	~Player() override = default;

	//functional methods
	void ChooseAction(Character& other) override;


protected:
	void UseItem() override;

	void Death(Character* killer) override;

private:
	inline Inventory* GetInventory() { return &_playerInventory; }

	void QuickHeal();

	void Attack(Character& other) override;
};
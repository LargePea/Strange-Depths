#pragma once
#include "Character.h"
#include "Inventory.h"
#include "InventoryMenu.h"
#include "Image.h"
#include <vector>

class Player : public Character {
friend class InventoryMenu;
friend class CombatAM;

private:
	Inventory _playerInventory{ *this };

	//combat
	bool _playerCombatTurn = false;

	Image _playerStats{ "", 0, { 0,0 } };
	Image _playerHealth{ "", 0, {0,0}};

public:
	Player();

	Player(const Player&);

	~Player() override = default;

	//functional methods
	void ChooseAction(Character& other) override;

	void Damage(const float& incomingDamage, Character& attacker) override;

	void LoadStats();

	void HideStats();

	void Heal(const float& incomingHeal) override;

protected:
	void UseItem() override;

	void Death(Character* killer) override;

private:
	void UpdateStats();

	void UpdateHealthStat();

	inline Inventory* GetInventory() { return &_playerInventory; }

	void QuickHeal();

	void Attack(Character& other) override;
};
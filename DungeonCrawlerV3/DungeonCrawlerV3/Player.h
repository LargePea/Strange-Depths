#pragma once
#include "Character.h"
#include <vector>
#include "Inventory.h"

class Player : public Character {

private:
	Inventory _playerInventory{ *this };

public:
	Player();

	//functional methods
	void ChooseAction(Character& other) override;

protected:
	void UseItem() override;

	void Death(Character& killer) override;
};
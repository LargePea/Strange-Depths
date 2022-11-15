#pragma once
#include "Character.h"
#include "Inventory.h"
#include <vector>

class Player : public Character {

private:
	static Inventory _inventory;

public:
	Player();

	//Getters
	static std::vector<Item>* GetInventory();

	static int GetCoins();

	//functional methods
	void ChooseAction(Character& other) override;

protected:
	void UseItem() override;

	void Death() override;
};
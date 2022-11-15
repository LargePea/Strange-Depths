#pragma once
#include "Character.h"
#include "Item.h"
#include <vector>

#define MAX_PLAYER_INVENTORY_SIZE 50

class Player : public Character {

private:
	static std::vector<Item> _inventory;
	static int _coins;

public:
	Player();

	//Getters
	static std::vector<Item>* GetInventory();

	static unsigned int GetCoins();

	//functional methods
	void ChooseAction(Character& other) override;

	static bool AddItem(Item &item);

	static bool RemoveOrSellItem(int &index, bool &sellItem);

	static void AddCoins(int &amount);

	static bool RemoveCoins(int &amount);

protected:
	void UseItem() override;

	void Death() override;
};
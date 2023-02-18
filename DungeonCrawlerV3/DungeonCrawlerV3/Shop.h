#pragma once

#include <array>
#include "Item.h"
#include "LootTable.h"
#include "EventSystem.h"

class Shop {
friend class ShopRoomAM;

private:
	std::array<Item*, 6> _shopStock;
	int _currentItemPos = 0;

public:
	Subject<> KeyBought;

public:
	Shop();

private:
	std::array<Item*, 6> GenerateStock();

	void BuyItem();

	void NextItem();

	void PrevItem();

	void SellItems();

	void UpdateScreen();
};
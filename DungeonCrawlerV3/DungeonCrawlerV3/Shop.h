#pragma once

#include <array>
#include "Item.h"
#include "LootTable.h"
#include "EventSystem.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "Animator.h"

class Shop {
friend class ShopRoomAM;

private:
	std::array<Item*, 6> _shopStock;
	int _currentItemPos = 0;

	Image* _shopDisplay = nullptr;
	Animator* _animator = nullptr;

public:
	Image _shopImage{ SHOP, 2, { 33, 10 } };
	Subject<> KeyBought;

public:
	Shop();

	Shop(const Shop&) = delete;

	~Shop();

	void ShowShop();

	void HideShop();

private:
	std::array<Item*, 6> GenerateStock();

	void BuyItem();

	void NextItem();

	void PrevItem();

	void SellItems();

	void UpdateScreen();

	void LeaveShop();
};
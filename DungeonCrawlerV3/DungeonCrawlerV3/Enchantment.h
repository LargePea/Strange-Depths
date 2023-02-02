#pragma once
#include "Item.h"
#include "GameState.h"
#include "Enchant.h"

class Enchantment : public Item
{
private:
	Enchant _enchant;

public:
	Enchantment(const char* name, int value, Enchant enchant) 
		: Item(name, value), _enchant(enchant) {
		_usableGameStates = static_cast<int>(GameStateMask::Combat) + static_cast<int>(GameStateMask::Normal);
	}

	void UseItem(Character& user) override;
};
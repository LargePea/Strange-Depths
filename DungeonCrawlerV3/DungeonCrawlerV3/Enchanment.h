#pragma once
#include "Item.h"
#include "GameState.h"

class Enchantment : public Item
{
private:
	float _modifyAmount = 0;
	CharacterStats _modifyType = CharacterStats::Attack;

public:
	Enchantment(std::string name, int value, float modifyAmount, CharacterStats modifyType) 
		: Item(name, value), _modifyAmount(modifyAmount), _modifyType(modifyType) {
		_usableGameStates = static_cast<int>(GameStateMask::Combat) + static_cast<int>(GameStateMask::Normal);
	}

	void UseItem(Character& user) override {
		user.ModStats(_modifyAmount, _modifyType);
	}
};
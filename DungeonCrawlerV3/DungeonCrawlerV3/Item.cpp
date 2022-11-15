#include "Item.h"
#include "GameState.h"

std::string Item::GetName() {
	return _name;
};

int Item::GetValue() {
	return _value;
}

bool Item::TryUseItem() {
	if (GameState::GetStateMask() & _usableGameStates) 
	{
		UseItem();
		return true;
	}

	else 
		return false;
}
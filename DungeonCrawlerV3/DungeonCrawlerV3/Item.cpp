#include "Item.h"
#include "GameState.h"

const char* Item::GetName() {
	return _name;
};

int Item::GetValue() {
	return _value;
}

bool Item::TryUseItem(Character& user) {
	if (GameState::GetStateMask() & _usableGameStates) 
	{
		UseItem(user);
		return true;
	}

	else 
		return false;
}
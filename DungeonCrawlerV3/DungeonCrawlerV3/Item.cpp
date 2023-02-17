#include "Item.h"
#include "GameState.h"

bool Item::TryUseItem(Character& user) {
	if (GameState::GetStateMask() & _usableGameStates) 
	{
		UseItem(user);
		return true;
	}

	else 
		return false;
}
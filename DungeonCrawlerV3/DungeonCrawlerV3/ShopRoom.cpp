#include "ShopRoom.h"
#include "GameState.h"

ShopRoom::ShopRoom() 
	: _actionMap(_shop) {

	GameState::SetStateMask(GameStateMask::Shop);
	ActionMap::AddActionMap(&_actionMap);
	_event = _shop.KeyBought.Attach(this, &ShopRoom::UnlockExit);
	Room::IncreaseRoomDifficulty();
}

void ShopRoom::UnlockExit() {
	_exitUnlocked = true;
}

ShopRoom::~ShopRoom() {
	GameState::SetStateMask(GameStateMask::Normal);
	_shop.KeyBought.Remove(_event);
}
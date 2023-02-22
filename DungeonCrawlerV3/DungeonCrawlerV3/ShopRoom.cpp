#include "ShopRoom.h"
#include "GameState.h"
#include "Notification.h"

ShopRoom::ShopRoom() 
	: _actionMap(_shop) {

	GameState::SetStateMask(GameStateMask::Shop);
	ActionMap::AddActionMap(&_actionMap);
	_event = _shop.KeyBought.Attach(this, &ShopRoom::UnlockExit);
	Room::IncreaseRoomDifficulty();
}

void ShopRoom::UnlockExit() {
	Notification _exitAvalibleNotif(std::vector<std::string>{
		"=================================================================",
		"|...............................................................|",
		"|.You hear something open in the distance,.possibly an escape?!.|",
		"|.................Press Any Key To Continue.....................|",
		"|...............................................................|",
		"================================================================="
	}, { 25, 38 });
	_exitUnlocked = true;
}

ShopRoom::~ShopRoom() {
	GameState::SetStateMask(GameStateMask::Normal);
	_shop.KeyBought.Remove(_event);
}
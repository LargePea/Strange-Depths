#include "ShopRoom.h"
#include "GameState.h"
#include <conio.h>

ShopRoom::ShopRoom() 
	: _actionMap(_shop) {

	GameState::SetStateMask(GameStateMask::Shop);
	ActionMap::AddActionMap(&_actionMap);
	_event = _shop.KeyBought.Attach(this, &ShopRoom::UnlockExit);
	Room::IncreaseRoomDifficulty();
}

void ShopRoom::UnlockExit() {
	_shop.HideShop();

	Image _exitAvalibleNotif = Image(std::vector<std::string>{
		"You hear something open in the distance, possibly an escape?!",
		"                 Press Any Key To Continue"
	}, 2, { 27, 41 });

	Screen::AddImages({ &_exitAvalibleNotif });
	_getch();
	Screen::RemoveImages({ &_exitAvalibleNotif });
	_shop.ShowShop();

	_exitUnlocked = true;
}

ShopRoom::~ShopRoom() {
	GameState::SetStateMask(GameStateMask::Normal);
	_shop.KeyBought.Remove(_event);
}
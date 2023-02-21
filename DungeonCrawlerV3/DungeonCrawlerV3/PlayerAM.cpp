#include "PlayerAM.h"
#include "Room.h"
#include "InventoryMenu.h"
#include "Image.h"
#include "SpriteAtlas.h"

PlayerAM::PlayerAM() 
	: ActionMap(Image(MOVEMENT_MENU, 1, std::make_pair<int, int>(0, 37))) {

}

void PlayerAM::InputAction(const char input) {
	
	switch (input)
	{
	case 'w':
	case 'W':
		Room::GetCurrentRoom()->Move(Room::Direction::Forward);
		break;
	case 'a':
	case 'A':
		Room::GetCurrentRoom()->Move(Room::Direction::Left);
		break;
	case 's':
	case 'S':
		Room::GetCurrentRoom()->Move(Room::Direction::Backward);
		break;
	case 'd':
	case 'D':
		Room::GetCurrentRoom()->Move(Room::Direction::Right);
		break;
	case 'e':
	case 'E':
		InventoryMenu::Navigate();
		break;
	default:
		break;
	}
}
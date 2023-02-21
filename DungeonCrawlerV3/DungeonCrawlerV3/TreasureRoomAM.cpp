#include "TreasureRoomAm.h"
#include "SpriteAtlas.h"

TreasureRoomAM::TreasureRoomAM(Chest* chest) 
	: ActionMap(Image(TREASURE_MENU, 1, std::make_pair<int, int>(0, 37))), _chest(chest) {}

void TreasureRoomAM::InputAction(const char input) {
	switch (input)
	{
	case 'q':
	case 'Q':
		_chest->RejectChest();
		break;
	case 'e':
	case 'E':
		_chest->OpenChest();
		break;
	default:
		break;
	}
}
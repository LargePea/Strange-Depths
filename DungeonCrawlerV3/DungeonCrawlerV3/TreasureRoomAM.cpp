#include "TreasureRoomAm.h"

TreasureRoomAM::TreasureRoomAM(TreasureRoom& room) 
	: _room(room) {}

void TreasureRoomAM::InputAction(const char input) {
	switch (input)
	{
	case 'q':
	case 'Q':
		_room.RejectChest();
		break;
	case 'e':
	case 'E':
		_room.OpenChest();
		break;
	default:
		break;
	}
}
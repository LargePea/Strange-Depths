#include "TreasureRoomAm.h"

TreasureRoomAM::TreasureRoomAM(Chest* chest) 
	: _chest(chest) {}

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
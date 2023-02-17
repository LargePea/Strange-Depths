#include "InventoryOverflowAM.h"
#include "InventoryMenu.h"

void InventoryOverflowAM::InputAction(const char input) {
	switch (input)
	{
	case 'q':
	case 'Q':
		InventoryMenu::RejectOverflowItem();
		break;
	case 'e':
	case 'E':
		InventoryMenu::AcceptOverflowItem();
		break;
	default:
		break;
	}
}
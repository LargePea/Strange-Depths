#include "InventoryOverflowAM.h"
#include "InventoryMenu.h"
#include "SpriteAtlas.h"

InventoryOverflowAM::InventoryOverflowAM()
	:ActionMap(Image(OVERFLOW_MENU, 1, std::make_pair<int, int>(0, 37))) {

}

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
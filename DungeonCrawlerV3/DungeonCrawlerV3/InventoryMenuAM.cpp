#include "InventoryMenuAM.h"
#include "InventoryMenu.h"

void InventoryMenuAM::InputAction(const char input) {
	switch (input)
	{
	case 'w':
	case 'W':
		InventoryMenu::DecreaseCursor();
		break;
	case 's':
	case 'S':
		InventoryMenu::IncreaseCursor();
		break;
	case 'a':
	case 'A':
		InventoryMenu::DecreasePage();
		break;
	case 'd':
	case 'D':
		InventoryMenu::IncreasePage();
		break;
	case 'e':
	case 'E':
		InventoryMenu::UseItem();
		break;
	case 'c':
	case 'C':
		InventoryMenu::RemoveItem();
		break;
	case 'q':
	case 'Q':
		InventoryMenu::Quit();
		break;
	default:
		break;
	}
}
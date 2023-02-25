#include "InventoryMenuAM.h"
#include "InventoryMenu.h"
#include "SpriteAtlas.h"

InventoryMenuAM::InventoryMenuAM() 
	:ActionMap(Image(INVENTORY_MENU, 1, std::make_pair<int, int>(0, 37))){}

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

void InventoryMenuAM::OnActivate() {
	InventoryMenu::UpdateDisplay();
	Screen::AddImages({ InventoryMenu::_displayImage });
}

void InventoryMenuAM::OnDeactivate() {
	Screen::RemoveImages({ InventoryMenu::_displayImage });
}
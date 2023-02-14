#include "InventoryMenu.h"
#include "GameState.h"
#include "Character.h"
#include <conio.h>

Inventory* InventoryMenu::_inventory;
int InventoryMenu::_cursorPos;
int InventoryMenu::_currentPage;
bool InventoryMenu::_inventoryOverflowMode;


//assumes input will have been capitalized already
//return value of this represents if the player is still wants to use the inventoryMenu
bool InventoryMenu::Navigate(char& input) {
	switch (input)
	{
	case 'W':				//decrease cursor position (loops around)
		if (_cursorPos == 0) MaxCursor();
		else --_cursorPos;
		UpdateDisplay();
		return true;

	case 'A':				//increase cursor position (loops around)
		if (_cursorPos == MAX_CURSOR_POSITION) ResetCursor();
		else ++_cursorPos;
		UpdateDisplay();
		return true;

	case 'S':				//decrease page number (loops around)
		if (_currentPage == 0) MaxPageCount();
		else --_currentPage;
		ResetCursor();
		UpdateDisplay();
		return true;

	case 'D':				//increase page number (loops around)
		if (_currentPage == MAX_PAGE_COUNT) ResetPageCount();
		else ++_currentPage;
		ResetCursor();
		UpdateDisplay();
		return true;

	case 'E':				//use item
	{
		if (_inventoryOverflowMode) return true;

		int itemIndex = _cursorPos + _currentPage * (MAX_CURSOR_POSITION + 1);
		if (itemIndex >= _inventory->Size()) return true;

		Character inventoryOwner = _inventory->GetOwner();
		bool itemUsed = _inventory->GetItems()[itemIndex]->TryUseItem(inventoryOwner);
		if (!itemUsed) return true;

		_inventory->RemoveOrSellItem(itemIndex, false);
		UpdateDisplay();
		return true;
	}
	case 'C':				//Sell/Remove item
	{
		bool removedItem = _inventory->RemoveOrSellItem(_cursorPos + _currentPage * (MAX_CURSOR_POSITION + 1), GameState::GetStateMask() & static_cast<int> (GameStateMask::Shop));
		if(removedItem) UpdateDisplay();

		if (_inventoryOverflowMode) return false;
		return true;
	}

	case 'Q':				//Quit inventory
		ResetCursor();
		ResetPageCount();
		UpdateDisplay();
		return false;

	default:				//incorrect input
		UpdateDisplay();
		return true;
	}
}

//TO:DO Fix input actions
//bool InventoryMenu::ItemOverflow() {
//	bool selectingItem = true;
//
//	while (selectingItem)
//	{
//		char input = _getch();
//		
//		switch (input)
//		{
//		case 'a':
//		case 'A':
//			_inventoryOverflowMode = true;
//			while ()
//			{
//
//			}
//		default:
//			break;
//		}
//	}
//}

void InventoryMenu::UpdateDisplay() {}
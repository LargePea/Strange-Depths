#pragma once

#include "Inventory.h"

//these are one less than what is displayed for easier vector interaction
#define MAX_CURSOR_POSITION 9 
#define MAX_PAGE_COUNT 4

class InventoryMenu
{
private:
	InventoryMenu();
	static Inventory* _inventory;

	//navigation
	static int _cursorPos;
	static int _currentPage;
	static bool _inventoryOverflowMode;

public:
	static void SetInventory(Inventory* inventory) {
		_inventory = inventory;
	}

	static bool Navigate(char& input);

	static bool ItemOverflow();

	static void UpdateDisplay(); //TO:DO somehow delegate things to screen

private:
	//navigation functions
	static inline void ResetCursor() { _cursorPos = 0; };
	static inline void ResetPageCount() { _currentPage = 0; };
	static inline void MaxCursor() { _cursorPos = MAX_CURSOR_POSITION; };
	static inline void MaxPageCount() { _currentPage = MAX_PAGE_COUNT; };
};
#pragma once

#include "Inventory.h"
#include "InventoryMenuAM.h"
#include "InventoryOverflowAM.h"

//these are one less than what is displayed for easier vector interaction
#define MAX_CURSOR_POSITION 9 
#define MAX_PAGE_COUNT 4

class InventoryMenu
{
friend class InventoryMenuAM;
friend class InventoryOverflowAM;

private:
	InventoryMenu();
	static Inventory* _inventory;

	//ActionMaps
	static InventoryMenuAM _inventoryAM;
	static InventoryOverflowAM _overflowAM;

	//navigation
	static int _cursorPos;
	static int _currentPage;
	static bool _inventoryOverflowMode;

public:
	static void SetInventory(Inventory* inventory) {
		_inventory = inventory;
	}

	static void Navigate();

	static void ItemOverflow(Item*& itemToAdd);

	static void AddItem(Item*& item);

	static void AddCoins(int& amount);

	static bool RemoveCoins(int& amount);

	static void UpdateDisplay(); //TO:DO somehow delegate things to screen

private:
	//navigation helpers
	static inline void ResetCursor() { _cursorPos = 0; };
	static inline void ResetPageCount() { _currentPage = 0; };
	static inline void MaxCursor() { _cursorPos = MAX_CURSOR_POSITION; };
	static inline void MaxPageCount() { _currentPage = MAX_PAGE_COUNT; };

	//navigation functions
	static void IncreaseCursor();
	static void DecreaseCursor();
	static void IncreasePage();
	static void DecreasePage();
	static void UseItem();
	static void RemoveItem(bool sellItem = GameState::GetStateMask() & static_cast<int> (GameStateMask::Shop));
	static void Quit();

	//item overflow functions
	static void AcceptOverflowItem();
	static void RejectOverflowItem();
};
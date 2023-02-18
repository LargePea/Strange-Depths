#include "InventoryMenu.h"
#include "GameState.h"
#include "Character.h"
#include <conio.h>

Inventory* InventoryMenu::_inventory;
int InventoryMenu::_cursorPos;
int InventoryMenu::_currentPage;
bool InventoryMenu::_inventoryOverflowMode;
InventoryMenuAM InventoryMenu::_inventoryAM;
InventoryOverflowAM InventoryMenu::_overflowAM;


//return value of this represents if the player is still wants to use the inventoryMenu
void InventoryMenu::Navigate() {
	ActionMap::AddActionMap(&_inventoryAM);
	UpdateDisplay();
}

void InventoryMenu::AddItem(Item*& item) {
	if (!_inventory->AddItem(item)) ItemOverflow(item);
}

void InventoryMenu::AddCoins(int& coins) {
	_inventory->AddCoins(coins);
}

bool InventoryMenu::RemoveCoins(int& amount) {
	if (_inventory->GetCoins() < amount) return false;

	_inventory->RemoveCoins(amount);
	return true;
}

void InventoryMenu::IncreaseCursor() {
	if (_cursorPos == MAX_CURSOR_POSITION) ResetCursor();
	else ++_cursorPos;
	UpdateDisplay();
}

void InventoryMenu::DecreaseCursor() {
	if (_cursorPos == 0) MaxCursor();
	else --_cursorPos;
	UpdateDisplay();
}

void InventoryMenu::IncreasePage() {
	if (_currentPage == MAX_PAGE_COUNT) ResetPageCount();
	else ++_currentPage;
	ResetCursor();
	UpdateDisplay();
}

void InventoryMenu::DecreasePage() {
	if (_currentPage == 0) MaxPageCount();
	else --_currentPage;
	ResetCursor();
	UpdateDisplay();
}

void InventoryMenu::UseItem() {
	int itemIndex = _cursorPos + _currentPage * (MAX_CURSOR_POSITION + 1);
	if (itemIndex >= _inventory->Size()) return; //if pointing at memory out of bounds dont do anything

	Character inventoryOwner = _inventory->GetOwner();
	bool itemUsed = _inventory->GetItem(itemIndex)->TryUseItem(inventoryOwner);
	if (!itemUsed) return; //if item did not get used do not remove item

	RemoveItem(false);
}

void InventoryMenu::RemoveItem(bool sellItem) {
	bool removedItem = _inventory->RemoveOrSellItem(_cursorPos + _currentPage * (MAX_CURSOR_POSITION + 1), sellItem);

	if (!removedItem) return; 

	if (_inventoryOverflowMode) {
		_inventoryOverflowMode = false;
		ActionMap::PopCurrentMap(); //if this actionmap call is for overflow then it's job is done
	}

	UpdateDisplay(); //only remove item from display if item was actually removed from inventory
}

void InventoryMenu::Quit() {
	ResetCursor();
	ResetPageCount();
	UpdateDisplay();
	ActionMap::PopCurrentMap();
}

void InventoryMenu::ItemOverflow(Item*& itemToAdd) {
	_inventoryOverflowMode = true;
	ActionMap::AddActionMap(&_overflowAM);
	while (_inventoryOverflowMode) {
		ActionMap::GetCurrentMap().InputAction(static_cast<char>(_getch()));
	}

	if (!_inventory->IsFull()) AddItem(itemToAdd);
}

void InventoryMenu::AcceptOverflowItem() {
	Navigate();
}

void InventoryMenu::RejectOverflowItem() {
	_inventoryOverflowMode = false;
	ActionMap::PopCurrentMap();
}


void InventoryMenu::UpdateDisplay() {}
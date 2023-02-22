#include "InventoryMenu.h"
#include "GameState.h"
#include "Character.h"
#include "Image.h"
#include "Screen.h"
#include "Notification.h"
#include <conio.h>

Inventory* InventoryMenu::_inventory;
size_t InventoryMenu::_cursorPos;
int InventoryMenu::_currentPage;
bool InventoryMenu::_inventoryOverflowMode;
Image* InventoryMenu::_displayImage;
InventoryMenuAM InventoryMenu::_inventoryAM;
InventoryOverflowAM InventoryMenu::_overflowAM;


//return value of this represents if the player is still wants to use the inventoryMenu
void InventoryMenu::Navigate() {
	ActionMap::AddActionMap(&_inventoryAM);
}

void InventoryMenu::AddItem(Item*& item) {
	if (!_inventory->AddItem(item)) 
	{
		{
			Notification overflowNotif({
				".Your.Inventory.is.full.and.can't.take.in:." + (std::string)item->GetName() + ".",
				".Please.choose.to.accept.this.item.or.not.",
				".Press.Any.Key.To.Continue."
				}, { 40, 38 });
		}
		ItemOverflow(item);
	}
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

	bool itemUsed = _inventory->GetItem(itemIndex)->TryUseItem(_inventory->GetOwner());
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

void InventoryMenu::UpdateDisplay() {
	static std::vector<std::string> inventoryDisplay(12, "");

	for (size_t row = 0; row < DISPLAY_ROWS; ++row) {
		std::string line;
		for (size_t col = 0; col < DISPLAY_COLUMNS; ++col) {
			std::string column{ "." + std::to_string((_currentPage * (MAX_CURSOR_POSITION + 1) + row) + (1 + DISPLAY_ROWS * col)) + ":"};

			Item* const& possibleItem = _inventory->GetItem(_currentPage * (MAX_CURSOR_POSITION + 1) + row + col * DISPLAY_ROWS);
			if (possibleItem != nullptr) column = column + possibleItem->GetName() + "..$" + std::to_string(possibleItem->GetValue());

			column += std::string(MAX_COLUMN_SIZE - column.size(), '.');
			line += column;
		}
		inventoryDisplay[row * 2] = line;
	}

	//display coins
	std::string coinsDisplay = "Coins: $" + std::to_string(_inventory->GetCoins());
	inventoryDisplay[DISPLAY_ROWS * 2] = std::string(MAX_COLUMN_SIZE - coinsDisplay.size() / 2, ' ') + coinsDisplay;

	if (_cursorPos < DISPLAY_ROWS) inventoryDisplay[_cursorPos * 2][0] = '>';
	else inventoryDisplay[(_cursorPos - DISPLAY_ROWS) * 2][MAX_COLUMN_SIZE] = '>';

	if (_displayImage == nullptr) _displayImage = new Image(inventoryDisplay, 1, { 2, 37 });
	else *_displayImage = std::move(Image(inventoryDisplay, 1, { 2, 37 }));
}
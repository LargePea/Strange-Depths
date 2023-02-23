#include "Shop.h"
#include "InventoryMenu.h"
#include "ItemDictionary.h"
#include "GameState.h"
#include "ActionMap.h"
#include "Screen.h"



Shop::Shop()
	:_shopStock(GenerateStock()) {
}

Shop::Shop(const Shop& other)
	:_shopStock(other._shopStock), _shopDisplay(other._shopDisplay) {
}

Shop::~Shop() {
	if(_shopDisplay != nullptr)
		delete _shopDisplay;
}

std::array<Item*, 6> Shop::GenerateStock() {
	static ItemDictionary instance = ItemDictionary::Instance();
	static LootTable shopLootTable = LootTable({
		{instance.GetPotion("Heal"), 30},
		{instance.GetPotion("Life Steal"), 15},
		{instance.GetPotion("Regeneration"), 7},
		{instance.GetPotion("Onion"), 2}});

	std::array<Item*, 6> stock;
	shopLootTable.CreateLoot(stock, true);
	stock[stock.size() - 1] = instance.GetItem("KeyStone");

	return stock;
}

void Shop::NextItem() {
	if (_currentItemPos + 1 > _shopStock.size() - 1) _currentItemPos = 0;
	else ++_currentItemPos;
	UpdateScreen();
}

void Shop::PrevItem() {
	if (_currentItemPos - 1 < 0) _currentItemPos = _shopStock.size() - 1;
	else --_currentItemPos;
	UpdateScreen();
}

void Shop::BuyItem() {
	Item* itemToBuy = _shopStock[_currentItemPos];
	if (itemToBuy == nullptr) return;

	int itemValue = itemToBuy->GetValue();
	if (!InventoryMenu::RemoveCoins(itemValue)) return;
	InventoryMenu::AddItem(itemToBuy);

	_shopStock[_currentItemPos] = nullptr;
	if (_currentItemPos == _shopStock.size() - 1) 
		KeyBought.Invoke();

	UpdateScreen();
}

void Shop::SellItems() {
	HideShop();
	InventoryMenu::Navigate();
}

void Shop::LeaveShop() {
	HideShop();
	ActionMap::GetCurrentMap().PopCurrentMap();
	GameState::SetStateMask(GameStateMask::Normal);
}

void Shop::HideShop() {
	Screen::RemoveImages({ _shopDisplay, &_shopImage });
}

void Shop::ShowShop() {
	_currentItemPos = 0;
	UpdateScreen();
	Screen::AddImages({ _shopDisplay, &_shopImage });
}

void Shop::UpdateScreen() {
	static int displayRows = _shopStock.size() / 2;
	static std::vector<std::string> stockDisplay(12, "");

	for (int row = 0; row < displayRows; ++row) {
		std::string line;
		for (int col = 0; col < DISPLAY_COLUMNS; ++col) {
			std::string column{ " " + std::to_string((1 + row) + (displayRows * col)) + ":" };

			Item* const& possibleItem = _shopStock[row + displayRows * col];
			if (possibleItem != nullptr) column = column + possibleItem->GetName() + "  $" + std::to_string(possibleItem->GetValue());

			column += std::string(MAX_COLUMN_SIZE - column.size(), ' ');
			line += column;
		}
		stockDisplay[row * 3] = line;
	}

	//display coins
	std::string coinsDisplay = "Coins: $" + std::to_string(InventoryMenu::GetCoins());
	stockDisplay[displayRows * 3] = std::string(MAX_COLUMN_SIZE - coinsDisplay.size() / 2, ' ') + coinsDisplay;

	if (_currentItemPos < displayRows) stockDisplay[_currentItemPos * 3][0] = '>';
	else stockDisplay[(_currentItemPos - displayRows) * 3][MAX_COLUMN_SIZE] = '>';

	if (_shopDisplay == nullptr) _shopDisplay = new Image(stockDisplay, 1, { 2, 37 });
	else *_shopDisplay = std::move(Image(stockDisplay, 1, { 2, 37 }));
}
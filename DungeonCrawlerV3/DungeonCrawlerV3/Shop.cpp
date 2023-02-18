#include "Shop.h"
#include "InventoryMenu.h"
#include "ItemDictionary.h"

Shop::Shop()
	:_shopStock(GenerateStock()) {
	UpdateScreen();
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
	if (_currentItemPos + 1 > _shopStock.size()) _currentItemPos = 0;
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
	int itemValue = itemToBuy->GetValue();
	if (!InventoryMenu::RemoveCoins(itemValue)) return;
	InventoryMenu::AddItem(itemToBuy);

	_shopStock[_currentItemPos] = nullptr;
	if (_currentItemPos == _shopStock.size()) KeyBought.Invoke();
	NextItem();
}

void Shop::SellItems() {
	InventoryMenu::Navigate();
}

void Shop::UpdateScreen() {

}
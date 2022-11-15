#include "Player.h"
#include <vector>

int Player::_coins;
std::vector<Item> Player::_inventory;

Player::Player() {
	_inventory.reserve(MAX_PLAYER_INVENTORY_SIZE);
}

//Getters
std::vector<Item>* Player::GetInventory() {
	return &_inventory;
}

unsigned int Player::GetCoins() {
	return _coins;
}

//Inventory Functionality
bool Player::AddItem(Item &item) {

	if (_inventory.size() == MAX_PLAYER_INVENTORY_SIZE) return false;

	_inventory.push_back(item);
	return true;
}

bool Player::RemoveOrSellItem(int &index, bool &sellItem) {
	if (index >= _inventory.size()) return false;


	if (sellItem) 
	{
		int itemValue = _inventory[index].GetValue();
		AddCoins(itemValue);
	} 
	_inventory.erase(_inventory.begin() + index);
	return true;
}

void Player::AddCoins(int &amount) {
	_coins += amount;
}

bool Player::RemoveCoins(int &amount) {
	if (amount > _coins) return false;

	_coins -= amount;
	return true;
}


//functional methods
void Player::ChooseAction(Character &other) {

}

void Player::UseItem() {

} 

void Player::Death() {

}
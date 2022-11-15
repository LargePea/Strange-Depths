#include "Player.h"
#include <vector>


Player::Player() {

}

//Getters
std::vector<Item>* Player::GetInventory() {
	return _inventory.GetInventory();
}

int Player::GetCoins() {
	return _inventory.GetCoins();
}


//functional methods
void Player::ChooseAction(Character &other) {

}

void Player::UseItem() {

} 

void Player::Death() {

}
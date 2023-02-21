#include "Player.h"
#include "InventoryMenu.h"
#include "CombatAM.h"
#include "Potion.h"
#include <vector>
#include <conio.h>


Player::Player() : 
	Character(20, 6, 4, 0.3f, 5) {
	InventoryMenu::SetInventory(&_playerInventory);
}

Player::Player(const Player& other)
	: Character(other._maxHealth, other._baseAttack, other._baseDefense, other._baseCritRatePercent, other._baseSpeed) {

}

//functional methods
void Player::ChooseAction(Character &other) {
	CombatAM playerActions(&other, this);
	ActionMap::AddActionMap(&playerActions);

	int startingInvSize = _playerInventory.Size();
	_playerCombatTurn = true;

	while (_playerCombatTurn)
	{
		ActionMap::GetCurrentMap().InputAction(static_cast<char>(_getch()));
		if (_playerCombatTurn //player didnt quick heal or attack
			&& _playerInventory.Size() < startingInvSize) {
			_playerCombatTurn = false; //if the inventory shrinks during player turn that means they used an item.
			ActionMap::PopCurrentMap(); //pop navigation map
		}
	}
	ActionMap::PopCurrentMap();
}

void Player::Attack(Character& other) {
	_playerCombatTurn = false;
	Character::Attack(other);
}

void Player::UseItem() {
	InventoryMenu::Navigate();
} 

void Player::QuickHeal() {
	for (int i = 0; i < _playerInventory.Size(); ++i) {
		Item* possibleHeal = _playerInventory.GetItem(i);
		if (possibleHeal->GetType() == ItemType::Potion 
			&& dynamic_cast<HealPotion*>(possibleHeal)) 
		{
			//use and remove item
			possibleHeal->TryUseItem(this);
			_playerInventory.RemoveOrSellItem(i, false);
			_playerCombatTurn = false;
			break;
		}
	}
}

void Player::Death(Character* killer) {
	//TO:DO display what room # player was on
}
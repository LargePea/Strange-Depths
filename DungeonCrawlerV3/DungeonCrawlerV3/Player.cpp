#include "Player.h"
#include "InventoryMenu.h"
#include "CombatAM.h"
#include "Potion.h"
#include "Screen.h"
#include <vector>
#include <conio.h>


Player::Player() : 
	Character(20, 6, 5, 0.3f, 5) {
	InventoryMenu::SetInventory(&_playerInventory);
}

Player::Player(const Player& other)
	: Character(other._maxHealth, other._baseAttack, other._baseDefense, other._baseCritRatePercent, other._baseSpeed) {

}

void Player::LoadStats() {
	UpdateStats();
	Screen::AddImages({ &_playerStats });
}

void Player::HideStats() {
	Screen::RemoveImages({ &_playerStats });
}

void Player::UpdateStats() {
	std::vector<std::string> stats{ 
		"        Health: " + std::to_string((int)_currentHealth), 
		"", 
		"Defense: " + std::to_string((int)_defense) + "     " + "Attack: " + std::to_string((int)_attack)};

	_playerStats = Image(stats, 2, { 74, 43 });
}

void Player::Damage(const float& incomingDamage, Character& attacker) {
	Character::Damage(incomingDamage, attacker);

	UpdateStats();
}

//functional methods
void Player::ChooseAction(Character &other) {


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
	Character::Death(killer);
	Screen::ClearImages();
	//TO:DO display what room # player was on
}
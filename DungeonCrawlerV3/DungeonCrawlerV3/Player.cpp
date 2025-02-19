#include "Player.h"
#include "InventoryMenu.h"
#include "CombatAM.h"
#include "Potion.h"
#include "Screen.h"
#include "Notification.h"
#include "SpriteAtlas.h"
#include <vector>
#include <conio.h>


Player::Player() : 
	Character(20, 6, 5, 0.3f, 5) {
	InventoryMenu::SetInventory(&_playerInventory);
	UpdateHealthStat();
	UpdateStats();
	Screen::AddImages({ &_playerHealth });
}

Player::Player(const Player& other)
	: Character(other._maxHealth, other._baseAttack, other._baseDefense, other._baseCritRatePercent, other._baseSpeed) {

}

void Player::LoadStats() {
	Screen::AddImages({ &_playerStats });
}

void Player::HideStats() {
	Screen::RemoveImages({ &_playerStats });
}

void Player::UpdateStats() {
	std::vector<std::string> stats{ 
		"Defense: " + std::to_string((int)_defense) + "     " + "Attack: " + std::to_string((int)_attack)};

	_playerStats = Image(stats, 2, { 74, 44 });
}

void Player::UpdateHealthStat() {
	_playerHealth = Image(std::vector<std::string>{std::to_string((int)_currentHealth)}, 2, { 101, 35 });
}

void Player::Damage(const float& incomingDamage, Character& attacker) {
	Character::Damage(incomingDamage, attacker);
	UpdateHealthStat();
}

void Player::Heal(const float& incomingHeal) {
	Character::Heal(incomingHeal);

	UpdateHealthStat();
}

//functional methods
void Player::ChooseAction(Character &other) {
	Character::ChooseAction(other);

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
			return;
		}
	}

	Notification noHealNotif({
		".You.have.no.Heal.Potions.",
		".Press.Any.Key.To.Continue."
		}, { 43, 39 });
}

void Player::Death(Character* killer) {
	Character::Death(killer);
	Screen::ClearImages();

	Notification gameOverNotif(GAMEOVER_MENU, { 0,0 });
}
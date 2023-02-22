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
	float recalculatedIncomingDamage = incomingDamage * (-2 * std::pow(_defense / (_defense + incomingDamage), incomingDamage / (_defense + incomingDamage)) + 2);
	float damagedhealth = std::round(_currentHealth - recalculatedIncomingDamage);

	std::string damageString = ".You.took." + std::to_string((int)std::round(recalculatedIncomingDamage)) + ".Damage.";
	std::string healthString = ".You.have." + std::to_string((int) (damagedhealth > 0 ? damagedhealth : 0)) + ".health.remaining.";

	Notification damageNotif({
		damageString,
		healthString,
		".Press.Any.Key.To.Continue."
	}, { 42, 38 });

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
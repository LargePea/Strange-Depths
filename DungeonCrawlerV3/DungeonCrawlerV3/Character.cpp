#include "Character.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

float Character::GetCurrentHealth() {
	return _currentHealth;
}

float Character::GetDefense() {
	return _defense;
}

float Character::GetSpeed() {
	return _speed;
}

void Character::Damage(float& incomingDamage) {

	float recalculatedIncomingDamage = incomingDamage * (- 2 * std::pow(_defense / (_defense + incomingDamage), incomingDamage / (_defense + incomingDamage)) + 2);
	float damagedhealth = std::round(_currentHealth - recalculatedIncomingDamage);

	//clamp health to a minimum of 0
	_currentHealth = damagedhealth > 0 ? damagedhealth : 0;
}

void Character::Attack(Character &other) {
	float damage = _attack;

	//generate seed value based on time
	std::srand((unsigned)std::time(nullptr));

	//change rolled number to a range of 1~100 and determine if it is within crit rate 
	if (_critRatePercentage >= (std::rand() + 1) % 101) {
		damage *= _criteDmgMultiplier;
	}

	other.Damage(damage);
}
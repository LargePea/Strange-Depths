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
	return _currentHealth;
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

	if (_critRateMultiplier >= std::rand() % 101) {
		damage *= _criteDmgMultiplier;
	}

	other.Damage(damage);
}
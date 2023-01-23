#include "Character.h"
#include <cmath>
#include <cstdlib>
#include <random>

void Character::Damage(float& incomingDamage) {

	float recalculatedIncomingDamage = incomingDamage * (- 2 * std::pow(_defense / (_defense + incomingDamage), incomingDamage / (_defense + incomingDamage)) + 2);
	float damagedhealth = std::round(_currentHealth - recalculatedIncomingDamage);

	//clamp health to a minimum of 0
	_currentHealth = damagedhealth > 0 ? damagedhealth : 0;
}

void Character::ModStats(float& incomingMod, CharacterStats& statToMod) {
	switch (statToMod)
	{
	case CharacterStats::Attack:
		_attackModifier += incomingMod;
		break;
	case CharacterStats::CritDmg:
		_critDmgModifier += incomingMod;
		break;
	case CharacterStats::CritRate:
		_critRateModifier += incomingMod;
		break;
	case CharacterStats::Defense:
		_defenseModifier += incomingMod;
		break;
	case CharacterStats::Speed:
		_speedModifier += incomingMod;
		break;
	case CharacterStats::Health:
	{
		//preserve health ratio when upgrading health
		float currentHealthRatio = _currentHealth / _baseMaxHealth;
		_maxHealthModifier += incomingMod;
		_currentHealth = std::round(_maxHealth * currentHealthRatio);
	}
		break;
	default:
		break;
	}
}

void Character::Attack(Character &other) {
	//static to save the state so it's actually randomized instead of rerolling the same state
	static std::uniform_int_distribution<int> dist(1, 100);
	static std::default_random_engine randGen;

	float damage = _attack;

	//generate seed value based on time
	std::srand((unsigned)std::time(nullptr));

	//change rolled number to a range of 1~100 and determine if it is within crit rate 
	if (_critRatePercent >= dist(randGen)) {
		damage *= _critDmgMulti;
	}

	other.Damage(damage);
}


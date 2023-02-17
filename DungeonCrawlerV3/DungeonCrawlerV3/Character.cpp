#include "Character.h"
#include <cmath>
#include <random>

Character::~Character() {
	if (_enchantment != nullptr)
		delete _enchantment;
}

void Character::Damage(const float& incomingDamage, Character& attacker) {
	float incomingDamageABS = incomingDamage > 0 ? incomingDamage : -incomingDamage;

	float recalculatedIncomingDamage = incomingDamageABS * (- 2 * std::pow(_defense / (_defense + incomingDamageABS), incomingDamageABS / (_defense + incomingDamageABS)) + 2);
	float damagedhealth = std::round(_currentHealth - recalculatedIncomingDamage);

	//clamp health to a minimum of 0
	_currentHealth = damagedhealth > 0 ? damagedhealth : 0;
	
	if (_currentHealth == 0) Death(&attacker);
}

void Character::Attack(Character& other) {
	//Invoke the attack event
	AttackEvent.Invoke();

	//static to save the state so it's actually randomized instead of rerolling the same state
	static std::uniform_int_distribution<int> dist(1, 100);
	static std::default_random_engine randGen;

	float damage = _attack;

	//change rolled number to a range of 1~100 and determine if it is within crit rate 
	if (_critRatePercent >= dist(randGen)) {
		damage *= _critDmgMulti;
	}

	other.Damage(damage, *this);
}

void Character::Death(Character* killer) {
	DeathEvent.Invoke(this);
}

void Character::Heal(const float& incomingHeal) {

	float healedHealth = std::round(_currentHealth + incomingHeal > 0 ? incomingHeal : -incomingHeal);

	_currentHealth = healedHealth > _maxHealth ? _maxHealth : healedHealth;
}

void Character::EquipEnchantment(IEquippable* toEquip) {
	if (_enchantment != nullptr) {
		_enchantment->UnequipItem();
		delete _enchantment;
	}
	toEquip->EquipItem();
	_enchantment = toEquip;
}

void Character::ModStat(float& incomingMod, float statToMod) {
	statToMod += incomingMod;
}

void Character::ModAttack(float& incomingMod) {
	ModStat(incomingMod, _attackModifier);
	_attack = _baseAttack * _attackModifier; 
}

void Character::ModDefense(float& incomingMod) {
	ModStat(incomingMod, _defenseModifier);
	_defense = _baseDefense * _defenseModifier; 
}

void Character::ModCritRate(float& incomingMod) {
	ModStat(incomingMod, _critRateModifier);
	_critRatePercent = _baseCritRatePercent + _critRateModifier;
}

void Character::ModSpeed(float& incomingMod) {
	ModStat(incomingMod, _speedModifier);
	_speed = _baseSpeed * _speedModifier;
}


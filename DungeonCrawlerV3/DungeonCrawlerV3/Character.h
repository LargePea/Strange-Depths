#pragma once
#include <iostream>
#include <deque>
#include "EventSystem.h"
#include "IEquippable.h"

class Character {
friend class Enchant;

private:
	//modifiers
	float _maxHealthModifier, _attackModifier, _defenseModifier, _speedModifier = 1;
	float _critRateModifier, _critDmgModifier = 0;

protected:

	//baseStats
	float _baseMaxHealth, _baseAttack, _baseCritRatePercent, _baseDefense, _baseSpeed = 0;
	float _baseCritDmgMulti = 2;

	//usefull stats
	float _currentHealth = _baseMaxHealth;
	float _maxHealth = _baseMaxHealth * _maxHealthModifier;

	float _attack = _baseAttack * _attackModifier;
	float _critRatePercent = _baseCritRatePercent + _critRateModifier;
	float _critDmgMulti = _baseCritDmgMulti + _critDmgModifier;

	float _defense = _baseDefense * _defenseModifier;
	float _speed = _baseSpeed * _speedModifier;

	//buffs
	const int _maxBuffs = 5;

	IEquippable* _enchantment = nullptr;

public:
	//Events
	Subject<> AttackEvent;
	Subject<> TurnBeginEvent;

public:
	Character(float maxHealth, float attack, float defense, float critRate, float speed) :
		_baseMaxHealth(maxHealth), _baseAttack(attack), _baseDefense(defense), _baseCritRatePercent(critRate), _baseSpeed(speed) {}
	Character(const Character& obj) {
		std::cout << "Copied" << "\n";
	};
	virtual ~Character() = default;

	//Getters
	inline float GetMaxHealth() { return _maxHealth; }

	inline float GetCurrentHealth() { return _currentHealth; }

	inline float GetDefense() { return _defense; }

	inline float GetSpeed() { return _speed; }

	inline float GetAttack() { return _attack; }

	//Functional methods
	//AI/Player chooses what to do in this function
	virtual void ChooseAction(Character& other) { TurnBeginEvent.Invoke(); }

	//Damage character
	void Damage(const float& incomingDamage, Character& attacker);

	//Heal character
	void Heal(const float& incomingHeal);

	//apply character enhancements
	void EquipEnchantment(IEquippable* toEquip);

	void ModStat(float& incomingMod, float Character::* statToMod);

	//Attack the opposing character
	void Attack(Character& other);

	//Use an Item
	virtual void UseItem() {}

	virtual void Death(Character* killer) {}
};
#pragma once
#include <iostream>
#include <deque>
#include "EventSystem.h"

enum class CharacterStats
{
	Attack,
	Health,
	CritRate,
	CritDmg,
	Defense,
	Speed
};

class Character {
private:
	//modifiers
	float _maxHealthModifier = 1;

	float _attackModifier = 1;
	float _critRateModifier = 1;
	float _critDmgModifier = 1;

	float _defenseModifier = 1;
	float _speedModifier = 1;

protected:
	float _currentHealth = 0;

	//baseStats
	float _baseMaxHealth = 20;

	float _baseAttack = 1;
	float _baseCritRatePercent = 0;
	float _baseCritDmgMulti = 2;

	float _baseDefense = 0;
	float _baseSpeed = 0;

	//usefull stats
	float _maxHealth = _baseMaxHealth * _maxHealthModifier;

	float _attack = _baseAttack * _attackModifier;
	float _critRatePercent = _baseCritRatePercent + _critRateModifier;
	float _critDmgMulti = _baseCritDmgMulti + _critDmgModifier;

	float _defense = _baseDefense * _defenseModifier;
	float _speed = _baseSpeed * _speedModifier;

	//buffs
	const int _maxBuffs = 5;

public:
	//Events
	Subject<> AttackEvent;
	Subject<> TurnBeginEvent;

public:
	Character() {

	};
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
	void Damage(const float& incomingDamage);

	//Heal character
	void Heal(const float& incomingHeal);

	//apply character enhancements
	void ModStats(float& incomingMod, CharacterStats& statToMod);

public:
	//Attack the opposing character
	void Attack(Character& other);

	//Use an Item
	virtual void UseItem() {}

	virtual void Death() {}

	//add buffs
	void AddBuff();

	void CheckBuffs();
};
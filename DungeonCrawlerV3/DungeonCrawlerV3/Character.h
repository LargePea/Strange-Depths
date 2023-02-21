#pragma once
#include <iostream>
#include <deque>
#include "EventSystem.h"
#include "IEquippable.h"

class Character {
private:
	//modifiers
	float _maxHealthModifier = 1, _attackModifier = 1, _defenseModifier = 1, _speedModifier = 1;
	float _critRateModifier = 0, _critDmgModifier = 0;

protected:

	//baseStats
	float _baseMaxHealth = 0, _baseAttack = 0, _baseCritRatePercent = 0, _baseDefense = 0, _baseSpeed = 0;
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
	Subject<Character*> DeathEvent;

public:
	Character(float maxHealth, float attack, float defense, float critRate, float speed) :
		_baseMaxHealth(maxHealth), _baseAttack(attack), _baseDefense(defense), _baseCritRatePercent(critRate), _baseSpeed(speed) {}
	Character(const Character& obj) = default;
	virtual ~Character();

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
	virtual void Damage(const float& incomingDamage, Character& attacker);

	//Heal character
	void Heal(const float& incomingHeal);

	//apply character enhancements
	void EquipEnchantment(IEquippable* toEquip);

	void ModAttack(float& incomingMod);
	void ModDefense(float& incomingMod);
	void ModCritRate(float& incomingMod);
	void ModSpeed(float& incomingMod);

	//Attack the opposing character
	virtual void Attack(Character& other);

	//Use an Item
	virtual void UseItem() {}

	virtual void Death(Character* killer);

private:
	void ModStat(float& incomingMod, float statToMod);

};
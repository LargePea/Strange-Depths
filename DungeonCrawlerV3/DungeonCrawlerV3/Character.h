#pragma once
#include <iostream>

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

public:
	Character() {

	};
	Character(const Character& obj) {
		std::cout << "Copied" << "\n";
	};
	virtual ~Character() = default;

	//Getters
	inline float GetCurrentHealth() { return _currentHealth; }

	inline float GetDefense() { return _defense; }

	inline float GetSpeed() { return _speed; }

	//Functional methods
	//AI/Player chooses what to do in this function
	virtual void ChooseAction(Character &other) {}

	//Damage character
	void Damage(float& incomingDamage);

	void ModStats(float& incomingMod, CharacterStats& statToMod);

protected:
	//Attack the opposing character
	void Attack(Character& other);

	//Use an Item
	virtual void UseItem() {}

	virtual void Death() {}
};
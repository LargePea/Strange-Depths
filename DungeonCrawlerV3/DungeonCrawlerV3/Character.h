#pragma once


class Character {
protected:
	//Stats
	float _maxHealth = 20;
	float _currentHealth = 20;

	float _attack = 1;
	float _critRateMultiplier = 0;
	float _criteDmgMultiplier = 2;

	float _defense = 0;
	float _speed = 0;

public:
	//Getters
	float GetCurrentHealth();

	float GetDefense();

	float GetSpeed();

	//Functional methods
	//AI/Player chooses what to do in this function
	virtual void ChooseAction(Character &other) = 0;

	//Damage character
	void Damage(float& incomingDamage);

protected:
	//Attack the opposing character
	void Attack(Character& other);

	//Use an Item
	virtual void UseItem() = 0;
};
#pragma once
#include "Character.h"
#include "IEquippable.h"

#include <map>

class Enchant : public IEquippable {
public:
enum EnchanmentTypes
{
	Attack,
	Defense,
	CritRate,
	Speed
};
private:
	std::map<EnchanmentTypes, float Character::*> _modificationTypeMap{
		{EnchanmentTypes::Attack, &Character::_attackModifier},
		{EnchanmentTypes::Defense, &Character::_defenseModifier},
		{EnchanmentTypes::CritRate, &Character::_critRateModifier},
		{EnchanmentTypes::Speed, &Character::_speedModifier}
	};

	const char* _name;
	float _modifyAmount = 0;
	float Character::* _moddedStat = &Character::_attackModifier;
	Character* _equippedCharacter = nullptr;

public:
	Enchant(const char* name, float modifyAmount, EnchanmentTypes enchantType);

	Enchant(const Enchant& other);

	~Enchant() = default;

	Enchant& operator=(Enchant other);

	void SetOwner(Character* owner);

	void EquipItem() override;

	void UnequipItem() override;
};
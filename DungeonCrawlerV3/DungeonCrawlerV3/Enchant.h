#pragma once
#include "Character.h"
#include "IEquippable.h"

#include <map>

class Enchant : public IEquippable {
using ModFunction = void(Character::*)(float&);

public:
enum class EnchanmentTypes
{
	Attack,
	Defense,
	CritRate,
	Speed
};
private:
	std::map<EnchanmentTypes, ModFunction> _modificationTypeMap{
		{EnchanmentTypes::Attack, &Character::ModAttack},
		{EnchanmentTypes::Defense, &Character::ModDefense},
		{EnchanmentTypes::CritRate, &Character::ModCritRate},
		{EnchanmentTypes::Speed,  &Character::ModSpeed}
	};

	const char* _name;
	float _modifyAmount = 0;
	ModFunction _moddedStat;
	Character* _equippedCharacter = nullptr;

public:
	Enchant(const char* name, float modifyAmount, EnchanmentTypes enchantType);

	Enchant(const Enchant& other);

	virtual ~Enchant() = default;

	Enchant& operator=(Enchant other);

	void SetOwner(Character* owner);

	void EquipItem() override;

	void UnequipItem() override;
};
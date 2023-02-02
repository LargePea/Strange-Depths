#pragma once
#include "Character.h"
#include "IEquippable.h"

class Enchant : public IEquippable {
private:
	const char* _name;
	float _modifyAmount = 0;
	float Character::* _moddedStat = &Character::_attackModifier;
	Character* _equippedCharacter = nullptr;

public:
	Enchant(const char* name, float modifyAmount, float Character::* moddedStat);

	Enchant(const Enchant& other);

	~Enchant() = default;

	Enchant& operator=(Enchant other);

	void SetOwner(Character* owner);

	void EquipItem() override;

	void UnequipItem() override;
};
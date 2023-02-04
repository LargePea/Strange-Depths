#pragma once
#include "Character.h"
#include "IEquippable.h"

class Enchant : public IEquippable {
	friend class SkeletonEnchant;
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

class SkeletonEnchant : public Enchant {
	SkeletonEnchant() : Enchant("Skeleton Enchant", 0.1, &Character::_attackModifier)
}
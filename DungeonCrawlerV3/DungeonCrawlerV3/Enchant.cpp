#include "Enchant.h"

Enchant::Enchant(const char* name, float modifyAmount, EnchanmentTypes enchanmentType) 
	: _name(name), _modifyAmount(modifyAmount), _moddedStat(_modificationTypeMap[enchanmentType]) {

}

Enchant::Enchant(const Enchant& other) {
	_name = other._name;
	_modifyAmount = other._modifyAmount;
	_moddedStat = other._moddedStat;
}

Enchant& Enchant::operator=(Enchant other) {
	_name = other._name;
	_modifyAmount = other._modifyAmount;
	_moddedStat = other._moddedStat;

	return *this;
}

void Enchant::SetOwner(Character* owner) {
	_equippedCharacter = owner;
}

void Enchant::EquipItem() {
	(_equippedCharacter->*_moddedStat)(_modifyAmount);
}

void Enchant::UnequipItem() {
	float negMod = -_modifyAmount;
	(_equippedCharacter->*_moddedStat)(negMod);
}
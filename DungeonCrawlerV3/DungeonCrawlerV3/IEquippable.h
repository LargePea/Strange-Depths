#pragma once
class IEquippable {
public:
	void virtual EquipItem() = 0;
	void virtual UnequipItem() = 0;
};
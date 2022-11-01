#pragma once
#include "Character.h"

class Player : public Character {
	//TO:DO add inventory

public:
	Player() {};

	void ChooseAction(Character& other) override;

protected:
	void UseItem() override;
};
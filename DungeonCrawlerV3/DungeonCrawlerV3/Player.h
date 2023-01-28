#pragma once
#include "Character.h"
#include <vector>

class Player : public Character {

private:


public:
	Player();

	//functional methods
	void ChooseAction(Character& other) override;

protected:
	void UseItem() override;

	void Death(Character& killer) override;
};
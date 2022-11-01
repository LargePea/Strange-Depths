#pragma once

#include "Image.h"
#include "Character.h"
#include <array>

class Enemy : public Character {
protected:
	//Display
	std::array<std::string, MAX_IMAGE_HEIGHT> _imageDisplay;


	//TO:DO Drops
	//TO:DO Inventory

public:
	Enemy() {};

	void ChooseAction(Character& other) override;

protected:
	void UseItem() override;
};
#pragma once

#include "Image.h"
#include "Character.h"
#include <array>
#include <iostream>

class Enemy : public Character {
protected:
	//Display
	std::array<std::string, MAX_IMAGE_HEIGHT> _imageDisplay;

	
	//TO:DO Drops
	//TO:DO Inventory
	//Special drop

public:
	std::string _name;
	Enemy(std::string name) : _name(name) {};

	Enemy(const Enemy& obj) {
		std::cout << "Copied" << "\n";
	};

	void ChooseAction(Character& other) override;

protected:
	void UseItem() override;
	
	void Death() override;
};
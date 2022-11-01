#pragma once

#include <string>
#include <iostream>
#include <array>

#define MAX_IMAGE_HEIGHT 50

class Image {
private:
	std::array<std::string, MAX_IMAGE_HEIGHT>& _image;
	int _priority = 0;
	std::array<int, 2>& _displayPosition;

public:
	Image(std::array<std::string, MAX_IMAGE_HEIGHT> &image, int priority, std::array<int, 2> &displayPosition);

	//Getters
	std::array<std::string, MAX_IMAGE_HEIGHT>* GetImage();

	size_t GetPriority();

	std::array<int, 2>* GetDisplayPosition();
};
#pragma once

#include <string>
#include <iostream>
#include <array>
#include <utility>

#define MAX_IMAGE_HEIGHT 50

class Image {
private:
	std::array<std::string, MAX_IMAGE_HEIGHT>& _image;
	int _priority = 0;
	std::pair<int, int> _displayPosition;

public:
	Image(std::array<std::string, MAX_IMAGE_HEIGHT> &image, int priority, std::pair<int, int> displayPos);

	//Getters
	inline std::array<std::string, MAX_IMAGE_HEIGHT>* GetImage() { return &_image; }

	inline size_t GetPriority() { return _priority; }

	inline const std::pair<int, int>& GetDisplayPosition() const { return _displayPosition; }

	friend bool operator<(const Image& lhs, const Image& rhs);
	friend bool operator>(const Image& lhs, const Image& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const Image& image);
};
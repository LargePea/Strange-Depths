#include "Image.h"
#include "Screen.h"
#include <fstream>

Image::Image(std::string imageFilePath, int priority, std::pair<int, int> displayPos)
	: _priority(priority), _displayPosition(displayPos)
{
	_image.reserve(SCREEN_HEIGHT);
	if (std::ifstream imageFile{ imageFilePath }) {
		std::string line;
		while (std::getline(imageFile, line)) {
			_image.emplace_back(line);
		}
		imageFile.close();
	}
	_image.shrink_to_fit();
}

Image::Image(std::vector<std::string> image, int priority, std::pair<int, int> displayPos)
	:_image(image), _priority(priority), _displayPosition(displayPos) { }

Image::Image(const Image& other) 
	:_image(other._image), _priority(other._priority), _displayPosition(other._displayPosition) { }

Image& Image::operator=(const Image& rhs) {
	this->_image = rhs._image;
	this->_priority = rhs._priority;
	this->_displayPosition = rhs._displayPosition;

	return *this;
}

Image::Image(Image&& other) noexcept
	:_image(other._image), _priority(other._priority), _displayPosition(other._displayPosition) {

	other._image = std::vector<std::string>();
	other._priority = 0;
	other._displayPosition = std::make_pair<int, int>(0, 0);
}

Image& Image::operator=(Image&& rhs) noexcept {
	if (this != &rhs) {
		_image = rhs._image;
		_priority = rhs._priority;
		_displayPosition = rhs._displayPosition;

		rhs._image = std::vector<std::string>();
		rhs._priority = 0;
		rhs._displayPosition = std::make_pair<int, int>(0, 0);
	}

	return *this;
}

Image Image::operator+(const Image& rhs) {
	std::pair<int, int> offset{ rhs._displayPosition.first - this->_displayPosition.first, rhs._displayPosition.second - this->_displayPosition.second };
	if (offset.first < 0 || offset.second < 0) return *this;

	const std::vector<std::string>& incomingImage = rhs.GetImage();
	std::vector<std::string> outgoingImage = this->_image;

	for (int row = 0; row < incomingImage.size() && row + offset.second < outgoingImage.size(); ++row) {
		if (incomingImage[row] == "") continue;
		for (int character = 0; character < incomingImage[row].size() && (character + offset.first) < outgoingImage[row + offset.second].size(); ++character) {
			outgoingImage[row + offset.second][character + offset.first] = incomingImage[row][character];
		}
	}

	return Image(outgoingImage, this->_priority, this->_displayPosition);
}

bool Image::ComparePointers(const Image* lhs, const Image* rhs) {
	return lhs->_priority < rhs->_priority;
}

bool operator>(const Image& lhs, const Image& rhs) {
	return !(lhs < rhs);
}

bool operator<(const Image& lhs, const Image& rhs)
{
	return lhs._priority < rhs._priority;
}
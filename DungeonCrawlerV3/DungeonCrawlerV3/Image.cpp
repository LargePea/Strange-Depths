#include "Image.h"
#include "Screen.h"
#include <fstream>

Image::Image(const char* imageFilePath, int priority, std::pair<int, int> displayPos)
	: _priority(priority), _displayPosition(displayPos)
{
	if (std::ifstream imageFile{ imageFilePath }) {
		std::string line;
		for (int i = 0; i < MAX_IMAGE_HEIGHT; ++i) {
			if (imageFile.eof()) break;
			std::getline(imageFile, line);
			_image[i] = line;
		}
	}
}

Image::Image(std::array<std::string, MAX_IMAGE_HEIGHT> image, int priority, std::pair<int, int> displayPos)
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

	other._image = std::array<std::string, MAX_IMAGE_HEIGHT>();
	other._priority = 0;
	other._displayPosition = std::make_pair<int, int>(0, 0);
}

Image& Image::operator=(Image&& rhs) noexcept {
	if (this != &rhs) {
		_image = rhs._image;
		_priority = rhs._priority;
		_displayPosition = rhs._displayPosition;

		rhs._image = std::array<std::string, MAX_IMAGE_HEIGHT>();
		rhs._priority = 0;
		rhs._displayPosition = std::make_pair<int, int>(0, 0);
	}

	return *this;
}

Image Image::operator+(const Image& rhs) {
	std::pair<int, int> offset{ rhs._displayPosition.first - this->_displayPosition.first, rhs._displayPosition.second - this->_displayPosition.second };
	if (offset.first < 0 || offset.second < 0) return *this;

	const std::array<std::string, MAX_IMAGE_HEIGHT>& incomingImage = rhs.GetImage();
	std::array<std::string, MAX_IMAGE_HEIGHT> outgoingImage = this->_image;

	for (int row = 0; row + offset.second < incomingImage.size(); ++row) {
		if (incomingImage[row] == "") continue;
		for (int character = 0; character < incomingImage[row].size() && (character + offset.first) < outgoingImage[row + offset.second].size(); ++character) {
			outgoingImage[row + offset.second][character + offset.first] = incomingImage[row][character];
		}
	}

	return Image(outgoingImage, this->_priority, this->_displayPosition);
}

bool operator>(const Image& lhs, const Image& rhs) {
	return !(lhs < rhs);
}

bool operator<(const Image& lhs, const Image& rhs)
{
	return lhs._priority < rhs._priority;
}

std::ostream& operator<<(std::ostream& stream, const Image& image) {
	static HANDLE handle = Screen::GetScreenHandler();
	const std::array<std::string, MAX_IMAGE_HEIGHT>& imageToPrint = image.GetImage();
	stream << std::flush; //flush buffer just incase program crashed and buffer is still full

	for (int row = 0; row < imageToPrint.size(); ++row) {
		//if the image is smaller than max size break early to prevent wasted time to render nothing
		if (imageToPrint[row].empty()) {
			Screen::ResetCursor();
			stream << std::flush;
			return stream;
		}

		for (int character = 0; character < imageToPrint[row].size(); ++character) {

			char possiblePixel = imageToPrint[row][character];
			if (possiblePixel == ' ') continue; //To display transparency, dont render pixels that are "transparent"

			Screen::MoveCursor(image.GetDisplayPosition().first + character, image.GetDisplayPosition().second + row);
			//determine if pixel is actually whitespace
			if (possiblePixel == '.') possiblePixel = ' ';
			stream << possiblePixel;
		}
		stream << "\n";
	}

	Screen::ResetCursor();
	stream << std::flush;
	return stream;
}
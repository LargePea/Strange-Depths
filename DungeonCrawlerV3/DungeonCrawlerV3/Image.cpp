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

bool operator<(const Image& lhs, const Image& rhs) {
	return lhs._priority < rhs._priority;
}

bool operator>(const Image& lhs, const Image& rhs) {
	return !(lhs < rhs);
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
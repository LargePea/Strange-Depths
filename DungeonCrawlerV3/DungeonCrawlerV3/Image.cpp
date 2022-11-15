#include "Image.h"

Image::Image(std::array<std::string, MAX_IMAGE_HEIGHT> &image, int priority, std::array<int, 2> &displayPosition)
	:_image(image), _priority(priority), _displayPosition(displayPosition)
{

}

//Getters
std::array<std::string, MAX_IMAGE_HEIGHT>* Image::GetImage() {
	return &_image;
}

size_t Image::GetPriority() {
	return _priority;
}

std::array<int, 2>* Image::GetDisplayPosition() {
	return &_displayPosition;
}
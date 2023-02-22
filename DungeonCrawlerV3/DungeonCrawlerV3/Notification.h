#pragma once

#include "Image.h"

class Notification : public Image{
private:
	Notification(const Notification&);
	Notification& operator=(Notification){}

	std::vector<std::string> GenerateNotifBox(std::initializer_list<std::string> image);

public:
	Notification(std::initializer_list<std::string> image, std::pair<int, int> displayPos, int priority = 10);

	Notification(const char* imageFilePath, std::pair<int, int> displayPos, int priority = 10);

	~Notification();
};
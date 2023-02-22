#pragma once

#include "Image.h"

class Notification : public Image{
private:
	Notification(const Notification&);
	Notification& operator=(Notification){}

public:
	Notification(std::vector<std::string> image, std::pair<int, int> displayPos, int priority = 10);

	Notification(const char* imageFilePath, std::pair<int, int> displayPos, int priority = 10);

	~Notification();
};
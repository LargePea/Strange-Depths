#include "Notification.h"
#include "Screen.h"
#include <conio.h>

Notification::Notification(std::initializer_list<std::string> image, std::pair<int, int> displayPos, int priority)
	:Image(GenerateNotifBox(image), priority, displayPos) {
	Screen::AddImages({ this });
	_getch();
}

Notification::Notification(const char* imageFilepath, std::pair<int, int> displayPos, int priority)
	: Image(imageFilepath, priority, displayPos) {
	Screen::AddImages({ this });
	_getch();
}

Notification::~Notification() {
	Screen::RemoveImages({ this });
}

std::vector<std::string> Notification::GenerateNotifBox(std::initializer_list<std::string> image) {
	std::vector<std::string> output;
	output.reserve(image.size() + 4);

	int largestLine = 0;
	for (auto& line : image)
		if (line.size() > largestLine)
			largestLine = line.size();

	output.emplace_back(std::string(largestLine + 2, '='));
	output.emplace_back('|' +  std::string(largestLine, '.') + '|');
	for (auto& line : image) {
		int firstHalfSpacing = (largestLine - line.size()) / 2;
		int secondHalfSpacing = line.size() % 2 == largestLine % 2 ? firstHalfSpacing : firstHalfSpacing + 1;
		output.emplace_back('|' + std::string(firstHalfSpacing, '.') + line + std::string(secondHalfSpacing, '.') + '|');
	}

	output.emplace_back('|' + std::string(largestLine, '.') + '|');
	output.emplace_back(std::string(largestLine + 2, '='));

	return output;
}
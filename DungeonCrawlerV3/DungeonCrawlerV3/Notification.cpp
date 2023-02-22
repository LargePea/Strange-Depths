#include "Notification.h"
#include "Screen.h"
#include <conio.h>

Notification::Notification(std::vector<std::string> image, std::pair<int, int> displayPos, int priority)
	:Image(image, priority, displayPos) {
	Screen::AddImages({ this });
	_getch();
}

Notification::~Notification() {
	Screen::RemoveImages({ this });
}
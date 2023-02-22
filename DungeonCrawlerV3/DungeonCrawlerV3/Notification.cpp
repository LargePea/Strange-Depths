#include "Notification.h"
#include "Screen.h"
#include <conio.h>

Notification::Notification(Image notification)
	:_notifImage(notification) {
	Screen::AddImages({ &_notifImage });
	_getch();
}

Notification::~Notification() {
	Screen::RemoveImages({ &_notifImage });
}
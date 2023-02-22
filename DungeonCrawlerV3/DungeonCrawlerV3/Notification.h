#pragma once

#include "Image.h"

class Notification {
private:
	Image _notifImage;

private:
	Notification(const Notification&);
	Notification& operator=(Notification){}

public:
	Notification(Image _notification);

	~Notification();
};
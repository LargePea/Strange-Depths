#pragma once
#include "Room.h"
#include "Shop.h"
#include "ShopRoomAM.h"
#include "EventSystem.h"
#include <array>

class ShopRoom : public Room {
friend class Room;

private:
	Shop _shop;
	ShopRoomAM _actionMap;
	IEvent<>* _event;

protected:
	ShopRoom();

	void UnlockExit();

public:
	~ShopRoom() override;
};
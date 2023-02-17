#pragma once
#include "ActionMap.h"
#include "TreasureRoom.h"


class TreasureRoomAM : public ActionMap {
private:
	TreasureRoom& _room;
public:
	TreasureRoomAM(TreasureRoom& room);

	void InputAction(const char input) override;
};
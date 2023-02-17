#pragma once
#include "ActionMap.h"
#include "Chest.h"


class TreasureRoomAM : public ActionMap {
private:
	Chest* _chest;
public:
	TreasureRoomAM(Chest* chest);

	void InputAction(const char input) override;
};
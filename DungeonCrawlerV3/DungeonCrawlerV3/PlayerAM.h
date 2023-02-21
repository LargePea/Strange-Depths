#pragma once

#include "ActionMap.h"

class PlayerAM : public ActionMap {
public:
	PlayerAM();

	void InputAction(const char input) override;
};
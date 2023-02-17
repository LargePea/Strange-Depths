#pragma once

#include "ActionMap.h"

class PlayerAM : public ActionMap {
public:
	PlayerAM() = default;

	void InputAction(const char input) override;
};
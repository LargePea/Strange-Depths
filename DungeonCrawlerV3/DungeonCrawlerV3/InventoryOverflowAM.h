#pragma once

#include "ActionMap.h"

class InventoryOverflowAM : public ActionMap {
public:
	InventoryOverflowAM();

	void InputAction(const char input) override;
};
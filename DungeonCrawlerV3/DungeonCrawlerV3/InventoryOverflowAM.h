#pragma once

#include "ActionMap.h"

class InventoryOverflowAM : public ActionMap {
public:
	InventoryOverflowAM() = default;

	void InputAction(const char input) override;
};
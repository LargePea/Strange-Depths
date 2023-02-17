#pragma once

#include "ActionMap.h"

class InventoryMenuAM : public ActionMap {
public:
	InventoryMenuAM() = default;

	void InputAction(const char input) override;
};
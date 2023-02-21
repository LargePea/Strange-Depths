#pragma once

#include "ActionMap.h"

class InventoryMenuAM : public ActionMap {
public:
	InventoryMenuAM();

	void InputAction(const char input) override;
};
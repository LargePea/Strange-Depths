#pragma once

#include "ActionMap.h"
#include "Shop.h"

class ShopRoomAM : public ActionMap {
private:
	Shop _shop;
public:
	ShopRoomAM(Shop shop);

	void InputAction(const char input) override;
};
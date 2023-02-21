#include "ShopRoomAM.h"

ShopRoomAM::ShopRoomAM(Shop shop)
	:ActionMap(Image("Sprites\\ShopMenu.txt", 1, std::make_pair<int, int>(0, 37))), _shop(shop) {

}

void ShopRoomAM::InputAction(const char input) {
	switch (input)
	{
	case 'w':
	case 'W':
		_shop.PrevItem();
		break;
	case 's':
	case 'S':
		_shop.NextItem();
		break;
	case 'c':
	case 'C':
		_shop.BuyItem();
		break;
	case 'e':
	case 'E':
		_shop.SellItems();
		break;
	case 'q':
	case 'Q':
		PopCurrentMap();
		break;
	default:
		break;
	}
}
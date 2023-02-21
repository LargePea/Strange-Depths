#include "CombatAM.h"
#include "SpriteAtlas.h"

CombatAM::CombatAM(Character* opponent, Player* user)
	:ActionMap(Image(COMBAT_MENU, 1, std::make_pair<int, int>(0, 37))), _opponent(opponent), _user(user) {}

void CombatAM::InputAction(const char input) {
	switch (input)
	{
	case 'e':
	case 'E':
		_user->UseItem();
		break;
	case 'q':
	case 'Q':
		_user->QuickHeal();
		break;
	case 'w':
	case 'W':
		_user->Attack(*_opponent);
	default:
		break;
	}
}
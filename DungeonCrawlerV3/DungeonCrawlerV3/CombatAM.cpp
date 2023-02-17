#include "CombatAM.h"

CombatAM::CombatAM(Character* opponent, Player* user)
	:_opponent(opponent), _user(user) {}

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
	case 'w':
	case 'W':
		_user->Attack(*_opponent);
	default:
		break;
	}
}
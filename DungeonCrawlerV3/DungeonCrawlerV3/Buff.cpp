#include "Buff.h"

bool Buff::TryUseBuff(Character& user) {
	if (GameState::GetStateMask() & _activeGameStates)
	{
		UseBuff(user);
		return true;
	}
	else return false;
}
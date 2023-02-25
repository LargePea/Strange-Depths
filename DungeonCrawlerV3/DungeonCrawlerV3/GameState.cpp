#include "GameState.h"

GameStateMask GameState::_currentGameState;

int GameState::GetStateMask() {
	int state = (int) _currentGameState;
	return state;
}

void GameState::SetStateMask(GameStateMask newState) {
	_currentGameState = newState;
}

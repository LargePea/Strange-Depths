#include "GameState.h"

GameStateMask GameState::_currentGameState;

int GameState::GetStateMask() {
	return (int) _currentGameState;
}

void GameState::SetStateMask(GameStateMask newState) {
	_currentGameState = newState;
}

#pragma once

enum class GameStateMask
{
	Normal = 1,
	Combat = 2,
	GameOver = 4,
};

class GameState {
private:
	static GameStateMask _currentGameState;

private:
	GameState() {};

public:
	//Getters
	static int GetStateMask();

	//Setters
	static void SetStateMask(GameStateMask& newState);
};
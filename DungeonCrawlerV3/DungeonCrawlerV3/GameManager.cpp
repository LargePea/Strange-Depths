#include "GameManager.h"
#include "GameState.h"
#include "Player.h"
#include <vector>
#include <conio.h>

Character* GameManager::_player;
PlayerAM GameManager::_playerControls;

void GameManager::Init() {
	Player player = Player();
	SetPlayer(&player);
	ActionMap::AddActionMap(&_playerControls);

	//main game loop
	while (~(GameState::GetStateMask() & (int)GameStateMask::GameOver)) {
		ActionMap::GetCurrentMap().InputAction(static_cast<char>(_getch()));
	}

	ActionMap::PopCurrentMap();
}


void GameManager::SetPlayer(Character* player) {
	_player = player;
}

void GameManager::BeginCombat(Character enemy) {
	Character* first = _player->GetSpeed() >= enemy.GetSpeed() ? _player : &enemy;
	Character* second = _player->GetSpeed() >= enemy.GetSpeed() ? &enemy: _player;

	first->DeathEvent.Attach(&GameManager::EndCombat);
	second->DeathEvent.Attach(&GameManager::EndCombat);

	GameState::SetStateMask(GameStateMask::Combat);
	bool firstCharacterturn = true;

	//Combat loop
	while (GameState::GetStateMask() == (int) GameStateMask::Combat)
	{
		if (firstCharacterturn) first->ChooseAction(*second);
		else second->ChooseAction(*first);

		firstCharacterturn = !firstCharacterturn;
	}
}

void GameManager::EndCombat(Character* deadCharacter) {
	if(deadCharacter == _player) GameState::SetStateMask(GameStateMask::GameOver);
	else GameState::SetStateMask(GameStateMask::Normal);
}
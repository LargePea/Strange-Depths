#include "GameManager.h"
#include "GameState.h"
#include "Player.h"
#include "Screen.h"
#include "Room.h"
#include "SpriteAtlas.h"
#include "CombatAM.h"
#include <conio.h>

Character* GameManager::_player;
PlayerAM GameManager::_playerControls;

void GameManager::Init() {
	Image menuImage = Image(MENU_BASE, 0, std::make_pair<int, int>(0, 36));
	Image backgroundImage = Image(BASIC_BACKGROUND, 0, std::make_pair<int, int>(0, 0));

	Screen::AddImages({ &menuImage, &backgroundImage });

	Player player;
	SetPlayer(&player);
	ActionMap::AddActionMap(&_playerControls);
	Room::Init();
	Screen::AddImages({ Room::GetProgress() });

	//main game loop
	while (~GameState::GetStateMask() & (int)GameStateMask::GameOver) {
		ActionMap::GetCurrentMap().InputAction(static_cast<char>(_getch()));
	}

	ActionMap::PopCurrentMap();
	Room::ResetRooms();
}


void GameManager::SetPlayer(Character* player) {
	_player = player;
}

void GameManager::BeginCombat(Character* enemy) {
	CombatAM playerActions(enemy, static_cast<Player*>(_player));
	ActionMap::AddActionMap(&playerActions);

	Character* first = _player->GetSpeed() >= enemy->GetSpeed() ? _player : enemy;
	Character* second = _player->GetSpeed() >= enemy->GetSpeed() ? enemy: _player;

	IEvent<Character*>* firstDeathEvent = first->DeathEvent.Attach(&GameManager::EndCombat);
	IEvent<Character*>* secondDeathEvent = second->DeathEvent.Attach(&GameManager::EndCombat);

	GameState::SetStateMask(GameStateMask::Combat);
	bool firstCharacterturn = true;

	//Combat loop
	while (GameState::GetStateMask() & (int) GameStateMask::Combat)
	{
		if (firstCharacterturn) first->ChooseAction(*second);
		else second->ChooseAction(*first);

		firstCharacterturn = !firstCharacterturn;
	}

	ActionMap::PopCurrentMap();
	first->DeathEvent.Remove(firstDeathEvent);
	second->DeathEvent.Remove(secondDeathEvent);
}

void GameManager::EndCombat(Character* deadCharacter) {
	if(deadCharacter == _player) GameState::SetStateMask(GameStateMask::GameOver);
	else GameState::SetStateMask(GameStateMask::Normal);
}

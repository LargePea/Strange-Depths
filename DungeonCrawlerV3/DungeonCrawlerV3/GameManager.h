#pragma once

#include "Character.h"
#include "PlayerAM.h"
#include "Image.h"

class GameManager {
private:
	static Character* _player;
	static PlayerAM _playerControls;

private:
	GameManager();

public:
	static void Init();

	static void SetPlayer(Character* player);

	static void BeginCombat(Character* enemy);

	static void EndCombat(Character* deadCharacter);
};
#pragma once

#include "Character.h"

class GameManager {
private:
	static Character* _player;

private:
	GameManager();

public:
	static void SetPlayer(Character* player);

	static void BeginCombat(Character enemy);

	static void EndCombat(Character* deadCharacter);
};
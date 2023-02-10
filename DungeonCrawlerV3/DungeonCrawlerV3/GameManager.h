#pragma once

#include "Character.h"

class GameManager {
private:
	static Character* _player;

private:
	GameManager();

public:
	static void SetPlayer(Character* player);

	static void BeginCombat(std::initializer_list<Character> enemies);

	static void EndCombat();
};
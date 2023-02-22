#pragma once

#include "ActionMap.h"
#include "Character.h"
#include "Player.h"

class CombatAM;

class CombatAM : public ActionMap {
private:
	Character* _opponent;
	Player* _user;

public:
	CombatAM(Character* opponent, Player* user);

	void InputAction(const char input) override;

	void OnActivate() override;

	void OnDeactivate() override;
};
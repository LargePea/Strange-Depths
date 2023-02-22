#pragma once
#include "GameState.h"
#include "Character.h"
#include "EventSystem.h"

class Buff {
protected:
	int _activeGameStates;
	int _maxUses;
	int _usesRemaining = _maxUses;
	Character* _user = nullptr;
	IEvent<>* _buffEvent;

public:
	Buff(Character* user, int uses, int activeGameState);
	virtual ~Buff() = default;

	void TryUseBuff();
	virtual void UseBuff() {}
	virtual void NoMoreUses() {}
};

class LifeSteal : public Buff {
private:
	float _lifeStealStrength;
public:
	LifeSteal(Character* user, int uses, float lifeStealStrength);
	~LifeSteal() override = default;

	void UseBuff() override;
	void NoMoreUses() override;
};

class Regeneration : public Buff {
private:
	float _totalHealPercent;
public:
	Regeneration(Character* user, int uses, float totalHealPercent);
	~Regeneration() override = default;

	void UseBuff() override;
	void NoMoreUses() override;
};
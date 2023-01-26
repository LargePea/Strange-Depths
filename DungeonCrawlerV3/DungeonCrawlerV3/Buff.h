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
	Event<Buff> _buffEvent{ this, &Buff::TryUseBuff };

public:
	Buff(Character* user, int uses);
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
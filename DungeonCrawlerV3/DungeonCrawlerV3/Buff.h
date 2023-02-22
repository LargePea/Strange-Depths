#pragma once
#include "GameState.h"
#include "Character.h"
#include "EventSystem.h"
#include <vector>

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

	virtual void IncreaseUses(int additionalUses) { _usesRemaining += additionalUses; }
};

class LifeSteal : public Buff {
friend class LifeStealPotion;

private:
	static std::vector<LifeSteal*> _activeLifeStealBuffs;
	float _lifeStealStrength;

public:
	LifeSteal(Character* user, int uses, float lifeStealStrength);
	~LifeSteal() override = default;

	void UseBuff() override;
	void NoMoreUses() override;

	static void DeactivateBuff(LifeSteal* buff);
};

class Regeneration : public Buff {
friend class RegenPotion;

private:
	static std::vector<Regeneration*> _activeRegenerationBuffs;
	float _totalHealPercent;
public:
	Regeneration(Character* user, int uses, float totalHealPercent);
	~Regeneration() override = default;

	void UseBuff() override;
	void NoMoreUses() override;
	void IncreaseUses(int additionalUses) override;

	static void DeactivateBuff(Regeneration* buff);
};
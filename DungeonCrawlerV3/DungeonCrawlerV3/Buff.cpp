#include "Buff.h"

//Base buff
Buff::Buff(Character* user, int uses) : _user(user), _maxUses(uses), _activeGameStates(0) {}

void Buff::TryUseBuff() {
	if (GameState::GetStateMask() & _activeGameStates && _user != nullptr && _usesRemaining > 0) 
		UseBuff();

	if (_usesRemaining == 0)
		NoMoreUses();
}

//LifeSteal

LifeSteal::LifeSteal(Character* user, int uses, float lifeStealStrength) : Buff(user, uses), _lifeStealStrength(lifeStealStrength) {
	_activeGameStates = static_cast<int>(GameStateMask::Combat);
	_user->AttackEvent.Attach(&_buffEvent);
}

void LifeSteal::UseBuff() {
	float healAmount = _lifeStealStrength * _user->GetAttack();
	_user->Heal(healAmount);

	--_usesRemaining;
}

void LifeSteal::NoMoreUses() {
	_user->AttackEvent.Remove(&_buffEvent);
}

//Rengeneration
Regeneration::Regeneration(Character* user, int uses, float totalHealPercent) : Buff(user, uses), _totalHealPercent(totalHealPercent) { 
	_activeGameStates = static_cast<int>(GameStateMask::Combat); 
	_user->TurnBeginEvent.Attach(&_buffEvent);
	UseBuff();
}

void Regeneration::UseBuff() {
	float healAmount = (_user->GetMaxHealth() * _totalHealPercent) / _maxUses;
	_user->Heal(healAmount);

	--_usesRemaining;
}

void Regeneration::NoMoreUses() {
	_user->TurnBeginEvent.Remove(&_buffEvent);
}
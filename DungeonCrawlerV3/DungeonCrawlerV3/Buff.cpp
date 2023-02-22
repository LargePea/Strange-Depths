#include "Buff.h"
#include "Notification.h"

//Base buff
Buff::Buff(Character* user, int uses, int activeGameState = 0) : 
	_user(user), _maxUses(uses), _activeGameStates(activeGameState) {}

void Buff::TryUseBuff() {
	if (GameState::GetStateMask() & _activeGameStates && _user != nullptr && _usesRemaining > 0) 
		UseBuff();

	if(_usesRemaining == 0)
	{
		NoMoreUses();
	}
}

//LifeSteal

LifeSteal::LifeSteal(Character* user, int uses, float lifeStealStrength) : 
	Buff(user, uses, static_cast<int>(GameStateMask::Combat)), _lifeStealStrength(lifeStealStrength) {
	_buffEvent = _user->AttackEvent.Attach((Buff*)this, &Buff::TryUseBuff, true);
}

void LifeSteal::UseBuff() {
	float healAmount = _lifeStealStrength * _user->GetAttack();
	_user->Heal(healAmount);

	--_usesRemaining;

	Notification lSNotif({
	".You.used.a.LifeSteal.Buff."
	".Uses.Remaining:." + std::to_string(_usesRemaining) + ".",
	".Press.Any.Key.To.Continue."
		}, { 42, 38 });
}

void LifeSteal::NoMoreUses() {
	_user->AttackEvent.Remove(_buffEvent);
}

//Rengeneration
Regeneration::Regeneration(Character* user, int uses, float totalHealPercent) : 
	Buff(user, uses, static_cast<int>(GameStateMask::Combat)), _totalHealPercent(totalHealPercent) {
	_buffEvent = _user->TurnBeginEvent.Attach((Buff*)this, &Buff::TryUseBuff, true);
	UseBuff();
}

void Regeneration::UseBuff() {
	float healAmount = (_user->GetMaxHealth() * _totalHealPercent) / _maxUses;
	_user->Heal(healAmount);

	--_usesRemaining;

	Notification regenNotif({
		".You.used.a.Regeneration.Buff."
		".Uses.Remaining:." + std::to_string(_usesRemaining) + ".",
		".Press.Any.Key.To.Continue."
		}, { 42, 38 });
}

void Regeneration::NoMoreUses() {
	_user->TurnBeginEvent.Remove(_buffEvent);
}
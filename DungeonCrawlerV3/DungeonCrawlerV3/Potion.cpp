#include "Potion.h"

void LifeStealPotion::UseItem(Character* user) {
	for (auto& buff : LifeSteal::_activeLifeStealBuffs) {
		if (buff->_user == user) {
			buff->IncreaseUses(buff->_maxUses);
			return;
		}
	}

	LifeSteal::_activeLifeStealBuffs.push_back(new LifeSteal(user, _buffDuration, _lifeStealStrength));
}

void RegenPotion::UseItem(Character* user) {
	for (auto& buff : Regeneration::_activeRegenerationBuffs) {
		if (buff->_user == user) {
			buff->IncreaseUses(buff->_maxUses);
			return;
		}
	}

	Regeneration::_activeRegenerationBuffs.push_back(new Regeneration(user, _buffDuration, _regenTotalPercentage));
}

void HealPotion::UseItem(Character* user) {
	user->Heal(_healStrength);
}
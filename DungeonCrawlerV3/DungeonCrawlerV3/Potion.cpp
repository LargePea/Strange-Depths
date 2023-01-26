#include "Potion.h"

void LifeStealPotion::UseItem(Character& user) {
	new LifeSteal(&user, _buffDuration, _lifeStealStrength);
}

void RegenPotion::UseItem(Character& user) {
	new Regeneration(&user, _buffDuration, _regenTotalPercentage);
}

void HealPotion::UseItem(Character& user) {
	user.Heal(_healStrength);
}
#include "Enchantment.h"

void Enchantment::UseItem(Character* user) {
	Enchant* enchant = new Enchant(_enchant);
	enchant->SetOwner(user);
}
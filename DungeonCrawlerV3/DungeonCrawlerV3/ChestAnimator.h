#pragma once

#include "Animator.h"
#include "SpriteAtlas.h"

class ChestAnimator : public Animator {
public:
	ChestAnimator(Image* targetImage)
		: Animator({
			AnimationClip(CHEST_OPEN, true, false)
			}, targetImage) {

	}
};
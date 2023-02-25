#pragma once

#include "Animator.h"
#include "SpriteAtlas.h"
#include "TriggerCondition.h"
#include "EmptyCondition.h"

class BansheeAnimator : public Animator {
public:
	BansheeAnimator(Image* targetImage) :
		Animator({ AnimationClip(BANSHEE_IDLE, false, true),
		AnimationClip(BANSHEE_ATTACK, true, false) }, targetImage) {

		_triggerConditions["Attack"] = false;
		AddConditions(&_animationClips[0], { new TriggerCondition(&_animationClips[1], true, &_triggerConditions["Attack"]) });
		AddConditions(&_animationClips[1], { new EmptyCondition(&_animationClips[0]) });
	}
};
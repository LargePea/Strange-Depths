#pragma once

#include "Animator.h"
#include "SpriteAtlas.h"
#include "TriggerCondition.h"
#include "EmptyCondition.h"

class OgreAnimator : public Animator {
public:
	OgreAnimator(Image* targetImage) :
		Animator({ AnimationClip(OGRE_IDLE, false, true),
		AnimationClip(OGRE_ATTACK, true, false) }, targetImage) {

		_triggerConditions["Attack"] = false;
		AddConditions(&_animationClips[0], { new TriggerCondition(&_animationClips[1], true, &_triggerConditions["Attack"]) });
		AddConditions(&_animationClips[1], { new EmptyCondition(&_animationClips[0]) });
	}
};
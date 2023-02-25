#pragma once

#include "Animator.h"
#include "SpriteAtlas.h"
#include "TriggerCondition.h"
#include "EmptyCondition.h"

class ShopAnimator : public Animator {
public:
	ShopAnimator(Image* targetImage)
		: Animator({
			AnimationClip(SHOP_IDLE, false, true),
			AnimationClip(SHOP_BUY, true, false)
			}, targetImage)
	{

		_triggerConditions["Buy"] = false;
		AddConditions(&_animationClips[0], { new TriggerCondition(&_animationClips[1], true, &_triggerConditions["Buy"]) });
		AddConditions(&_animationClips[1], { new EmptyCondition(&_animationClips[0]) });
	}
};
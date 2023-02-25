#pragma once

#include "AnimatorCondition.h"

class EmptyCondition : public AnimatorCondition {
public:
	EmptyCondition(AnimationClip* targetClip) : AnimatorCondition(targetClip){}

	bool CheckCondition() const override { return true; }
};
#pragma once

#include "AnimationClip.h"

class AnimatorCondition {
private:
	AnimationClip* _targetClip;

public:
	AnimatorCondition(AnimationClip* targetClip) : _targetClip(targetClip){}

	virtual ~AnimatorCondition() = default;

	virtual bool CheckCondition() const = 0;

	inline const AnimationClip* GetTargetClip() const { return _targetClip; }
};
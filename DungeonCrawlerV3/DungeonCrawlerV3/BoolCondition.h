#pragma once

#include "AnimatorCondition.h"

class BoolCondition : public AnimatorCondition {
private:
	bool _checkCondition;
	bool* _conditionToCheck;

public:
	BoolCondition(AnimationClip* targetClip, bool checkCondition, bool* conditionToCheck) : AnimatorCondition(targetClip), _checkCondition(checkCondition), _conditionToCheck(conditionToCheck) {}

	~BoolCondition() override = default;

	bool CheckCondition() const override { return _checkCondition == *_conditionToCheck; }
};
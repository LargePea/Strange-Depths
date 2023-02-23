#pragma once

#include "AnimatorCondition.h"

class BoolCondition : public AnimatorCondition {
private:
	bool _checkCondition;
	bool* _conditionToCheck;

public:
	BoolCondition(bool checkCondition, bool* conditionToCheck) : _checkCondition(checkCondition), _conditionToCheck(conditionToCheck) {}

	~BoolCondition() override = default;

	bool CheckCondition() const override { return _checkCondition == *_conditionToCheck; }
};
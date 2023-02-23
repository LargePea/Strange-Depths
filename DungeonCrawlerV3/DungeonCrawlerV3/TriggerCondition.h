#pragma once

#include "AnimatorCondition.h"

class TriggerCondition : public AnimatorCondition {
private:
	bool _checkCondition;
	bool* _conditionToCheck;

public:
	TriggerCondition(bool checkCondition, bool* conditionToCheck) : _checkCondition(checkCondition), _conditionToCheck(conditionToCheck) {}

	~TriggerCondition() override = default;

	bool CheckCondition() const override {
		if (_checkCondition == *_conditionToCheck) {
			*_conditionToCheck = false;
			return true;
		}

		return false;
	}
};

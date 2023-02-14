#include "ActionMap.h"

std::stack<ActionMap*> ActionMap::_actionMapStack;

ActionMap& ActionMap::GetCurrentMap() {
	return *_actionMapStack.top();
}

void ActionMap::PopCurrentMap() {
	_actionMapStack.pop();
}

void ActionMap::AddActionMap(ActionMap* newMap) {
	_actionMapStack.emplace(newMap);
}
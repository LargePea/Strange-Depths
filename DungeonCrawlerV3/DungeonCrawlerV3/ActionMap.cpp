#include "ActionMap.h"
#include "Screen.h"

std::stack<ActionMap*> ActionMap::_actionMapStack;

ActionMap::ActionMap(Image actionMenu)
	: _actionMenu(actionMenu){ }

void ActionMap::PopCurrentMap() {
	GetCurrentMap().RemoveMapImage();
	GetCurrentMap().OnDeactivate();
	_actionMapStack.pop();
	if (_actionMapStack.size() == 0) return;

	GetCurrentMap().AddMapImage();
	GetCurrentMap().OnActivate();
}

void ActionMap::AddActionMap(ActionMap* newMap) {
	if (_actionMapStack.size() != 0) {
		GetCurrentMap().RemoveMapImage();
		GetCurrentMap().OnDeactivate();
	}
	_actionMapStack.emplace(newMap);
	GetCurrentMap().AddMapImage();
	GetCurrentMap().OnActivate();
}
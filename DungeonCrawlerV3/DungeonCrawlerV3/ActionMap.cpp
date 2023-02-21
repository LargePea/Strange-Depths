#include "ActionMap.h"
#include "Screen.h"

std::stack<ActionMap*> ActionMap::_actionMapStack;

ActionMap::ActionMap(Image actionMenu)
	: _actionMenu(actionMenu){ }

void ActionMap::PopCurrentMap() {
	GetCurrentMap().RemoveMapImage();
	_actionMapStack.pop();
	GetCurrentMap().AddMapImage();
}

void ActionMap::AddActionMap(ActionMap* newMap) {
	if(_actionMapStack.size() != 0) GetCurrentMap().RemoveMapImage();
	_actionMapStack.emplace(newMap);
	GetCurrentMap().AddMapImage();
}
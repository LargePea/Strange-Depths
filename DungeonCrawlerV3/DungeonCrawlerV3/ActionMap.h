#pragma once

#include <stack>
#include <map>
#include "Image.h"
#include "Screen.h"

class ActionMap {

private:
	static std::stack<ActionMap*> _actionMapStack;

	Image _actionMenu;

public:
	ActionMap(Image actionMenu);

	static inline ActionMap& GetCurrentMap() { return *_actionMapStack.top(); }

	static void PopCurrentMap();

	static void AddActionMap(ActionMap* newMap);

	void virtual InputAction(const char) = 0;

	void virtual OnActivate() {}

	void RemoveMapImage() { Screen::RemoveImages({ &_actionMenu }); }

	inline void AddMapImage() { Screen::AddImages({ &_actionMenu }); }
};
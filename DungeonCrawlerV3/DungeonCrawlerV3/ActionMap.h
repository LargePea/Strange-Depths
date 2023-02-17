#pragma once

#include <stack>
#include <map>

class ActionMap {

private:
	static std::stack<ActionMap*> _actionMapStack;

public:
	ActionMap() = default;

	static ActionMap& GetCurrentMap();

	static void PopCurrentMap();

	static void AddActionMap(ActionMap* newMap);

	void virtual InputAction(const char) = 0;
};
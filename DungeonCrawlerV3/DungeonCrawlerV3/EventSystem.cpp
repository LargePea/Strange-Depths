#include "EventSystem.h"

EventSystem EventSystem::operator+=(func lhs) {
	_functionCallList.insert(lhs);
	return *this;
}

EventSystem EventSystem::operator-=(func lhs) {
	std::multiset<func>::iterator foundItem = _functionCallList.find(lhs);
	if (foundItem != _functionCallList.end()) _functionCallList.erase(foundItem);
	return *this;
}
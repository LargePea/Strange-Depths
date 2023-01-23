#pragma once
#include <set>


template<typename T>
class EventSystemGeneric
{
public:


private:

};

class EventSystem
{
	using func = void(*)();
private:
	std::multiset<func>_functionCallList;

public:
	EventSystem operator+=(func rhs);
	EventSystem operator-=(func rhs);

	inline void Invoke() {
		for (auto function : _functionCallList) function();
	}
};
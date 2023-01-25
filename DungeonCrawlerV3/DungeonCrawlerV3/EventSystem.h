#pragma once
#include <list>

template<typename... Args>
class IEvent {
public:
	inline virtual void Invoke(Args... args) = 0;
};

template<typename T, typename... Args>
class Event : public IEvent<Args...> {
using functionType = void (T::*)(Args...);

private:
	std::pair<T*, functionType> _event;

public:
	Event(T* object, functionType functionPointer) : IEvent<Args...>() {
		_event.first = object;
		_event.second = functionPointer;
	}
	
	inline void Invoke(Args... args) override { (_event.first->*_event.second)(args...); }
};

//Event handler
template<typename... Args>
class Subject {
private:
	std::list<IEvent<Args...>*> events;

public:
	inline void Attach(IEvent<Args...>* event) { events.push_back(event); }

	inline void Remove(IEvent<Args...>* event) { events.remove(event); }

	inline void Invoke(Args... args) { for (IEvent<Args...>* &event : events) event->Invoke(args...); }

	inline int ObserverCount() { return events.size(); }
};
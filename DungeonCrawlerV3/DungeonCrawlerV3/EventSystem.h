#pragma once
#include <set>

template<typename... Args>
class IEvent {
public:
	IEvent() = default;

	virtual ~IEvent() = default;

	inline virtual void Invoke(Args... args) = 0;

	inline virtual void Delete() = 0;
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
	
	~Event() override = default;

	//assumes pointer points to a valid object
	inline void Invoke(Args... args) override { (_event.first->*_event.second)(args...); }

	inline void Delete() override { delete _event.first; }
};

//Event handler
template<typename... Args>
class Subject {
private:
	std::set<IEvent<Args...>*> events;
	std::set< IEvent<Args...>*> eventsToRemove;
public:
	Subject() = default;

	~Subject() = default;

	inline void Attach(IEvent<Args...>* event) { events.insert(events.end(), event); }

	inline void Remove(IEvent<Args...>* event) { eventsToRemove.insert(eventsToRemove.end(), event); }


	void Invoke(Args... args) { 
		for (IEvent<Args...>* event : events) event->Invoke(args...);

		if (eventsToRemove.size() == 0) return;

		for (IEvent<Args...>* event : eventsToRemove) {
			events.erase(events.find(event));
			event->Delete();
		}
		eventsToRemove.clear();
	}

	inline int ObserverCount() { return events.size(); }
};
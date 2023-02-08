#pragma once
#include <set>

template<typename... Args> class Subject;

template<typename... Args>
class IEvent {
public:
	IEvent() = default;

	virtual ~IEvent() = default;

	inline virtual void Invoke(Args... args) = 0;
};

template<typename T, typename... Args>
class Event : public IEvent<Args...> {
using functionType = void (T::*)(Args...);

friend class Subject<Args...>;

private:
	std::pair<T*, functionType> _event;
	bool _deleteObject;
	Event(T* object, functionType functionPointer, bool deleteObject) : 
		IEvent<Args...>(), _event(object, functionPointer), _deleteObject(deleteObject) {
	}

public:
	
	virtual ~Event() {
		if (_deleteObject)
			delete _event.first;
	}

	//assumes pointer points to a valid object
	inline void Invoke(Args... args) override { (_event.first->*_event.second)(args...); }
};

//Event handler
template<typename... Args>
class Subject {
private:
	std::set<IEvent<Args...>*> events;
	std::set< IEvent<Args...>*> eventsToRemove;
public:
	Subject() = default;

	~Subject() {
		for (auto& event : events)
			delete event;
	}

	template<typename T> 
	Event<T>* Attach(T* object, void (T::* function)(Args...), bool deleteObject) {
		Event<T>* event = new Event<T>(object, function, deleteObject);
		events.insert(events.end(), event);
		return event;
	}

	inline void Remove(IEvent<Args...>* event) { eventsToRemove.insert(eventsToRemove.end(), event); }


	void Invoke(Args... args) { 
		for (IEvent<Args...>* event : events) event->Invoke(args...);

		if (eventsToRemove.size() == 0) return;

		for (IEvent<Args...>* event : eventsToRemove) {
			auto foundEvent = events.find(event);
			//check to see if event was already removed
			if (foundEvent != events.end())
				delete event;
				events.erase(foundEvent);
		}
		eventsToRemove.clear();
	}

	inline int EventCount() { return events.size(); }
};
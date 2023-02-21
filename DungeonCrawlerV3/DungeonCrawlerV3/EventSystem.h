#pragma once
#include <set>
#include <mutex>

template<typename... Args> class Subject;
template<typename... Args> class IEvent;
template<typename T, typename... Args> class Event;
template<typename... Args> class StaticEvent;

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

private:
	Event(T* object, functionType functionPointer, bool deleteObject) :
		IEvent<Args...>(), _event(object, functionPointer), _deleteObject(deleteObject){}

	virtual ~Event() {
		if (_deleteObject)
			delete _event.first;
	}

public:
	//assumes pointer points to a valid object
	inline void Invoke(Args... args) override { (_event.first->*_event.second)(args...); }
};

template<typename... Args>
class StaticEvent : public IEvent<Args...> {
using functionType = void (*)(Args...);

friend class Subject<Args...>;

private:
	functionType _event;

private:
	StaticEvent(functionType event) : _event(event){}

	virtual ~StaticEvent() = default;

public:
	inline void Invoke(Args... args) override { (*_event)(args...); }
};

//Event handler
template<typename... Args>
class Subject {
private:
	std::set<IEvent<Args...>*> events;
	std::mutex eventsMutex;

public:
	Subject() = default;

	~Subject() {
		for (auto& event : events)
			delete event;
	}

	template<typename T> 
	IEvent<Args...>* Attach(T* object, void (T::* function)(Args...), bool deleteObject = false) {
		IEvent<Args...>* event = new Event<T, Args...>(object, function, deleteObject);
		events.insert(events.end(), event);
		return event;
	}

	IEvent<Args...>* Attach(void (* function)(Args...)) {
		IEvent<Args...>* event = new StaticEvent<Args...>(function);
		events.insert(events.end(), event);
		return event;
	}

	void Remove(IEvent<Args...>* event) { events.erase(event); }


	void Invoke(Args... args) { 
		std::lock_guard<std::mutex> lock(eventsMutex);
		for (IEvent<Args...>* event : events) event->Invoke(args...);

	}

	inline int EventCount() { return events.size(); }
};
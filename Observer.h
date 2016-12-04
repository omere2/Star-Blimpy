#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#define NO_OBSERVABLE (0)

#include <vector>

class Observable;

class Observer
{
// Public Methods	//
public:
	enum observer_types;

	// Constructor: create an observer observing an observable object, hehe...	//
	Observer(observer_types type = OBSERVE_ALL);

	// Destructor: remove self as an observer of the observable object	//
	virtual ~Observer();

	// AddObservable: add an observable to the object	//
	void AddObservable(Observable &observable);
	
	// RemoveObservable: remove an observable from the object	//
	void RemoveObservable(Observable &observable);

	// Update: called by the object being observed to indicate a change that requires observing	//
	virtual void ObserverUpdate(Observable& observable) = 0;

	enum observer_types
	{
		OBSERVE_ALL = 0,
		OBSERVE_HEALTH = 1,
		OBSERVE_POSITION = 2,
		OBSERVE_WEAPONS = 3
	};

	observer_types GetType();

// Protected members	//
protected:
	std::vector<Observable*>	m_observables;				// objects being observed									//
	Observable*					m_optimized_observable;		// single object being observed, for optimization purposes	//
	observer_types m_type;						// What does this observer look for	//
};


#endif
#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <vector>
#include "Observer.h"

class Observer;

class Observable
{
public:
	// Default Constructor	//
	Observable();

	// Default Destructor: notify all observers to stop observing	//
	virtual ~Observable();

	// AddObserver: add an observer to the object	//
	void AddObserver(Observer &observer);
	
	// RemoveObserver: remove an observer from the object	//
	void RemoveObserver(Observer &observer);

	// UpdateObservers(): update the observers that a change was made	//
	void UpdateObservers(Observer::observer_types type = Observer::OBSERVE_ALL);

// Protected members	//
protected:
	std::vector<Observer*> m_observers;
};


#endif
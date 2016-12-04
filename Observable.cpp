#include "Observable.h"
#include "observer.h"
#include "baseexception.h"

Observable::Observable():
	m_observers()
{
}


Observable::~Observable()
{
	// Remove all observers	//
	std::vector<Observer*>::iterator i;
	for (i = m_observers.begin(); i < m_observers.end(); i++)
	{
		// Notify the observer to stop peeking at other windows...	//
		(*i)->RemoveObservable(*this);
	}
}


void Observable::AddObserver(Observer& observer_to_add)
{
	std::vector<Observer*>::iterator i;
	for (i = m_observers.begin(); i < m_observers.end(); i++)
	{
		Observer* observer = *i;
		if (observer == &observer_to_add)
		{
			throw BaseException("AddObserver failed: observer is already in the list");
		}
	}

	m_observers.push_back(&observer_to_add);
}


void Observable::RemoveObserver(Observer& observer_to_remove)
{
	std::vector<Observer*>::iterator i;
	for (i = m_observers.begin(); i < m_observers.end(); i++)
	{
		Observer* observer = *i;
		if (observer == &observer_to_remove)
		{
			// Remove the observer from the list of observers	//
			m_observers.erase(i);
		}
	}
}


void Observable::UpdateObservers(Observer::observer_types type)
{
	// Update all the observers observing the object	//
	std::vector<Observer*>::iterator i;
	for (i = m_observers.begin(); i < m_observers.end(); i++)
	{
		if ((type == Observer::OBSERVE_ALL) ||
			((*i)->GetType() == Observer::OBSERVE_ALL) ||
			((*i)->GetType() == type))
		{
			(*i)->ObserverUpdate(*this);
		}
	}
}
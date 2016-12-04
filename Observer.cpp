#include "Observer.h"
#include "observable.h"
#include "BaseException.h"


Observer::Observer(observer_types type):
m_observables(),
m_type(type)
{
}


Observer::~Observer()
{
	// Notify all observed objects, that this one stopped observing...	//
	std::vector<Observable*>::iterator i;
	for (i = m_observables.begin(); i < m_observables.end(); i++)
	{
		(*i)->RemoveObserver(*this);
	}
}



void Observer::AddObservable(Observable& observable_to_add)
{
	std::vector<Observable*>::iterator i;
	for (i = m_observables.begin(); i < m_observables.end(); i++)
	{
		Observable* observable = *i;
		if (observable == &observable_to_add)
		{
			throw BaseException("AddObservable failed: observable is already in the list");
		}
	}

	m_observables.push_back(&observable_to_add);
	
	// if there is only one observed object, use the optimized member	//
	if (m_observables.size() == 1)
	{
		m_optimized_observable = &observable_to_add;
	}
	else
	{
		m_optimized_observable = NULL;
	}

	return;
}



void Observer::RemoveObservable(Observable& observable_to_remove)
{
	std::vector<Observable*>::iterator i;
	for (i = m_observables.begin(); i < m_observables.end(); i++)
	{
		Observable* observable = *i;
		if (observable == &observable_to_remove)
		{
			// Remove the observer from the list of observers	//
			m_observables.erase(i);
		}
	}

	// if there is only one observed object, use the optimized member	//
	if (m_observables.size() == 1)
	{
		m_optimized_observable = *(m_observables.begin());
	}
	else
	{
		m_optimized_observable = NULL;
	}

	return;
}




Observer::observer_types Observer::GetType()
{
	return m_type;
}

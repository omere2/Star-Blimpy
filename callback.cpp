#include "callback.h"

using namespace std;


Callback Callback::m_instance;

Callback::Callback()
{
}

Callback::~Callback()
{
}

Callback* Callback::GetInstance()
{
	return &m_instance;
}

void Callback::AddFunction(BaseCallable* f, unsigned int ms_time)
{
	pair<BaseCallable*, unsigned int> x;
	x.first = f;
	x.second = GetTickCount() + ms_time;
	m_callback_vector.push_back(x);
}

void Callback::CheckForCallback()
{
	unsigned int current_time = GetTickCount();
	list<pair<BaseCallable*,unsigned int> > :: iterator i;

	i = m_callback_vector.begin();
	while (i != m_callback_vector.end())
	{
		// time passed
		if ((*i).second < current_time)
		{
			// call callback
			(*((*i).first))(); 
			
			delete (*i).first; // free callable
			i = m_callback_vector.erase(i);
		}
		else
		{	
			++i;
		}

		
	}
}

void Callback::RemoveObject(void* object)
{
	unsigned int current_time = GetTickCount();
	list<pair<BaseCallable*,unsigned int> > :: iterator i;

	i = m_callback_vector.begin();
	while (i != m_callback_vector.end())
	{
		if (((*i).first)->getObjectPtr() == object)
		{
			delete (*i).first; // free callable
			i = m_callback_vector.erase(i);
		}
		else
		{	
			++i;
		}
		
	}
}


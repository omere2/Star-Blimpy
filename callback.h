#ifndef __CALLBACK_H__
#define __CALLBACK_H__

#include "common.h"
#include <list>

class BaseCallable
{
public:
	virtual void operator () (void) = 0;
	virtual void* getObjectPtr() = 0;
};

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

//typedef void (Missile::*bla)();
template <class T>
class Callable : public BaseCallable
{
public:
	Callable(T* c, void (T::*f)()) { m_c = c; m_f = f; }
	~Callable() {}

	void operator () (void) { CALL_MEMBER_FN(*m_c, m_f)(); }
	void* getObjectPtr() { return (void*)m_c; }
	
private:
	T* m_c;
	void (T::*m_f)();
};


class Callback
{
public:
	~Callback();
	static Callback* GetInstance();

	void AddFunction(BaseCallable*, unsigned int ms_time);
	void RemoveObject(void* object);

	void CheckForCallback();
private:
	Callback();

	static Callback m_instance;
	
	std::list<std::pair<BaseCallable*, unsigned int> > m_callback_vector;
};


#endif
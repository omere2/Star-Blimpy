#ifndef __DEATHEXCEPTION_H__
#define __DEATHEXCEPTION_H__

#include "GameException.h"

class DeathException : public GameException
{
public:
	DeathException();
	virtual ~DeathException();
};

#endif

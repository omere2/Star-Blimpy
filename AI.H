#ifndef __AI_H__
#define __AI_H__

#include "DynamicEntity.h"

class AI
{
public:
	AI();
	virtual ~AI();
	virtual void UpdateEntity(DynamicEntity *, scalar time_delta);
};


#endif

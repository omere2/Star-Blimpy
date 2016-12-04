#ifndef __SHIPKEYBOARDAI_H__
#define __SHIPKEYBOARDAI_H__

#include "KeyboardAI.h"
#include "Ship.h"

class ShipKeyboardAI : public KeyboardAI
{
public:
	ShipKeyboardAI(const game_keys keys);
	virtual ~ShipKeyboardAI();
	virtual void UpdateEntity(DynamicEntity *, scalar time_delta);
private:
};

#endif
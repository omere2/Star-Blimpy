#ifndef __KEYBOARDAI_H__
#define __KEYBOARDAI_H__

#include "allegro.h"
#include "AI.h"
#include "keys.h"

class KeyboardAI : public AI
{
public:
	KeyboardAI(const game_keys keys);
	virtual ~KeyboardAI();
	virtual void UpdateEntity(DynamicEntity *, scalar time_delta);
protected:
	game_keys m_keys;
};


#endif
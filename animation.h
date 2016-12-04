#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "drawable.h"
#include "BasicAnimation.h"

class Animation: public Drawable, public BasicAnimation
{
public:
	Animation(DWORD sequence_delay = 0, unsigned long cycle_image = 0);
	Animation(const Animation&); // copy constructor
	void operator=(const Animation&); // assignment operator
	virtual ~Animation();


	void Draw(BITMAP* dest, int x, int y, fixed alpha = 0);
	void Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha = 0);
private:
	DWORD m_total_time;
};

#endif
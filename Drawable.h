#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "common.h"

class Drawable
{
public:
	Drawable(): m_is_rotatable(true) {};
	
	
	// Draw in absolute location
	virtual void Draw(BITMAP* dest) { };

	// Draw in position x,y in angle alpha
	virtual void Draw(BITMAP* dest, int x, int y, fixed alpha) = 0;

	// Draw in position x,y according to pivot cx,cy in angle alpha
	virtual void Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha) = 0;

	bool isRotatable() const { return m_is_rotatable; };
	void setRotatble(bool rotatable) { m_is_rotatable = rotatable; };

private:
	bool m_is_rotatable;

};

#endif
#ifndef __CIRCLEAI_H__
#define __CIRCLEAI_H__

#include "AI.h"

const unsigned char DEFAULT_ROTATE_SPEED = 2;
const bool ROTATE_CLOCKWISE = true;
const bool ROTATE_COUNTER_CLOCKWISE = false;

class CircleAI : public AI
{
public:
	// Basic Constructor: create a CircleAI circling the specified target in the specified radius	//
	CircleAI(Entity& target, scalar radius, fixed alpha = 0, 
			 unsigned char rotate_speed = DEFAULT_ROTATE_SPEED, bool clockwise = ROTATE_CLOCKWISE);

	// Basic destructor	//
	virtual ~CircleAI();

	// Update the entity's course	//
	virtual void UpdateEntity(DynamicEntity *, scalar time_delta);
private:
	Entity&			m_target;		// Entity to patrol							//
	scalar			m_radius;		// Range from the entity					//
	fixed			m_alpha;		// Angle from the entity					//
	unsigned char	m_rotate_speed;	// Rotation speed							//
	bool			m_clockwise;	// rotate clockwise or counter clockwise	//
};



#endif
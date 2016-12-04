#include "CircleAI.h"
#include <assert.h>


CircleAI::CircleAI(Entity& target, scalar radius, fixed alpha, 
				   unsigned char rotate_speed, bool clockwise):
m_target(target),
m_radius(radius),
m_alpha(alpha),
m_rotate_speed(rotate_speed),
m_clockwise(clockwise)
{
}


CircleAI::~CircleAI()
{
}


void CircleAI::UpdateEntity(DynamicEntity *entity, scalar time_delta)
{
	// assertion	//
	assert(entity != NULL);

	// update alpha	//
	if (m_clockwise)
	{
		m_alpha += m_rotate_speed*(DWORD)time_delta<<12;
	}
	else
	{
		m_alpha -= m_rotate_speed*(DWORD)time_delta<<12;
	}

	// update position	//
	vector_2D position( m_target.getX() + fixtof(fixcos(m_alpha)) * m_radius,
						m_target.getY() + fixtof(fixsin(m_alpha)) * m_radius);
	entity->setPosition(position);

	return;
}
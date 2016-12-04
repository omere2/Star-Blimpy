
#include "Explosion.h"

Explosion::Explosion(CompositeAnimation& anim,	// Entity's Composite Animation	//
					  scalar	mass,			// Mass of the entity			//
					  scalar	radius,			// Radius of the entity			//
					  DWORD	ttl,				// Entity's Time to live		//
					  fixed	alpha,				// Angle of the entity			//
					  vector_2D position,		// Position of the entity		//
					  vector_2D velocity		// Starting velocity of the entity	//
					 ):
DynamicEntity(anim, mass, radius, INFINITE_HEALTH, ttl, alpha, position, velocity)
{
	m_collision_type = ENTITY_TRANSPARENT;
}


Explosion::~Explosion()
{
}

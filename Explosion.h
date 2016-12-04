#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "DynamicEntity.h"

class Explosion : public DynamicEntity
{
public:
	// Basic constructor	//
	Explosion(CompositeAnimation& anim,	// Entity's Composite Animation	//
			  scalar	mass,			// Mass of the entity			//
			  scalar	radius,			// Radius of the entity			//
			  DWORD		ttl,			// Entity's Time to live		//
			  fixed		alpha,			// Angle of the entity			//
			  vector_2D position,		// Position of the entity		//
			  vector_2D velocity	= vector_2D()	// Starting velocity of the entity		//
		);

	// Basic destructor		//
	virtual ~Explosion();
};


#endif
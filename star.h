#ifndef __STAR_H__
#define __STAR_H__

#include "entity.h"

class Star : public Entity
{
public:
	Star(CompositeAnimation& anim,	// Entity's Composite Animation	//
		 scalar mass,				// Mass of the entity			//
		 scalar radius,				// Radius of the entity			//
		 DWORD ttl,					// Entity's Time to live		//
		 fixed alpha,				// Angle of the entity			//
		 vector_2D position);		// Position of the entity		//
	virtual ~Star();
};

#endif
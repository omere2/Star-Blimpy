#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "Shot.h"

const DWORD INFINITE_FUEL			= -1;
const DWORD MISSILE_DEFAULT_DAMAGE	= 500;

class Missile : public Shot
{
// Public methods	//
public:
	// basic constructor	//
	Missile(CompositeAnimation& anim,		// Entity's Composite Animation	//
			scalar	mass,					// Mass of the entity			//
			scalar	radius,					// Radius of the entity			//
			long	health,					// Health of the entity			//
			DWORD	ttl,					// Entity's Time to live		//
			fixed	alpha,					// Angle of the entity			//
			vector_2D position,				// Position of the entity		//
			// New Dynamic Entity data:		//
			vector_2D velocity		= vector_2D(),		// Starting velocity of the entity		//
			Engine& engine			= Engine(),			// Engine of the entity					//
			// New Missile data:	//
			DWORD fuel_time		= INFINITE_FUEL,			// Time of acceleration of the missile	//
			DWORD damage		= MISSILE_DEFAULT_DAMAGE	// Damage of the missile	//
		);
	
	// basic destructor	//
	virtual ~Missile();

	virtual void Die(void);
	virtual void NoFuel(void);
};

#endif
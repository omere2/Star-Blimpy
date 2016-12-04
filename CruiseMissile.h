#ifndef __CRUISE_MISSILE_H__
#define __CRUISE_MISSILE_H__


#include "AdvDynamicEntity.h"
#include "ShotInterface.h"
#include "KeyboardAI.h"
#include "Missile.h"	// for constants	//


class CruiseMissile : public AdvDynamicEntity, public ShotInterface
{
// Public methods	//
public:
	// basic constructor	//
	CruiseMissile(CompositeAnimation& anim,		// Entity's Composite Animation	//
				scalar	mass,					// Mass of the entity			//
				scalar	radius,					// Radius of the entity			//
				long	health,					// Health of the entity			//
				DWORD	ttl,					// Entity's Time to live		//
				fixed	alpha,					// Angle of the entity			//
				vector_2D position,				// Position of the entity		//
				// New Dynamic Entity data:		//
				vector_2D velocity	= vector_2D(),		// Starting velocity of the entity		//
				Engine& engine		= Engine(),			// Engine of the entity					//
				// New CruiseMissile data:	//
				AI&		ai			= AI(),						// AI controling the missile			//
				DWORD	fuel_time	= INFINITE_FUEL,			// Time of acceleration of the missile	//
				DWORD	damage		= MISSILE_DEFAULT_DAMAGE	// Damage of the missile	//
		);
	
	// basic destructor	//
	virtual ~CruiseMissile();

	// Collide: method called when there's a collision with another entity	//
	virtual void Collide(Entity&);
	
	virtual void Die(void);
	virtual void NoFuel(void);

	virtual DWORD GetDamage();
};


#endif
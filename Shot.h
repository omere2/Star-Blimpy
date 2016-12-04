#ifndef __SHOT_H__
#define __SHOT_H__

#include "DynamicEntity.h"
#include "ShotInterface.h"

// Constant variables	//
extern const scalar SHOT_DEFAULT_VELOCITY;
extern const long	SHOT_DEFAULT_TTL;
extern const scalar SHOT_DEFAULT_DAMAGE;


class Shot : public DynamicEntity, public ShotInterface
{
// Public methods	//
public:
	Shot(CompositeAnimation& anim,	// Entity's Composite Animation	//
		 scalar	mass,				// Mass of the entity			//
		 scalar	radius,				// Radius of the entity			//
		 DWORD	ttl,				// Entity's Time to live		//
		 fixed	alpha,				// Angle of the entity			//
		 vector_2D position,		// Position of the entity		//

		 // New Dynamic Entity data://
		 vector_2D velocity	= vector_2D(),	// Starting velocity of the entity		//

		 // New Shot data:	//
		 DWORD damage = SHOT_DEFAULT_DAMAGE	// Damage of the shot					//
		);

	// Basic destructor: destroy a shot	//
	~Shot();

	// Collide: method called when there's a collision with another entity	//
	virtual void Collide(Entity&);

	// Die: Called when ttl expired, Deregister self from engine	//
	virtual void Die(void);

	virtual DWORD GetDamage();

// Public members	//
public:

};


#endif
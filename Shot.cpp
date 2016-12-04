#include "Shot.h"
#include "GameEngine.h"
#include "EntityFactory.h"

// Constant variables	//
extern const scalar SHOT_DEFAULT_VELOCITY = 0;
extern const long SHOT_DEFAULT_TTL = 1000;
extern const scalar SHOT_DEFAULT_DAMAGE = 100;


Shot::Shot(CompositeAnimation& anim,	// Entity's Composite Animation	//
		   scalar	mass,		// Mass of the entity			//
		   scalar	radius,		// Radius of the entity			//
		   DWORD	ttl,		// Entity's Time to live		//
		   fixed	alpha,		// Angle of the entity			//
		   vector_2D position,	// Position of the entity		//
		   vector_2D velocity,	// Starting velocity of the entity		//
		   DWORD damage			// Damage of the shot					//
		 ):
	DynamicEntity(anim, mass, radius, INFINITE_HEALTH, ttl, 
				  alpha, position, velocity),
	ShotInterface(damage)
{
	setEngineFriction(ENGINE_NO_FRICTION);
}

Shot::~Shot()
{
}


void Shot::Collide(Entity& target)
{
	ShotInterface::Collide(target);
	Die();
}


void Shot::Die()
{
	// Parent Die()	//
	DynamicEntity::Die();
}


DWORD Shot::GetDamage()
{
	return m_damage;
}

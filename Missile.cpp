#include "Missile.h"
#include "Explosion.h"
#include "EntityFactory.h"
#include "GameEngine.h"

Missile::Missile(CompositeAnimation& anim,	// Entity's Composite Animation			//
			scalar	mass,					// Mass of the entity					//
			scalar	radius,					// Radius of the entity					//
			long	health,					// Health of the entity					//
			DWORD	ttl,					// Entity's Time to live				//
			fixed	alpha,					// Angle of the entity					//
			vector_2D position,				// Position of the entity				//
			vector_2D velocity,				// Starting velocity of the entity		//
			Engine& engine,					// Engine of the entity					//
			DWORD fuel_time,				// Time of acceleration of the missile	//
			DWORD damage					// Damage of the missile				//
		):
Shot(anim, mass, radius, ttl, alpha, position, velocity, damage)
{	
	// Set the missile health	//
	setHealth(health);

	// Set the missile engine	//
	setEngine(engine);

	// Set the missile starting acceleration to the engine acceleration	// 
	SetAcceleration(getEngineAcceleration());

	// Create a callback to stop the missile acceleration when the fuel runs out	//
	if (fuel_time != INFINITE_FUEL)
	{
		Callback::GetInstance()->AddFunction(new Callable<Missile>(this, &Missile::NoFuel), fuel_time);
	}
}


Missile::~Missile()
{
}


void Missile::Die()
{
	// Create Explosion...	//
	Entity* explosion;
	explosion = &EntityFactory::GetInstance()->CreateEntity(EntityFactory::E_EXPLOSION, m_position, m_alpha, m_velocity);
	GameEngine::GetInstance()->RegisterEntity(*explosion);

	// Parent Die()	//
	DynamicEntity::Die();
}


void Missile::NoFuel()
{
	SetAcceleration(0);
}

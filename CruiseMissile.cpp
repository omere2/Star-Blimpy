
#include "CruiseMissile.h"
#include "Explosion.h"
#include "EntityFactory.h"
#include "GameEngine.h"

CruiseMissile::CruiseMissile(CompositeAnimation& anim,	// Entity's Composite Animation			//
							scalar	mass,					// Mass of the entity					//
							scalar	radius,					// Radius of the entity					//
							long	health,					// Health of the entity					//
							DWORD	ttl,					// Entity's Time to live				//
							fixed	alpha,					// Angle of the entity					//
							vector_2D position,				// Position of the entity				//
							vector_2D velocity,				// Starting velocity of the entity		//
							Engine& engine,					// Engine of the entity					//
							AI&		ai,						// AI controling the missile			//
							DWORD	fuel_time,				// Time of acceleration of the missile	//
							DWORD	damage					// Damage of the missile				//
						):
AdvDynamicEntity(anim, mass, radius, health, ttl, 
				  alpha, position, velocity),
ShotInterface(damage)
{	
	// Set the AI	//
	changeAI(&ai);

	// Set the missile engine	//
	setEngine(engine);

	// Set the missile starting acceleration to the engine acceleration	// 
	SetAcceleration(getEngineAcceleration());

	// Create a callback to stop the missile acceleration when the fuel runs out	//
	if (fuel_time != INFINITE_FUEL)
	{
		Callback::GetInstance()->AddFunction(new Callable<CruiseMissile>(this, &CruiseMissile::NoFuel), fuel_time);
	}
}


CruiseMissile::~CruiseMissile()
{
}

void CruiseMissile::Collide(Entity& target)
{
	ShotInterface::Collide(target);
	Die();
}


void CruiseMissile::Die()
{
	// Create Explosion...	//
	Entity* explosion;
	explosion = &EntityFactory::GetInstance()->CreateEntity(EntityFactory::E_EXPLOSION, m_position, m_alpha, m_velocity);
	GameEngine::GetInstance()->RegisterEntity(*explosion);

	// Parent Die()	//
	AdvDynamicEntity::Die();
}


void CruiseMissile::NoFuel()
{
	// stop accelerating, and disable AI control...	//
	SetAcceleration(0);
	changeAI(new AI());
}


DWORD CruiseMissile::GetDamage()
{
	return m_damage;
}

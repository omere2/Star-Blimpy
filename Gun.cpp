#include "Gun.h"
#include "GameEngine.h"
#include "EntityFactory.h"
#include "AnimationFactory.h"

Gun::Gun(Entity* host_entity, scalar reload_time, scalar shot_velocity, long shot_ttl):
	Weapon(host_entity, reload_time),
	m_shot_velocity(shot_velocity),
	m_shot_ttl(shot_ttl)
{
	// Create basic animation	//
	m_BasicAnimation.AddAnimation(AnimationFactory("Shot"), 0, 0);
	m_InventoryAnimation.AddAnimation(AnimationFactory("Shot"), 11, 11);
}

Gun::~Gun()
{
}

bool Gun::Fire(vector_2D velocity)
{
	// Start the Fire procedure from the base	//
	if (Weapon::Fire(velocity))
	{
		// Calculate positions of the new shot	//
		fixed alpha = m_HostEntity->getAlpha();

		// Create a new missile
		Entity* shot = EntityFactory::GetInstance()->CreateShot(vector_2D(), alpha, velocity, m_shot_ttl, m_shot_velocity);

		// Get the radius of the missile	//
		scalar shot_radius = shot->getRadius();
		scalar host_radius = m_HostEntity->getRadius();
		scalar radius = host_radius + shot_radius + 2;

		// Set the missile starting position to avoid collision	with host	//
		vector_2D position(	m_HostEntity->getX() + fixtof(fixcos(alpha)) * radius,
							m_HostEntity->getY() + fixtof(fixsin(alpha)) * radius);

		shot->setPosition(position);

		// And register it in the GameEngine	//
		GameEngine::GetInstance()->RegisterEntity(*shot);

		// Return true, 
		return true;
	}
	else
	{
		// Basic Fire() didn't fire, so we won't either	//
		return false;
	}
}
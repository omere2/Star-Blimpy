#include "MissileLauncher.h"
#include "EntityFactory.h"
#include "AnimationFactory.h"
#include "GameEngine.h"

MissileLauncher::MissileLauncher(Entity* host_entity, scalar reload_time, MISSILE_TYPE type):
	Weapon(host_entity, reload_time),
	m_type(type)
{
	// Create basic animation	//
	switch (m_type)
	{
	case MISSILE_NORMAL:
		m_BasicAnimation.AddAnimation(AnimationFactory("Missile"), 0, 0);
		m_InventoryAnimation.AddAnimation(AnimationFactory("Missile"), 0, 0);
		break;
	case MISSILE_CRUISE:
		m_BasicAnimation.AddAnimation(AnimationFactory("CMissile"), 0, 0);
		m_InventoryAnimation.AddAnimation(AnimationFactory("CMissile"), 0, 0);
		break;
	case MISSILE_HOMING:
		m_BasicAnimation.AddAnimation(AnimationFactory("HMissile"), 0, 0);
		m_InventoryAnimation.AddAnimation(AnimationFactory("HMissile"), 0, 0);
		break;
	}
}

MissileLauncher::~MissileLauncher()
{
}


bool MissileLauncher::Fire(vector_2D velocity)
{
	// Start the Fire procedure from the base	//
	if (Weapon::Fire(velocity))
	{
		// Create a new missile
		Entity* missile = CreateMissile(m_HostEntity->getPosition(), m_HostEntity->getRadius(), m_HostEntity->getAlpha(), velocity);
			
		// And register it in the GameEngine	//
		GameEngine::GetInstance()->RegisterEntity(*missile);

		// Return true, 
		return true;
	}
	else
	{
		// Basic Fire() didn't fire, so we won't either	//
		return false;
	}
}



Entity* MissileLauncher::CreateMissile(vector_2D launcher_position, scalar launcher_radius, fixed alpha, vector_2D velocity)
{
	Entity* missile = NULL;
	switch (m_type)
	{
	case MISSILE_CRUISE:
		missile = CreateCruiseMissile(alpha, velocity);
		break;
	case MISSILE_HOMING:
		missile = CreateHomingMissile(alpha, velocity);
		break;
	case MISSILE_NORMAL:
	default:
		missile = CreateNormalMissile(alpha, velocity);
		break;
	}

	if (missile == NULL)
	{
		throw BaseException("CreateMissile failed");
	}

	// Get the radius of the missile	//
	scalar missile_radius = missile->getRadius();
	scalar radius = launcher_radius + missile_radius + 2;

	// Set the missile starting position to avoid collision	with host	//
	vector_2D position(	launcher_position.x + fixtof(fixcos(alpha)) * radius,
						launcher_position.y + fixtof(fixsin(alpha)) * radius);

	missile->setPosition(position);

	return missile;
}

Entity* MissileLauncher::CreateNormalMissile(fixed alpha, vector_2D velocity)
{
	// Load Animations	//
	Animation& FireAnimation = AnimationFactory("fire");
	Animation& MissileAnimation = AnimationFactory("Missile");

	// Create CompositeAnimation	//
	CompositeAnimation* MissileCAnimation = new CompositeAnimation(16,16);

	// And add animations to it	//
	MissileCAnimation->AddAnimation(MissileAnimation, 2, 2 );
	int flame_handle = MissileCAnimation->AddAnimation(FireAnimation, 0, 12);

	Engine missile_engine;
	missile_engine.setEngineAcceleration(0.0015);
	missile_engine.setEngineAccelerationHandle(flame_handle);
	missile_engine.setEngineFriction(0.9995);
	return new Missile(*MissileCAnimation, 100, 18, 3000, 4000, alpha, vector_2D(), velocity, missile_engine, 400);
}

Entity* MissileLauncher::CreateCruiseMissile(fixed alpha, vector_2D velocity)
{
	// Load Animations	//
	Animation& FireAnimation = AnimationFactory("fire");
	Animation& MissileAnimation = AnimationFactory("CMissile");

	// Create CompositeAnimation	//
	CompositeAnimation* MissileCAnimation = new CompositeAnimation(16,16);

	// And add animations to it	//
	MissileCAnimation->AddAnimation(MissileAnimation, 2, 2 );
	int flame_handle = MissileCAnimation->AddAnimation(FireAnimation, 0, 12);

	Engine missile_engine;
	missile_engine.setEngineAcceleration(0.0006);
	missile_engine.setEngineAccelerationHandle(flame_handle);
	missile_engine.setEngineFriction(0.9995);
	AI* missile_ai = new KeyboardAI(game_keys(0, KEY_LEFT, KEY_RIGHT));

	return new CruiseMissile(*MissileCAnimation, 100, 18, 3000, 4000, alpha, vector_2D(), velocity, missile_engine, *missile_ai, 3000);
}


Entity* MissileLauncher::CreateHomingMissile(fixed alpha, vector_2D velocity)
{
	return NULL;
}



#include <math.h>
#include "DynamicEntity.h"



DynamicEntity::DynamicEntity(CompositeAnimation& anim, 
							 scalar mass, 
							 scalar radius,	
							 long health, 
							 DWORD ttl, 
							 fixed alpha,
							 vector_2D position, 
							 vector_2D velocity,
							 vector_2D acceleration, 
							 Engine& engine
		):
		Entity(anim, mass, radius, health, ttl, alpha, position),
		Engine(engine),
		m_velocity(velocity),
		m_acceleration(acceleration)
{
}

////////////////////////////////////////////////////////////////////////////////////

DynamicEntity::~DynamicEntity()
{
}


void DynamicEntity::Collide(Entity& target)
{
	// if none of the entities are transparent, recalclulate speeds	//
	if (!((getCollisionType() | target.getCollisionType()) & ENTITY_TRANSPARENT))
	{
		if (getX() < target.getX())
		{
			m_velocity.x =	-0.15;
//			m_acceleration.x = -0.13;
		}
		else
		{
			m_velocity.x =	0.15;
//			m_acceleration.x = 0.13;
		}
		
		if (getY() < target.getY())
		{
			m_velocity.y =	-0.15;
//			m_acceleration.y = -0.13;
		}
		else
		{
			m_velocity.y =	0.15;
//			m_acceleration.y = 0.13;
		}
	}
	Entity::Collide(target);
}


////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::Move(scalar time_delta)
{
	// Handle the acceleration animation	//
	DisplayAcceleration();
	
	// Do the actual moving:	//
	// Update the position according to the velocity		//
	m_position.x += m_velocity.x * time_delta + m_acceleration.x * time_delta * time_delta / 2;
	m_position.y += m_velocity.y * time_delta + m_acceleration.y * time_delta * time_delta / 2;

	// Update the velocity according to the acceleration	//
	m_velocity.x += m_acceleration.x * time_delta;
	m_velocity.y += m_acceleration.y * time_delta;

	// caclulate friction	//
	scalar friction = pow(getEngineFriction(), time_delta);
	m_velocity.x *= friction;
	m_velocity.y *= friction;

}

////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::DisplayAcceleration()
{
	// check if the entity is accelerated, and enable/disable	//
	// the acceleration animation accordingly					//
	if ((m_acceleration.x != 0) || (m_acceleration.y != 0))
	{
		EnableAnimation(getEngineAccelerationHandle());
	}
	else
	{
		DisableAnimation(getEngineAccelerationHandle());
	}
}

////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::ChangeAngle(fixed delta)
{
	m_alpha += delta;
}

////////////////////////////////////////////////////////////////////////////////////

vector_2D DynamicEntity::getAcceleration()
{
	return m_acceleration;
}

////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::SetAcceleration(scalar acceleration)
{
	m_acceleration.x = fixtof(fixcos(m_alpha)) * acceleration;
	m_acceleration.y = fixtof(fixsin(m_alpha)) * acceleration;
}

////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::SetAcceleration(vector_2D acceleration)
{
	m_acceleration = acceleration;
}

////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::SetVelocity(scalar velocity)
{
	m_velocity.x = fixtof(fixcos(m_alpha)) * velocity;
	m_velocity.y = fixtof(fixsin(m_alpha)) * velocity;
}

////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::SetVelocity(vector_2D velocity)
{
	m_velocity = velocity;
}

////////////////////////////////////////////////////////////////////////////////////

vector_2D DynamicEntity::getVelocity()
{
	return m_velocity;
}

////////////////////////////////////////////////////////////////////////////////////

scalar DynamicEntity::getAbsVelocity()
{
	scalar velocity = 0;
	velocity = sqrt((m_velocity.x*m_velocity.x) + (m_velocity.y*m_velocity.y));

	return velocity;
}

////////////////////////////////////////////////////////////////////////////////////

void DynamicEntity::setEngine(Engine &new_engine)
{
	setEngineAcceleration(new_engine.getEngineAcceleration());
	setEngineMaxSpeed(new_engine.getEngineMaxSpeed());
	setEngineRotateVelocity(new_engine.getEngineRotateVelocity());
	setEngineFriction(new_engine.getEngineFriction());
	setEngineBreaksFriction(new_engine.getEngineBreaksFriction());
	setEngineAccelerationHandle(new_engine.getEngineAccelerationHandle());
}

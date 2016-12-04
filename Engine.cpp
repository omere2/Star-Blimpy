

#include "Engine.h"


const scalar ENGINE_DEFAULT_ACCELERATION	= 0.0008;
const scalar ENGINE_DEFAULT_MAXSPEED		= INFINITE;
const scalar ENGINE_DEFAULT_ROTATE_VELOCITY	= 5;
const scalar ENGINE_DEFAULT_FRICTION		= 0.999;
const scalar ENGINE_DEFAULT_BREAKS_FRICTION	= 0.03;
const scalar ENGINE_NO_FRICTION				= 1;




Engine::Engine(scalar acceleration, 
			   scalar max_speed, 
			   UCHAR rotate_velocity,
			   scalar friction, 
			   scalar breaks_friction,
			   int acceleration_handle):
m_acceleration(acceleration),
m_maxSpeed(max_speed),
m_rotateVelocity(rotate_velocity),
m_friction(friction),
m_breaksFriction(breaks_friction),
m_acceleration_handle(acceleration_handle)
{
}

Engine::Engine(const Engine& new_engine):
m_acceleration(new_engine.getEngineAcceleration()),
m_maxSpeed(new_engine.getEngineMaxSpeed()),
m_rotateVelocity(new_engine.getEngineRotateVelocity()),
m_friction(new_engine.getEngineFriction()),
m_breaksFriction(new_engine.getEngineBreaksFriction()),
m_acceleration_handle(new_engine.getEngineAccelerationHandle())
{
}


Engine::~Engine()
{
}


void Engine::operator= (const Engine& new_engine)
{
	m_acceleration		= new_engine.getEngineAcceleration();
	m_maxSpeed			= new_engine.getEngineMaxSpeed();
	m_rotateVelocity	= new_engine.getEngineRotateVelocity();
	m_friction			= new_engine.getEngineFriction();
	m_breaksFriction	= new_engine.getEngineBreaksFriction();
	m_acceleration_handle = new_engine.getEngineAccelerationHandle();
}



scalar	Engine::getEngineAcceleration()	const					{ return m_acceleration;				}
void	Engine::setEngineAcceleration(scalar acceleration)		{ m_acceleration = acceleration;		}

scalar	Engine::getEngineMaxSpeed()	const						{ return m_maxSpeed;					}
void	Engine::setEngineMaxSpeed(scalar max_speed)				{ m_maxSpeed = max_speed;				}

scalar	Engine::getEngineBreaksFriction() const					{ return m_breaksFriction;				}
void	Engine::setEngineBreaksFriction(scalar breaks_friction)	{ m_breaksFriction = breaks_friction;	}

UCHAR	Engine::getEngineRotateVelocity() const					{ return m_rotateVelocity;				}
void	Engine::setEngineRotateVelocity(UCHAR rotate_velocity)	{ m_rotateVelocity = rotate_velocity;	}

scalar	Engine::getEngineFriction()	const						{ return m_friction;					}
void	Engine::setEngineFriction(scalar friction)				{ m_friction = friction;				}

int		Engine::getEngineAccelerationHandle()	const				{ return m_acceleration_handle;		}
void	Engine::setEngineAccelerationHandle(int acceleration_handle){ m_acceleration_handle = acceleration_handle; }


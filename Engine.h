#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "common.h"
#include "compositeanimation.h"

//////////////////////////////////////////////////////////////
//                                                          //
// Class: Engine											//
//                                                          //
// Description: contains all the members responsible of the //
// dynamic part of the entity: acceleration, friction,      //
// breaks, rotating speed, etc.                             //
//                                                          //
//////////////////////////////////////////////////////////////

extern const scalar ENGINE_DEFAULT_ACCELERATION;
extern const scalar ENGINE_DEFAULT_MAXSPEED;
extern const scalar ENGINE_DEFAULT_ROTATE_VELOCITY;
extern const scalar ENGINE_DEFAULT_FRICTION;
extern const scalar ENGINE_DEFAULT_BREAKS_FRICTION;
extern const scalar ENGINE_NO_FRICTION;


class Engine
{
public:
	Engine(scalar	acceleration	= ENGINE_DEFAULT_ACCELERATION, 
			scalar	max_speed		= ENGINE_DEFAULT_MAXSPEED,
			UCHAR	rotate_velocity	= ENGINE_DEFAULT_ROTATE_VELOCITY, 
			scalar	friction		= ENGINE_DEFAULT_FRICTION, 
			scalar	breaks_friction	= ENGINE_DEFAULT_BREAKS_FRICTION,
			int		acceleration_handle = ANIMATION_NO_HANDLE);

	Engine(const Engine& engine);

	virtual ~Engine();

	void operator=(const Engine& new_engine);

	scalar	getEngineAcceleration()	const;
	void	setEngineAcceleration(scalar acceleration);

	scalar	getEngineMaxSpeed()	const;
	void	setEngineMaxSpeed(scalar max_speed);

	scalar	getEngineBreaksFriction()	const;
	void	setEngineBreaksFriction(scalar breaks_friction);

	UCHAR	getEngineRotateVelocity()	const;
	void	setEngineRotateVelocity(UCHAR rotate_velocity);

	scalar	getEngineFriction()	const;
	void	setEngineFriction(scalar friction);

	int		getEngineAccelerationHandle()	const;
	void	setEngineAccelerationHandle(int acceleration_handle);

private:
	scalar m_acceleration;
	scalar m_maxSpeed;
	scalar m_rotateVelocity;
	scalar m_friction;
	scalar m_breaksFriction;

	// Acceleration animation variable	//
	int m_acceleration_handle;
};





#endif

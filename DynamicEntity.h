#ifndef __DYNAMICENTITY_H__
#define __DYNAMICENTITY_H__

#include "Entity.h"
#include "Engine.h"


class DynamicEntity : public Entity, public Engine
{
public:
	// Constructor: Create a new DynamicEntity	//
	DynamicEntity(CompositeAnimation& anim,			// Entity's Composite Animation	//
					scalar	mass,					// Mass of the entity			//
					scalar	radius,					// Radius of the entity			//
					long	health,					// Health of the entity			//
					DWORD	ttl,					// Entity's Time to live		//
					fixed	alpha,					// Angle of the entity			//
					vector_2D position,				// Position of the entity		//
					// New Dynamic Entity data:		//
					vector_2D velocity		= vector_2D(),		// Starting velocity of the entity		//
					vector_2D acceleration	= vector_2D(),		// Starting acceleration of the entity	//
					Engine& engine			= Engine()			// Engine of the entity					//
		);
	// Destructor	//
	virtual ~DynamicEntity();

	// Collide: method called when there's a collision with another entity	//
	virtual void Collide(Entity&);

	// Set the entity's acceleration	//
	void SetAcceleration(scalar acceleration);
	void SetAcceleration(vector_2D acceleration);

	// Get the entity's acceleration	//
	vector_2D getAcceleration();

	// Set the entity's velocity		//
	void SetVelocity(scalar velocity);
	void SetVelocity(vector_2D velocity);

	// Get the entity's velocity		//
	vector_2D getVelocity();
	scalar getAbsVelocity();

	// Change the entity's angle		//
	void ChangeAngle(fixed delta);

	// Set a new Engine					//
	void setEngine(Engine &engine);

protected:
	// Move: update the positional variables of the entity		//
	// Called in Iterate() and therefore protected				//
	virtual void Move(scalar time_delta);

	// DisplayAcceleration: define whether the acceleration animation should	//
	// be displayed.															//
	void DisplayAcceleration();

	// Velocity & Acceleration structs	//
	vector_2D m_velocity;
	vector_2D m_acceleration;
};


#endif

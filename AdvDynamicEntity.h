#ifndef __ADVDYNAMICENTITY_H__
#define __ADVDYNAMICENTITY_H__

#include "DynamicEntity.h"
#include "AI.h"

class AdvDynamicEntity : public DynamicEntity
{
public:
	// Constructor: Create a new AdvDynamicEntity	//
	AdvDynamicEntity(CompositeAnimation& anim,	// Entity's Composite Animation	//
						scalar mass,			// Mass of the entity			//
						scalar radius,			// Radius of the entity			//
						long health,			// Health of the entity			//
						DWORD ttl,				// Entity's Time to live		//
						fixed alpha,			// Angle of the entity			//
						vector_2D position,		// Position of the entity		//
						// New Dynamic Entity data:		//
						vector_2D velocity		= vector_2D(),		// Starting velocity of the entity		//
						vector_2D acceleration	= vector_2D(),		// Starting acceleration of the entity	//
						Engine& engine			= Engine()			// Engine of the entity					//
		);

	// Destructor	//
	virtual ~AdvDynamicEntity();

	// ChangeAI: change the AI controlling the entity	//
	void changeAI(AI* new_ai);

protected:
	// UpdateCourse: update the variables affecting the entity's course	//
	virtual void UpdateCourse(scalar time_delta);

	// Pointer to AI controller of the AdvDynamicEntity	//
	AI* m_AI;

};

#endif
#include "AdvDynamicEntity.h"

AdvDynamicEntity::AdvDynamicEntity(CompositeAnimation& anim,
								   scalar mass,
								   scalar radius,
								   long health,
								   DWORD ttl,
								   fixed alpha,
								   vector_2D position,
								   vector_2D velocity,
								   vector_2D acceleration,
								   Engine& engine):
DynamicEntity(anim, mass, radius, health, ttl, alpha, position, velocity, acceleration, engine),
m_AI(NULL)
{
	m_collision_type |= ENTITY_ADVANCED;

	// create a new basic AI for the object	//
	if (m_AI != NULL)
	{
		delete(m_AI);
	}
	m_AI = new AI();
}

////////////////////////////////////////////////////////////////////////////////////

AdvDynamicEntity::~AdvDynamicEntity()
{
	// free the AI object	//
	if (m_AI != NULL)
	{
		delete(m_AI);
	}
}

////////////////////////////////////////////////////////////////////////////////////

void AdvDynamicEntity::changeAI(AI* new_ai)
{
	// avoid NullPointerException	//
	if (m_AI != NULL)
	{
		// Free the old AI object	//
		delete(m_AI);
	}

	// Replace it with the new one	//
	m_AI = new_ai;
}

////////////////////////////////////////////////////////////////////////////////////

void AdvDynamicEntity::UpdateCourse(scalar time_delta)
{
	if (m_AI != NULL)
	{
		m_AI->UpdateEntity(this, time_delta);
	}
}

////////////////////////////////////////////////////////////////////////////////////

#include "ActiveShield.h"

ActiveShield::ActiveShield(CompositeAnimation& anim,	// Entity's Composite Animation		//
						 scalar radius,				// Radius of the entity				//
						 long health,				// Health of the entity				//
						 DWORD ttl,					// Entity's Time to live			//				
						 fixed alpha,				// Angle of the entity				//
						 Entity& protectee,			// Entity protected by the shield	//	
						 scalar protectee_range,	// Range from the protected entity	//
						 fixed start_alpha			// Starting position in the course around the protected entity	//
						 ):
AdvDynamicEntity(anim, 0, radius, health, ttl, alpha, vector_2D()),
m_protectee(protectee)
{
	// Set the AI	//
	changeAI(new CircleAI(m_protectee, protectee_range, start_alpha));	
}


ActiveShield::~ActiveShield()
{
}

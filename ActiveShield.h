#ifndef __ACTIVESHIELD_H__
#define __ACTIVESHIELD_H__

#include "AdvDynamicEntity.h"
#include "CircleAI.h"


class ActiveShield : public AdvDynamicEntity
{
public:
	// Constructor: create a new ship	//
	ActiveShield(CompositeAnimation& anim,	// Entity's Composite Animation		//
				 scalar radius,				// Radius of the entity				//
				 long health,				// Health of the entity				//
				 DWORD ttl,					// Entity's Time to live			//				
				 fixed alpha,				// Angle of the entity				//
				 Entity& protectee,			// Entity protected by the shield	//	
				 scalar protectee_range,	// Range from the protected entity	//
				 fixed start_alpha = 0		// Starting position in the course around the protected entity	//
				);

	// Destructor	//
	~ActiveShield();

protected:
	Entity& m_protectee;
};



#endif
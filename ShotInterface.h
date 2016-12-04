#ifndef __SHOTINTERFACE_H__
#define __SHOTINTERFACE_H__

#include "Entity.h"

class ShotInterface
{
public:
	ShotInterface(DWORD damage);
	virtual ~ShotInterface();

	virtual DWORD GetDamage() = 0;

	// Collide: method called when there's a collision with another entity	//
	void Collide(Entity&);

// Protected members	//
protected:
	DWORD m_damage;		// damage of each shot	//

};



#endif
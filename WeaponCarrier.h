#ifndef __WEAPONCARRIER_H__
#define __WEAPONCARRIER_H__

#include <memory>
#include "DynamicEntity.h"
#include "Weapon.h"
#include "Ship.h"

class Ship;

class WeaponCarrier : public DynamicEntity
{
// Public methods	//
public:
	// Default constructor	//
	WeaponCarrier(DWORD ttl,						// WeaponCarrier's time to live		//
				  fixed alpha,						// Angle of the weapon carrier		//
				  vector_2D position,				// Position of the weapon carrier	//
				  vector_2D velocity = vector_2D(), // Starting velocity of the carrier	//
				  Weapon* weapon = NO_WEAPON		// Weapon carried by the carrier	//
				 );
	
	// Default destructor	//
	~WeaponCarrier();

	// Collide: method called when there's a collision with another entity	//
	virtual void Collide(Entity&);

	Weapon* DetachWeapon();

// Private members	//
private:
	// Weapon being carried by the carrier	//
	Weapon* m_weapon;	

};




#endif
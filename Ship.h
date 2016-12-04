#ifndef __SHIP_H__
#define __SHIP_H__

#include <memory>
#include "AdvDynamicEntity.h"
#include "Weapon.h"
#include "WeaponCarrier.h"

extern const long SHIP_DEFAULT_HEALTH;

class WeaponCarrier;

class Ship : public AdvDynamicEntity
{
// Public methods		//
public:
	// Constructor: create a new ship	//
	Ship(CompositeAnimation& anim,		// Entity's Composite Animation	//
		 scalar	mass,					// Mass of the entity			//
		 scalar	radius,					// Radius of the entity			//
		 long	health,					// Health of the entity			//
		 DWORD	ttl,					// Entity's Time to live		//
		 fixed	alpha,					// Angle of the entity			//
		 vector_2D position,			// Position of the entity		//
		 // New Dynamic Entity data:	//
		 vector_2D velocity	= vector_2D(),	// Starting velocity of the entity		//
		 Engine& engine		= Engine(),		// Engine of the entity					//
		 // New Ship data:				//
		 AI &ai = AI(),							// AI controling the ship			//
		 Weapon *weapon_primary		= NO_WEAPON,// Primary weapon of the ship		//
		 Weapon *weapon_secondary	= NO_WEAPON	// Secondary weapon of the ship		//
		);

	// Destructor	//
	~Ship();

	// Die: Called when the entity dies		//
	virtual void Die(void);

	// Fire:		//
	void Fire(unsigned char weapon_id);


	// ChangeWeapon: change the weapon to the m_selected_weapon	//
	Weapon* changeWeapon(unsigned char weapon_id);
	void ToggleWeapon();

	// AddWeapon: add a weapon to the weapons vector	//
	void AddWeapon(Weapon* new_weapon);

	// RemoveWeapon: dump the currently selected weapon to space	//
	Weapon* RemoveWeapon();

	Weapon* GetWeapon(unsigned char weapon_id);

	void EnableToggle(void);
	void EnableChangeWeapon(void);

// Protected methods	//
protected:
	// ChangeWeapon: change the Weapon	//
	Weapon* changeWeapon(unsigned char weapon_id, Weapon* new_weapon);

// Private methods		//
private:

// public members	//
public:
	enum 
	{
		SELECTED_WEAPON = 0,
		PRIMARY_WEAPON = 1,
		SECONDARY_WEAPON = 2
	};

// Protected members	//
protected:

// Private members	//
private:
	Weapon* m_weapon_primary;
	Weapon* m_weapon_secondary;
	std::vector<Weapon*> m_weapons;
	std::vector<Weapon*>::iterator m_selected_weapon;
	bool m_toggle;
	bool m_change_weapon;
	DWORD m_toggle_time;
	DWORD m_change_weapon_time;

};


#endif
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <memory>
#include "Entity.h"

const scalar MIN_RELOAD_TIME = 100;

class Weapon
{
public:
	// Constructor: Create a new Weapon	//
	Weapon(Entity* host_entity, scalar reload_time);
	
	// Basic destructor	//
	virtual ~Weapon();

	// Fire from m_HostEntity, with the specified velocity (in case of a dynamic entity)	//
	virtual bool Fire(vector_2D velocity = vector_2D());

	// Reload: reload the weapon, set the weapon to be ready to shoot	//
	virtual void Reload(void);

	// SetHostEntity: set a entity hosting this weapon	//
	virtual void SetHostEntity(Entity *new_host_entity);

	// GetBasicAnimation	//
	CompositeAnimation& GetBasicAnimation();
	CompositeAnimation& GetInventoryAnimation();

protected:
	// Entity hosting the weapon	//
	std::auto_ptr<Entity> m_HostEntity;
	scalar m_ReloadTime;
	bool m_isReady;

	// Runtime animation of the weapon	//
	CompositeAnimation m_BasicAnimation;
	CompositeAnimation m_InventoryAnimation;
/*	
	// Runtime animation of the weapon	//
	Animation m_BasicAnimation;

	// Firing animation of the weapon	//
	Animation m_FireAnimation;
*/
};

extern Weapon* NO_WEAPON;

#endif

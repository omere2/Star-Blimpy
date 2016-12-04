#include "Weapon.h"
#include "EntityFactory.h"
#include "GameEngine.h"

Weapon::Weapon(Entity* host_entity, scalar reload_time):
	m_HostEntity(host_entity),
	m_ReloadTime(MAX(reload_time, MIN_RELOAD_TIME)),
	m_isReady(false)
{
	Callback::GetInstance()->AddFunction(new Callable<Weapon>(this, &Weapon::Reload), m_ReloadTime);
}

Weapon::~Weapon()
{
	// Remove all timers associated with this weapon	//
	Callback::GetInstance()->RemoveObject((void*)this);

	// And release the Host Entity to avoid taking it down (along with the whole application)	//
	// With us	//
	m_HostEntity.release();
}


bool Weapon::Fire(vector_2D velocity)
{
	// Check if the weapon is ready to fire	//
	if (!m_isReady)
	{
		// Play sound, or whatever	//
		return false;
	}

	m_isReady = false;
	// Display Fire animations, etc...

	// Set timer for reload	//
	Callback::GetInstance()->AddFunction(new Callable<Weapon>(this, &Weapon::Reload), m_ReloadTime);
	return true;
}


void Weapon::Reload()
{
	m_isReady = true;
}


void Weapon::SetHostEntity(Entity *new_host_entity)
{
	m_HostEntity.release();
	m_HostEntity = std::auto_ptr<Entity>(new_host_entity);
}


CompositeAnimation& Weapon::GetBasicAnimation()
{
	return m_BasicAnimation;
}


CompositeAnimation& Weapon::GetInventoryAnimation()
{
	return m_InventoryAnimation;
}



#include "WeaponCarrier.h"
#include "AnimationFactory.h"

const long DEFAULT_WC_HEALTH = 200;
const int WC_RADIUS = 25;

WeaponCarrier::WeaponCarrier(DWORD ttl,	// WeaponCarrier's time to live		//
				  fixed alpha,			// Angle of the weapon carrier		//
				  vector_2D position,	// Position of the weapon carrier	//
				  vector_2D velocity,	// Starting velocity of the carrier	//
				  Weapon* weapon		// Weapon carried by the carrier	//
				  ):
DynamicEntity(CompositeAnimation(WC_RADIUS, WC_RADIUS), 0, WC_RADIUS, DEFAULT_WC_HEALTH, ttl, 
			  alpha, position, velocity),
m_weapon(weapon)
{
	m_collision_type = ENTITY_TRANSPARENT;
	setEngineFriction(ENGINE_NO_FRICTION);
	
	// Create carrier animation	//
	Animation& CarrierAnimation = AnimationFactory("weaponcarrier");
	m_animation.AddAnimation(CarrierAnimation, 0,0);

	// Add weapon animation inside carrier	//
	if (m_weapon != NO_WEAPON)
	{
		m_animation.AddAnimation(weapon->GetBasicAnimation(), 10,10);

		// Set self as the host entity of the weapon	//
		m_weapon->SetHostEntity(this);
	}
}


WeaponCarrier::~WeaponCarrier()
{
	if (m_weapon != NO_WEAPON)
	{
		delete(m_weapon);
	}
}

Weapon* WeaponCarrier::DetachWeapon()
{
	Weapon* detached_weapon = m_weapon;

	detached_weapon->SetHostEntity(NULL);
	m_weapon = NO_WEAPON;
	Die();
	
	return detached_weapon;
}



void WeaponCarrier::Collide(Entity& target)
{
	// if collided with a ship, send the weapon to it...
	if (target.getCollisionType() & ENTITY_SHIP)
	{
		Ship& ship = (Ship&)target;

		// Add the weapon to the ship	//
		ship.AddWeapon(DetachWeapon());
	}
}

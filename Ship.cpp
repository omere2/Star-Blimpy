#include "Ship.h"
#include "ShipKeyboardAI.h"
#include "MissileLauncher.h"
#include "Gun.h"
#include "GameEngine.h"
#include "EntityFactory.h"

const long SHIP_DEFAULT_HEALTH = 10000;
const DWORD	WEAPON_TOGGLE_TIME = 500;
const DWORD WEAPON_CHANGE_TIME = 500;

Ship::Ship(CompositeAnimation& anim,	// Entity's Composite Animation		//
		   scalar		mass,			// Mass of the entity				//
		   scalar		radius,			// Radius of the entity				//
		   long			health,			// Health of the entity				//
		   DWORD		ttl,			// Entity's Time to live			//
		   fixed		alpha,			// Angle of the entity				//
		   vector_2D	position,		// Position of the entity			//
		   vector_2D	velocity,		// Starting velocity of the entity	//
		   Engine&		engine,			// Engine of the entity				//
		   AI &ai,						// AI controling the ship			//
		   Weapon *weapon_primary,		// Primary weapon of the ship		//
		   Weapon *weapon_secondary		// Secondary weapon of the ship		//
		 ):
AdvDynamicEntity(anim, mass, radius, health, ttl, 
					 alpha, position, velocity, vector_2D(), engine),
	m_weapon_primary(NO_WEAPON),
	m_weapon_secondary(NO_WEAPON),
	m_toggle_time(WEAPON_TOGGLE_TIME),
	m_change_weapon_time(WEAPON_CHANGE_TIME)
{
	m_collision_type = ENTITY_SHIP | ENTITY_ADVANCED;
	
	// Set the AI	//
	changeAI(&ai);

	// Set the weapons	//
	changeWeapon(PRIMARY_WEAPON, weapon_primary);
	changeWeapon(SECONDARY_WEAPON, weapon_secondary);

	// Set a first NO_WEAPON in the m_weapons array	//
	m_selected_weapon = m_weapons.begin();
	m_selected_weapon = m_weapons.insert(m_selected_weapon, NO_WEAPON);

/*
	Weapon* launcher = new MissileLauncher(NULL, 300);
	Weapon* gun = new Gun(NULL, 100, 0.5, 250);
	AddWeapon(launcher);
	AddWeapon(gun);
*/
}


Ship::~Ship()
{	
}


void Ship::Die()
{
	// Create Explosion...	//
	Entity* explosion;
	explosion = &EntityFactory::GetInstance()->CreateEntity(EntityFactory::E_EXPLOSION, m_position, m_alpha, m_velocity);
	GameEngine::GetInstance()->RegisterEntity(*explosion);

	// Parent Die()	//
	DynamicEntity::Die();
}


void Ship::Fire(unsigned char weapon_id)
{
	switch (weapon_id)
	{
	case PRIMARY_WEAPON:
		if (m_weapon_primary != NO_WEAPON)
		{
			m_weapon_primary->Fire(getVelocity());
		}
		break;
	case SECONDARY_WEAPON:
		if (m_weapon_secondary != NO_WEAPON)
		{
			m_weapon_secondary->Fire(getVelocity());
		}
		break;
	}
}


Weapon* Ship::changeWeapon(unsigned char weapon_id, Weapon* new_weapon)
{
	// set success return value	//
	bool ret_val = true;
	Weapon* weapon_to_dump = NO_WEAPON;

	// replace the specified weapon with the new one	//
	// and update the 
	switch (weapon_id)
	{
	case PRIMARY_WEAPON:
		weapon_to_dump = m_weapon_primary;
		m_weapon_primary = new_weapon;
		if (m_weapon_primary != NO_WEAPON)
		{
			m_weapon_primary->SetHostEntity(this);
		}
		break;
	case SECONDARY_WEAPON:
		weapon_to_dump = m_weapon_secondary;
		m_weapon_secondary = new_weapon;
		if (m_weapon_secondary != NO_WEAPON)
		{
			m_weapon_secondary->SetHostEntity(this);
		}
		break;
	// in case no weapon was found, return false	//
	default:
		weapon_to_dump = new_weapon;
		break;
	}

	UpdateObservers(Observer::OBSERVE_WEAPONS);

	// Dump the old weapon to space	//
	return weapon_to_dump;
}


Weapon* Ship::changeWeapon(unsigned char weapon_id)
{
	if (m_change_weapon)
	{
		// check that the selected weapon is valid	//
		if ((m_selected_weapon < m_weapons.end()) && (*m_selected_weapon != NO_WEAPON))
		{
			// try to change the weapon	//
			Weapon* old_weapon = changeWeapon(weapon_id, *m_selected_weapon);

			// if the weapon was replaced	//
			if (old_weapon != *m_selected_weapon)
			{
				// remove the weapon from the vector, and insert the replaced one instead	//
				m_weapons.erase(m_selected_weapon);

				m_selected_weapon = m_weapons.begin();
				if (old_weapon != NO_WEAPON)
				{
					m_selected_weapon = m_weapons.insert(m_selected_weapon, old_weapon);
				}
			}
		}
		m_change_weapon = false;
		Callback::GetInstance()->AddFunction(new Callable<Ship>(this, &Ship::EnableChangeWeapon), m_change_weapon_time);
		UpdateObservers(Observer::OBSERVE_WEAPONS);
	}

	return *m_selected_weapon;
}

void Ship::AddWeapon(Weapon* new_weapon)
{
	if (new_weapon != NO_WEAPON)
	{
		// check that the weapon does not exist	//
		std::vector<Weapon*>::iterator i;
		for (i = m_weapons.begin(); i < m_weapons.end(); i++)
		{
			Weapon* temp_weapon = *i;
			if (temp_weapon == new_weapon)
			{
				return;
			}
		}	

		m_selected_weapon = m_weapons.begin();
		m_selected_weapon = m_weapons.insert(m_selected_weapon, new_weapon);
	}
	UpdateObservers(Observer::OBSERVE_WEAPONS);
}

Weapon* Ship::RemoveWeapon()
{
	if (m_selected_weapon < m_weapons.end())
	{
		Weapon* weapon_to_dump = *m_selected_weapon;
		m_weapons.erase(m_selected_weapon);
		m_selected_weapon = m_weapons.begin();
		free(weapon_to_dump);
	}

	UpdateObservers(Observer::OBSERVE_WEAPONS);
	return NULL;
}


Weapon* Ship::GetWeapon(unsigned char weapon_id)
{
	// default return value is NO_WEAPON	//
	Weapon* weapon = NO_WEAPON;

	// Check which weapon should be returned	//
	switch (weapon_id)
	{
	// in case of the currently selected weapon	//
	case SELECTED_WEAPON:
		// avoid memory crash	//
		if (m_selected_weapon < m_weapons.end())
		{
			// and return the currently selected weapon	//
			weapon = *m_selected_weapon;
		}
		break;
	// in case of the primary weapon	//
	case PRIMARY_WEAPON:
		// return the current primary weapon	//
		weapon = m_weapon_primary;
		break;
	// in case of the secondary weapon	//
	case SECONDARY_WEAPON:
		// return the current secondary weapon	//
		weapon = m_weapon_secondary;
		break;
	// in case of any other weapon	//
	default:
		// return a NO_WEAPON	//
		weapon = NO_WEAPON;
	}

	return weapon;
}


void Ship::ToggleWeapon()
{
	if (m_toggle)
	{
		m_selected_weapon++;
		if (m_selected_weapon >= m_weapons.end())
		{
			m_selected_weapon = m_weapons.begin();
		}
		m_toggle = false;
		Callback::GetInstance()->AddFunction(new Callable<Ship>(this, &Ship::EnableToggle), m_toggle_time);
		UpdateObservers(Observer::OBSERVE_WEAPONS);
	}
}

void Ship::EnableToggle(void)
{
	m_toggle = true;
}

void Ship::EnableChangeWeapon(void)
{
	m_change_weapon = true;
}


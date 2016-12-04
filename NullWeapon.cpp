#include "NullWeapon.h"
#include "AnimationFactory.h"

const scalar MAX_RELOAD_TIME = 1000*36000;

NullWeapon::NullWeapon():
Weapon(NULL, MAX_RELOAD_TIME)
{
	// Create basic animation	//
	m_InventoryAnimation.AddAnimation(AnimationFactory("NoWeapon"), 0, 0);
}

NullWeapon::~NullWeapon()
{
}

bool NullWeapon::Fire(vector_2D velocity)
{
	return false;
}
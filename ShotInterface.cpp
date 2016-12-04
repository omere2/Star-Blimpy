#include "ShotInterface.h"


ShotInterface::ShotInterface(DWORD damage):
m_damage(damage)
{
}


ShotInterface::~ShotInterface()
{
}


void ShotInterface::Collide(Entity& target)
{
	// damage target	//
	target.ChangeHealth(DAMAGE(GetDamage()));
}

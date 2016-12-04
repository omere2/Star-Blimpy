#ifndef __MISSILELAUNCHER_H__
#define __MISSILELAUNCHER_H__

#include "Weapon.h"
#include "Missile.h"
#include "CruiseMissile.h"

class MissileLauncher : public Weapon
{
public:
	enum MISSILE_TYPE
	{
		MISSILE_NORMAL		= 0,
		MISSILE_CRUISE		= 1,
		MISSILE_HOMING		= 2,
	};
public:
	MissileLauncher(Entity* host_entity, scalar reload_time, MISSILE_TYPE type);
	virtual ~MissileLauncher();

	// Fire from the specified DynamicEntity	//
	virtual bool Fire(vector_2D velocity = vector_2D());

protected:
	Entity* CreateMissile(vector_2D launcher_position, scalar launcher_radius, fixed alpha, vector_2D velocity = vector_2D());
	Entity* CreateNormalMissile(fixed alpha, vector_2D velocity);
	Entity* CreateCruiseMissile(fixed alpha, vector_2D velocity);
	Entity* CreateHomingMissile(fixed alpha, vector_2D velocity);

protected:
	MISSILE_TYPE m_type;
};


#endif
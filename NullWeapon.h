#ifndef __NULLWEAPON_H__
#define __NULLWEAPON_H__

#include "Weapon.h"

class NullWeapon : public Weapon
{
public:
	NullWeapon();
	virtual ~NullWeapon();
	virtual bool Fire(vector_2D velocity = vector_2D());
};

#endif
#ifndef __GUN_H__
#define __GUN_H__

#include "Weapon.h"
#include "Shot.h"

class Gun : public Weapon
{
public:
	Gun(Entity* host_entity, scalar reload_time, scalar shot_velocity = SHOT_DEFAULT_VELOCITY, long shot_ttl = SHOT_DEFAULT_TTL);
	virtual ~Gun();

	// Fire from the specified DynamicEntity	//
	virtual bool Fire(vector_2D velocity = vector_2D());
private:
	scalar m_shot_velocity;
	long m_shot_ttl;
};


#endif
#ifndef __COLLISION_H__
#define __COLLISION_H__

/*
#include "Entity.h"
class Collision;

//typedef void (Collision::*CollisionFunc)(Entity&, Entity&);
typedef void (*CollisionFunc)(Entity*, Entity*);
typedef CollisionFunc* CollisionFuncP;

class Collision
{
// Public methods	//
public:
	Collision();
	virtual ~Collision();

	void Initialize();

	inline static void Swap(Entity** e1, Entity** e2, Entity::CollisionTypes type_of_e2);

// Collision methods	//
	static void Collide2Entities(Entity* e1, Entity* e2);
	static void CollideEntityDynamicEntity(Entity* e1, Entity* e2);
	static void Collide2DynamicEntities(Entity* e1, Entity* e2);
	static void CollideEntityShot(Entity* e1, Entity* e2);
	static void CollideDynamicEntityShot(Entity* e1, Entity* e2);
	static void Collide2Shots(Entity* e1, Entity* e2);
	static void CollideShipWeaponCarrier(Entity* e1, Entity*e2);

// Public members	//
public:
	CollisionFunc** m_TheMatrix;

private:
	static const unsigned short MATRIX_SIZE;
};

*/
#endif
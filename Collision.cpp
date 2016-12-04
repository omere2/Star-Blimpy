/*
#include "Collision.h"
#include "baseexception.h"
#include "Entity.h"
#include "DynamicEntity.h"
#include "AdvDynamicEntity.h"
#include "ShotInterface.h"
#include "WeaponCarrier.h"
#include "Ship.h"

const unsigned short Collision::MATRIX_SIZE = 10;

Collision::Collision():
m_TheMatrix(NULL)
{
	Initialize();
}

Collision::~Collision()
{
	if (m_TheMatrix != NULL)
	{
		for (int i=0; i < MATRIX_SIZE; i++)
		{
			if (m_TheMatrix[i] != NULL)
			{
				delete[] m_TheMatrix[i];
			}
		}
		delete[] m_TheMatrix;
	}
}

void Collision::Initialize()
{
	// Allocate the matrix... (hehe)	//
	if (m_TheMatrix == NULL)
	{
		m_TheMatrix = new CollisionFuncP[MATRIX_SIZE];
		if (m_TheMatrix == NULL)
		{
			throw BaseException("Error allocating collision matrix");
		}
		for (int i=0; i<MATRIX_SIZE; i++)
		{
			m_TheMatrix[i] = new CollisionFunc[MATRIX_SIZE];
			if (m_TheMatrix[i] == NULL)
			{
				throw BaseException("Error allocating collision matrix");
			}
		}
	}
	else
	{
		throw BaseException("Collision matrix already initialized");
	}

	// fill it up...	//
	for (int i=0; i < MATRIX_SIZE; i++)
	{
		for (int j=0; j < MATRIX_SIZE; j++)
		{
			if ((i == Entity::SHOT) || (j == Entity::SHOT))
			{
				m_TheMatrix[i][j] = CollideDynamicEntityShot;
			}
			else
			{
				m_TheMatrix[i][j] = Collide2DynamicEntities;
			}
		}
	}



	m_TheMatrix[Entity::ENTITY][Entity::DYNAMIC_ENTITY] = CollideEntityDynamicEntity;
	m_TheMatrix[Entity::DYNAMIC_ENTITY][Entity::ENTITY] = CollideEntityDynamicEntity;
	m_TheMatrix[Entity::DYNAMIC_ENTITY][Entity::DYNAMIC_ENTITY] = Collide2DynamicEntities;
	m_TheMatrix[Entity::DYNAMIC_ENTITY][Entity::SHOT] = CollideDynamicEntityShot;
	m_TheMatrix[Entity::SHOT][Entity::ENTITY] = CollideEntityShot;
	m_TheMatrix[Entity::ENTITY][Entity::SHOT] = CollideEntityShot;
	m_TheMatrix[Entity::SHOT][Entity::DYNAMIC_ENTITY] = CollideDynamicEntityShot;
	m_TheMatrix[Entity::SHOT][Entity::SHIP] = CollideDynamicEntityShot;
	m_TheMatrix[Entity::SHIP][Entity::SHOT] = CollideDynamicEntityShot;
	m_TheMatrix[Entity::SHOT][Entity::SHOT] = Collide2Shots;
	m_TheMatrix[Entity::SHIP][Entity::SHIP] = Collide2DynamicEntities;
	m_TheMatrix[Entity::SHIP][Entity::WEAPON_CARRIER] = CollideShipWeaponCarrier;
	m_TheMatrix[Entity::WEAPON_CARRIER][Entity::SHIP] = CollideShipWeaponCarrier;

}


void Collision::Swap(Entity** e1, Entity** e2, Entity::CollisionTypes type_of_e2)
{
	if ((e1 != NULL) && (*e1 != NULL) && (e2 != NULL))
	{
		if ((*e1)->getCollisionType() == type_of_e2)
		{
			Entity* e3 = *e2;
			*e2 = *e1;
			*e1 = e3;
		}
	}
	return;
}

#define VALIDATE_ENTITIES(a,b) if ((a == NULL) || (b == NULL)) return;

void Collision::Collide2Entities(Entity* e1, Entity* e2)
{
}

void Collision::CollideEntityDynamicEntity(Entity* e1, Entity* e2)
{
	VALIDATE_ENTITIES(e1, e2);
	Swap(&e1, &e2, Entity::DYNAMIC_ENTITY);

	if (e2->getCollisionType() == Entity::ENTITY)
	{
		Collide2Entities(e1, e2);
		return;
	}

	DynamicEntity* de2 = (DynamicEntity*) e2;

	if (de2->getX() < e1->getX())
	{
		de2->m_acceleration.x = -0.02;
	}
	else
	{
		de2->m_acceleration.x = 0.02;
	}
	if (de2->getY() < e1->getY())
	{
		de2->m_acceleration.y = -0.02;
	}
	else
	{
		de2->m_acceleration.y = 0.02;
	}
}

void Collision::Collide2DynamicEntities(Entity* e1, Entity* e2)
{
	VALIDATE_ENTITIES(e1, e2);

	if (e1->getCollisionType() == Entity::ENTITY)
	{
		CollideEntityDynamicEntity(e1, e2);
		return;
	}

	DynamicEntity* de1 = (DynamicEntity*)e1;
	DynamicEntity* de2 = (DynamicEntity*)e2;

	if (de2->getX() < de1->getX())
	{
		de1->m_velocity.x=0.1;
		de2->m_velocity.x=-0.1;
	}
	else
	{
		de1->m_velocity.x=-0.1;
		de2->m_velocity.x=0.1;
	}
	if (de2->getY() < de1->getY())
	{
		de1->m_velocity.y=0.1;
		de2->m_velocity.y=-0.1;
	}
	else
	{
		de1->m_velocity.y=-0.1;
		de2->m_velocity.y=0.1;
	}
}

void Collision::CollideEntityShot(Entity* e1, Entity* e2)
{
	VALIDATE_ENTITIES(e1, e2);
	Swap(&e1, &e2, Entity::SHOT);

	ShotInterface* s2 = (ShotInterface*)e2;

	// damage target	//
	e1->ChangeHealth(DAMAGE(s2->GetDamage()));

	// the shot is no more	//
	e2->Die();	
}

void Collision::CollideDynamicEntityShot(Entity* e1, Entity* e2)
{
	VALIDATE_ENTITIES(e1, e2);
	Swap(&e1, &e2, Entity::SHOT);

	DynamicEntity* de1 = (DynamicEntity*)e1;
	ShotInterface* s2 = (ShotInterface*)e2;

	// first of all, a dynamic collision	//
	Collide2DynamicEntities(e1, e2);

	// damage target	//
	e1->ChangeHealth(DAMAGE(s2->GetDamage()));

	e2->Die();

}

void Collision::Collide2Shots(Entity* e1, Entity* e2)
{
	VALIDATE_ENTITIES(e1, e2);

//	ShotInterface* s1 = (ShotInterface*)e1;
//	ShotInterface* s2 = (ShotInterface*)e2;

	e1->Die();
	e2->Die();
}

void Collision::CollideShipWeaponCarrier(Entity* e1, Entity* e2)
{
	VALIDATE_ENTITIES(e1, e2);
	Swap(&e1, &e2, Entity::WEAPON_CARRIER);

}




*/
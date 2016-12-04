#ifndef __ENTITYPOOL_H__
#define __ENTITYPOOL_H__

#include "Entity.h"
#include <vector>

class EntityPool
{
public:
	EntityPool();
	virtual ~EntityPool();

	void RegisterEntity(Entity &entity);
	Entity& DeRegisterEntity(Entity &entity);
	Entity& DeRegisterEntity(unsigned int index);
	Entity& GetEntity(unsigned int index);
	bool HasEntity(Entity &entity);
	unsigned int GetEntityCount();

	// clears entity pool
	void Clear(); 
	
private:
	std::vector<Entity*> m_entities;

};




#endif
#include "EntityPool.h"
#include "baseexception.h"

EntityPool::EntityPool()
{
}

EntityPool::~EntityPool()
{
	std::vector<Entity*>::iterator i;
	for (i = m_entities.begin(); i < m_entities.end(); i++)
	{
		Entity* entity = *i;
		if (entity != NULL)
		{
			delete(entity);
		}
	}
}


void EntityPool::RegisterEntity(Entity &entity_to_add)
{
	// first, check that the entity is not already in the list...	//	
	std::vector<Entity*>::iterator i;
	for (i = m_entities.begin(); i < m_entities.end(); i++)
	{
		Entity* entity = *i;
		if (entity == &entity_to_add)
		{
			// throw exception ?	//
			return;
		}
	}

	// now we can add the entity to the vector	//
	m_entities.push_back(&entity_to_add);
}


Entity& EntityPool::DeRegisterEntity(unsigned int index)
{
	// set the iterator to the specified position	//
	std::vector<Entity*>::iterator i;
	i = m_entities.begin();
	i+=index;

	// get the entity to return	//
	Entity* entity = *i;

	// remove it from the vector	//
	m_entities.erase(i);

	// and return reference to it	//
	return *entity;
}


Entity& EntityPool::DeRegisterEntity(Entity &entity_to_remove)
{
	// search for the entity in the vector	//
	std::vector<Entity*>::iterator i;
	for (i = m_entities.begin(); i < m_entities.end(); i++)
	{
		// if the entity is found, remove it from the vector, and return refence to it		//
		// the reference is returned to avoid losing all pointers and references withtout	//
		// without destorying the entity					//
		Entity* entity = *i;
		if (entity == &entity_to_remove)
		{
			m_entities.erase(i);
			return *entity;
		}
	}

	throw BaseException("DeRegisterEntity failed: could not find entity");
}

bool EntityPool::HasEntity(Entity &entity_to_find)
{
	// search for the entity in the vector	//
	std::vector<Entity*>::iterator i;
	for (i = m_entities.begin(); i < m_entities.end(); i++)
	{
		// if the entity is found, remove it from the vector, and return refence to it		//
		// the reference is returned to avoid losing all pointers and references withtout	//
		// without destorying the entity					//
		Entity* entity = *i;
		if (entity == &entity_to_find)
		{
			return true;
		}
	}

	// The entity was not found in the pool	//
	return false;
}


Entity& EntityPool::GetEntity(unsigned int index)
{
	// this throws an exception if no entity can be found in the specified index	//
	Entity* entity = m_entities.at(index);

	return *entity;
}


unsigned int EntityPool::GetEntityCount()
{
	// return the size of the entity vector	//
	return m_entities.size();
}

void EntityPool::Clear()
{
	m_entities.clear();
}



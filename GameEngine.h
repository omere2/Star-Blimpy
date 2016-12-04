#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include <allegro.h>
#include <winalleg.h>
#include "common.h"
#include "Entity.h"
#include "EntityPool.h"
#include "Drawable.h"
#include "Collision.h"

extern const int screenx;
extern const int screeny;

class GameEngine
{
public:
	// Destructor	//
	virtual ~GameEngine();
	
	// GetInstance(): get instance of the singleton class	//
	static GameEngine* GetInstance();

	// RegisterEntity(): add an entity to the active entities pool	//
	void RegisterEntity(Entity &entity);

	// DeRegisterEntity(): remove an entity from the active entities pool, and move it to the graveyard	//
	void DeRegisterEntity(Entity &entity);

	// IsAlive(): check if an entity is alive	//
	bool IsAlive(Entity &entity);

	// GetEntitiesInRadius: return a vector of all the entities in the specified radius from the given position	//
	std::vector<Entity*> GetEntitiesInRadius(vector_2D center, scalar radius, bool exclude_self = true);

	// Main GameEngine loop	//
	void Run();

	void AddWidget(Drawable*);


private:	// methods	//
	// Private constructor, to maintain singleton status	//
	GameEngine();

	// CleanGraveYard(): get rid(free) of the corpses in the graveyard	//
	void CleanGraveYard();

	void RegisterEntities();

	void CollisionDetection();
	
	bool isCollision(const Entity& e1, const Entity& e2) const;

	void DrawWidgets(BITMAP* dest);;
	

private:	// members	//
	// Singleton memeber	//
	static GameEngine ms_instance;

	// Pool of active entities	//
	EntityPool m_epool;
	
	// vector of entities waiting to be destroyed	//
	EntityPool m_graveyard;

	// Pool of enitites being born that should be added to the main entity pool
	EntityPool m_infants;

	std::vector<Drawable*> m_widgets;

};


#endif
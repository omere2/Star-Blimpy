#ifndef __ENTITYFACTORY_H__
#define __ENTITYFACTORY_H__

#include "AnimationFactory.h"
#include "DynamicEntity.h"
#include "Weapon.h"

extern const scalar SHOT_DEFAULT_VELOCITY;
extern const long SHOT_DEFAULT_TTL;


class EntityFactory
{
public :
	// Destructor	//
	virtual ~EntityFactory();

	// GetInstance(): get instance of the singleton class	//
	static EntityFactory* GetInstance();
	
	// CreateEntity: Create a new entity	//
	Entity& CreateEntity(const unsigned short, vector_2D position, fixed alpha, vector_2D velocity = vector_2D());

	// Specific Entities Creation	//
	Entity* CreateShip(vector_2D position, fixed alpha, vector_2D velocity = vector_2D());
	Entity* CreateShip2(vector_2D position, fixed alpha, vector_2D velocity = vector_2D());
	Entity* CreateMissile(vector_2D position, fixed alpha, vector_2D velocity = vector_2D());
	Entity* CreateShot(vector_2D position, fixed alpha, vector_2D velocity = vector_2D(), long ttl = SHOT_DEFAULT_TTL, scalar start_velocity = SHOT_DEFAULT_VELOCITY);
	Entity* CreateExplosion(vector_2D position, fixed alpha, vector_2D velocity = vector_2D());
	Entity* CreateStar(vector_2D position, fixed alpha);
	Entity* CreateWeaponCarrier(vector_2D position, fixed alpha, vector_2D velocity = vector_2D(), Weapon* weapon = NO_WEAPON);
	Entity* CreateActiveShield(Entity& protectee, scalar protectee_range, long health = INFINITE_HEALTH, DWORD ttl = INFINITE_TTL, fixed start_alpha = 0);
protected :
	// Singleton memeber	//

	static EntityFactory ms_instance;
	// Private constructor, to maintain singleton status	//
	EntityFactory();	
	


public:
	enum {
		E_USERSHIP1 = 0,
		E_USERSHIP2,
		E_SHOT,
		E_MISSILE,
		E_STAR,
		E_EXPLOSION,
		E_WEAPON_CARRIER
	};



};




#endif

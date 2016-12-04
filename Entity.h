#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "common.h"
#include "CompositeAnimation.h"
#include "Callback.h"
#include "Observable.h"

const long INFINITE_TTL = -1;
const long INFINITE_HEALTH = -1;
const long NO_HEALTH = 0;
const long MAX_HEALTH = 0x7FFF;

#define DAMAGE(x) (x*(-1))


#define ENTITY_TRANSPARENT	(0x00000001)	// Entities pass through it, no dynamic collision	//
#define ENTITY_ADVANCED		(0x00000002)	// Has AI, can be casted as a AdvancedDynamicEntity	//
#define ENTITY_SHIP			(0x00000004)	// A Ship, can collect objects...					//

// class Entity implements a static abstract entity that includes basic components.	//
class Entity : public Observable
{
// Public methods	//
public:
	// Constructor: Create a new Entity	//
	Entity(CompositeAnimation& anim,	// Entity's Composite Animation	//
			scalar mass,				// Mass of the entity			//
			scalar radius,				// Radius of the entity			//
			long health,				// Health of the entity			//
			DWORD ttl,					// Entity's Time to live		//
			fixed alpha,				// Angle of the entity			//
			vector_2D position);		// Position of the entity		//

	// Destructor	//
	virtual ~Entity();

	// Iterate: Do all per-turn based actions for the entity	//
	// Called by "GameEngine" and therefore public					//
	virtual void Iterate(scalar time_delta);

	// Draw: draw the entity on the specifed buffer		//
	// Called by "GameEngine" and therefore public			//
	void Draw(BITMAP* dest, int x, int y);

	// Collide: method called when there's a collision with another entity	//
	virtual void Collide(Entity&);

	// Die: Called when ttl expired, Deregister self from GameEngine	//
	virtual void Die(void);

	// GetPosition: returns struct of the entity's position		//
	vector_2D getPosition() const;
	
	// SetPosition: sets the entity's position		//
	void setPosition(const vector_2D position);

	// SetName: sets the entity's name	//
	void setName(std::string name);

	// getHealth: get the entity's health	//
	long getHealth() const;

	// Change the entity's health	//
	void setHealth(const long new_health);
	long ChangeHealth(const long delta);

	// getXXX: returns member	//
	scalar getX() const;
	scalar getY() const;
	scalar getRadius() const;
	fixed getAlpha() const;
	std::string getName() const;

	UCHAR getCollisionType() const;

	CompositeAnimation& getCompositeAnimation();

// Protected methods	//
protected:
	// Move: update the positional variables of the entity		//
	// empty for static entities, overriden by dynamic ones	//
	// Called in Iterate() and therefore protected				//
	virtual void Move(scalar time_delta) {};

	// UpdateCourse: update the variables affecting the entity's course	//
	// empty for static entities, overriden by advanced dynamic ones	//
	// Called in Iterate() and therefore protected						//
	virtual void UpdateCourse(scalar time_delta) {}; 

	void DisableAnimation(int handle);
	void EnableAnimation(int handle);

// Protected members	//
protected:
	long m_health;						// Health of the entity							//
	DWORD m_ttl;						// Time to live, entity dies when this zeroes	//
	DWORD m_creation_time;				// Creation time of the entity					//
	scalar m_mass;						// Mass	of the entity							//
	scalar m_radius;					// Radius of the entity (maximal)				//
	fixed m_alpha;						// Angle of the entity							//
	vector_2D m_position;				// Position of the entity						//	
	CompositeAnimation m_animation;		// Composite Animation class of the entity		//
	std::string m_name;					// name of the entity							//
	UCHAR m_collision_type;				// type of collision involving this entity		//
// Private members	//
private:
};


#endif



#include "Entity.h"
#include "GameEngine.h"
#include "DeathException.h"

Entity::Entity(CompositeAnimation& anim,
			scalar mass, scalar radius, long health, DWORD ttl, 
			fixed alpha, vector_2D position):
	m_collision_type(0),
	m_animation(anim),
	m_mass(mass), 
	m_radius(radius), 
	m_position(position), 
	m_health(health),
	m_ttl(ttl), 
	m_alpha(alpha),
	m_name("")
{
	// Get the creation time of the entity	//
	m_creation_time= GetTickCount();

	// If this entity has a limited time to live, create a timer that will call it's Die() method when the ttl expires	//
	if (ttl != INFINITE_TTL)
	{
		Callback::GetInstance()->AddFunction(new Callable<Entity>(this, &Entity::Die), ttl);
	}
}


////////////////////////////////////////////////////////////////////////////////////

Entity::~Entity()
{
	Callback::GetInstance()->RemoveObject((void*)this);
}

////////////////////////////////////////////////////////////////////////////////////

void Entity::Iterate(scalar time_delta)
{
	// Check if the entity should die	//
	if (m_health == NO_HEALTH)
	{
		Die();
		// omer, why exception logic? anyway, I need to updateobservers!
		// throw DeathException();
	}
	else 
	{
		// Move() the entity	//
		Move(time_delta);

		// Update-its-Course()	//
		UpdateCourse(time_delta);
		UpdateObservers(Observer::OBSERVE_POSITION);
	}


	return;
}


////////////////////////////////////////////////////////////////////////////////////

void Entity::Draw(BITMAP* dest, int x, int y)
{
	// draw the entity, in the specified buffer,	//
	// according to its position and angle			//
	//m_animation.Draw(dest, m_position.x, m_position.y, m_alpha);
	m_animation.Draw(dest, x, y, m_alpha);
}


////////////////////////////////////////////////////////////////////////////////////

void Entity::DisableAnimation(int handle)
{
	m_animation.Disable(handle);
}

////////////////////////////////////////////////////////////////////////////////////

void Entity::EnableAnimation(int handle)
{
	m_animation.Enable(handle);
}

////////////////////////////////////////////////////////////////////////////////////

scalar Entity::getX() const
{
	return m_position.x;
}

////////////////////////////////////////////////////////////////////////////////////

scalar Entity::getY() const
{
	return m_position.y;
}

////////////////////////////////////////////////////////////////////////////////////

vector_2D Entity::getPosition() const
{
	return m_position;
}

////////////////////////////////////////////////////////////////////////////////////

scalar Entity::getRadius() const
{
	return m_radius;
}

////////////////////////////////////////////////////////////////////////////////////

fixed Entity::getAlpha() const 
{
	return m_alpha;
}

void Entity::Collide(Entity&)
{
}

////////////////////////////////////////////////////////////////////////////////////

void Entity::Die()
{
	GameEngine::GetInstance()->DeRegisterEntity(*this);
}

////////////////////////////////////////////////////////////////////////////////////

void Entity::setPosition(const vector_2D position)
{
	m_position = position;
}

////////////////////////////////////////////////////////////////////////////////////

long Entity::getHealth() const
{
	return m_health;
}

////////////////////////////////////////////////////////////////////////////////////

void Entity::setHealth(const long new_health)
{
	m_health = new_health;
}

////////////////////////////////////////////////////////////////////////////////////

long Entity::ChangeHealth(const long delta)
{
	// if we're not talking about an immortal entity	//
	if (m_health != INFINITE_HEALTH)
	{
		if (m_health + delta <= NO_HEALTH)
		{
			m_health = NO_HEALTH;
		}
		else if (m_health + delta >= MAX_HEALTH) 
		{
			m_health = MAX_HEALTH;
		}
		else
		{
			m_health += delta;
		}
		UpdateObservers(Observer::OBSERVE_HEALTH);
	}
	
	return m_health;
}

CompositeAnimation& Entity::getCompositeAnimation()
{
	return m_animation;
}


std::string Entity::getName() const
{
	return m_name;
}

UCHAR Entity::getCollisionType() const
{
	return m_collision_type;
}



void Entity::setName(std::string new_name)
{
	m_name = new_name;
}
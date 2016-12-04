#include "star.h"

Star::Star(CompositeAnimation& anim,  
		   scalar mass, 
		   scalar radius,
		   DWORD ttl,
		   fixed alpha, 
		   vector_2D position):
Entity(anim, mass, radius, INFINITE_HEALTH, ttl, alpha, position)
{
}


Star::~Star()
{
}

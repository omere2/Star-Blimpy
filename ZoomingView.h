#ifndef __ZOOMING_VIEW_H__
#define __ZOOMING_VIEW_H__

#include "WorldView.h"
#include "Observer.h"
#include "Entity.h"


// ZoomingView is a view class, responsible of following a certain entity or entities,	//
// while zooming in/out to keep the followed entities on screen							//
class ZoomingView : public WorldView, public Observer
{
public:
	ZoomingView(int default_x, int default_y, int draw_posx, int draw_posy, int default_width, int default_height);
	~ZoomingView();
	
	virtual void UpdateView();

	// AddObservedEntity: add an entity to the list of entities in view	//
	void AddObservedEntity(Entity &entity);
	
	// RemoveObservedEntity: remove an entity from the list of entities in view	//
	void RemoveObservedEntity(Entity &entity);

private:
	// default values, in case there are no observed entities	//
	int		m_default_x;		
	int		m_default_y;
	int		m_default_width;
	int		m_default_height;	

	// indicates whether the view should be updated				//
	bool	m_updated;
};







#endif
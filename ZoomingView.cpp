
#include "ZoomingView.h"


ZoomingView::ZoomingView(int default_x, int default_y, int draw_posx, int draw_posy, int default_width, int default_height):
	WorldView(0, 0, draw_posx, draw_posy, default_width, default_height)
{
}

ZoomingView::~ZoomingView()
{
}

/*
void ZoomingView::ObserverUpdate()
{
	//	check if there is more then one entity

	m_x = m_observed_entity->getX()-m_width/2;
	m_y = m_observed_entity->getY()-m_height/2;
}
*/

void ZoomingView::UpdateView()
{
}
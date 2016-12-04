#include "WorldView.h"



WorldView::WorldView(int x, int y, int draw_posx, int draw_posy, int width, int height):
	m_x(x),
	m_y(y),
	m_draw_posx(draw_posx),
	m_draw_posy(draw_posy),
	m_width(width),
	m_height(height)
{
}

WorldView::~WorldView()
{
}

int WorldView::getX() const
{
	return m_x;
}

int WorldView::getY() const
{
	return m_y;
}

int WorldView::getDrawPosX() const
{
	return m_draw_posx;
}

int WorldView::getDrawPosY() const
{
	return m_draw_posy;
}

int WorldView::getWidth() const
{
	return m_width;
}

int WorldView::getHeight() const
{
	return m_height;
}


bool WorldView::InView(int x, int y) const
{
	if ((x > m_x) && (x < m_x + m_width) &&
		(y > m_y) && (y < m_y + m_height))
	{
		return true;	
	}

	return false;
}


void WorldView::UpdateView()
{
	return;
}

#ifndef __WORLD_VIEW_H__
#define __WORLD_VIEW_H__

// WorldView is a class responsible to hold the current view of the screen		//
// Supplying a method to help decide whether a coordinate is inside the view	// 

class WorldView
{
public:
	WorldView(int x, int y, int draw_posx, int draw_posy, int width, int height);
	~WorldView();

	int getX() const;
	int getY() const;
	int getDrawPosX() const;
	int getDrawPosY() const;
	int getWidth() const;
	int getHeight() const;
	bool InView(int x, int y) const;
	virtual void UpdateView();

protected:
	int m_x;
	int m_y;
	int m_draw_posx;
	int m_draw_posy;
	int m_width;
	int m_height;
};


#endif
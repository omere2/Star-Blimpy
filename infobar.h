#ifndef __INFOBAR__H__
#define __INFOBAR__H__

#include <string>
#include "common.h"
#include "Drawable.h"

class InfoBar : public Drawable
{
public:
	InfoBar(int x, int y, int width, int height,
		int capacity, std::string text, 
		int text_color, int fill_color, int border_color);

	virtual ~InfoBar();

	virtual void Draw(BITMAP* dest);
	
	// inherited from Drawable
	virtual void Draw(BITMAP* dest, int x, int y, fixed alpha);
	virtual void Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha);

	virtual void Update(int progress);
	virtual void SetTransperancy(int r, int g, int b, int a);

	virtual void operator-=(int x);
	virtual void operator+=(int x);

protected:
	int m_x, m_y;
	int m_width, m_height;
	int m_capacity;
	std::string m_text;
	int m_text_color;
	int m_fill_color;
	int m_border_color;

	int m_progress;

private:	
	int m_trans_r;
	int m_trans_g;
	int m_trans_b;
	int m_trans_alpha;
	BITMAP* m_bitmap;

};

#endif
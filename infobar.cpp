#include "infobar.h"


	
InfoBar::InfoBar(int x, int y, int width, int height,
		int capacity, std::string text, 
		int text_color, int fill_color, int border_color):
		m_x(x), m_y(y), m_width(width), m_height(height),
		m_capacity(capacity), m_text(text), m_text_color(text_color),
		m_fill_color(fill_color), m_border_color(border_color),
		m_progress(capacity), 
		// no transperacy
		m_trans_r(255), 
		m_trans_g(255), 
		m_trans_b(255), 
		m_trans_alpha(255)
{
	m_bitmap = create_bitmap(m_width + 2, m_height + 2);
	setRotatble(false);
}

InfoBar::~InfoBar()
{
	destroy_bitmap(m_bitmap);
}

void InfoBar::Draw(BITMAP* dest)
{
	clear_bitmap(m_bitmap);
	
	scalar width = ((scalar)m_progress / m_capacity)*m_width;
	if (m_progress > 0)
	{
		rectfill(m_bitmap, 1, 1, width, m_height, m_fill_color);
	}
	rect(m_bitmap, 0, 0, m_width + 1, m_height + 1, m_border_color);

	set_trans_blender(m_trans_r, m_trans_g, m_trans_b, m_trans_alpha);
	draw_trans_sprite(dest, m_bitmap, m_x, m_y);
	

	textout_centre(dest, font, m_text.c_str(), m_x + m_width/2, m_y+m_height+3, m_text_color);
}

void InfoBar::Draw(BITMAP* dest, int x, int y, fixed alpha)
{
	m_x = x;
	m_y = y;
	Draw(dest);
}

void InfoBar::Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha)
{
	m_x = x;
	m_y = y;
	Draw(dest);
}

void InfoBar::Update(int progress)
{
	if ((progress >= 0) && (progress <= m_capacity))
	{
		m_progress = progress;
	}
	else if (progress < 0)
	{
		m_progress = 0;
	}
	else
	{
		m_progress = m_capacity;
	}
}

void InfoBar::operator-=(int x) 
{ 
	Update(m_progress - x); 
};

void InfoBar::operator+=(int x)
{
	Update(m_progress + x);
}

void InfoBar::SetTransperancy(int r, int g, int b, int a)
{
	m_trans_r = r;
	m_trans_g = g;
	m_trans_b = b;
	m_trans_alpha = a;
}

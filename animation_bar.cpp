#include "animation_bar.h"

AnimationBar::AnimationBar(int x, int y, int width, int height, int border_color,
							 std::string text, int text_color):
	m_x(x),
	m_y(y),
	m_width(width),
	m_height(height),
	m_border_color(border_color),
	m_text(text),
	m_text_color(text_color),
	// no transperacy
	m_trans_r(255), 
	m_trans_g(255), 
	m_trans_b(255), 
	m_trans_alpha(255),
	m_animation(new CompositeAnimation())
{
	setRotatble(false);
	m_bitmap = create_bitmap(m_width + 2, m_height + 2);
}


AnimationBar::~AnimationBar()
{
	destroy_bitmap(m_bitmap);
}

void AnimationBar::Update(CompositeAnimation &new_animation)
{
	m_animation = std::auto_ptr<CompositeAnimation>(&new_animation);
}

void AnimationBar::SetTransperancy(int r, int g, int b, int a)
{
	m_trans_r = r;
	m_trans_g = g;
	m_trans_b = b;
	m_trans_alpha = a;
}

void AnimationBar::Draw(BITMAP* dest)
{
	clear_bitmap(m_bitmap);
	rectfill(m_bitmap, 0, 0, m_width + 1, m_height + 1, 0xff00ff);
	m_animation->Draw(m_bitmap, 0, 0);
	rect(m_bitmap, 0, 0, m_width + 1, m_height + 1, m_border_color);

	set_trans_blender(m_trans_r, m_trans_g, m_trans_b, m_trans_alpha);
	draw_trans_sprite(dest, m_bitmap, m_x, m_y);
	
	textout_centre(dest, font, m_text.c_str(), m_x + m_width/2, m_y+m_height+3, m_text_color);
}

void AnimationBar::Draw(BITMAP* dest, int x, int y, fixed alpha)
{
	m_x = x;
	m_y = y;
	Draw(dest);
}

void AnimationBar::Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha)
{
	m_x = x;
	m_y = y;
	Draw(dest);
}

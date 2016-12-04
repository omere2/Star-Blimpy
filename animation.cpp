#include "animation.h"

Animation::Animation(DWORD total_time, unsigned long cycle_image):
	BasicAnimation(cycle_image), 
	m_total_time(total_time)
{
}


Animation::Animation(const Animation& src):
	BasicAnimation(src),
	m_total_time(src.m_total_time)
{
}


void Animation::operator=(const Animation& src)
{
	BasicAnimation::operator=(src);
	m_total_time = src.m_total_time;
}


Animation::~Animation()
{
}


void Animation::Draw(BITMAP* dest, int x, int y, fixed alpha)
{
	rotate_sprite(dest, const_cast<BITMAP*>(GetNextImage(m_total_time)), x, y, alpha);
}


void Animation::Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha)
{
	pivot_sprite(dest, const_cast<BITMAP*>(GetNextImage(m_total_time)), x, y, cx, cy, alpha);
}


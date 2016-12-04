#include "CompositeAnimation.h"

CompositeAnimation::CompositeAnimation(int pivot_x, int pivot_y):
	_animations(NULL), _num_of_animations(0),
	_pivot_x(pivot_x), _pivot_y(pivot_y)
{
}

CompositeAnimation::CompositeAnimation(CompositeAnimation& src)
{
	std::vector<AnimationPos*>::iterator i;
	for (i = src._animations.begin(); i < src._animations.end(); i++)
	{
		AnimationPos* x = new AnimationPos;
		x->animation_object = (*i)->animation_object;
		x->relx = (*i)->relx;
		x->rely = (*i)->rely;
		x->is_enabled = (*i)->is_enabled;
		x->handle = (*i)->handle;
		_animations.push_back(x);
	}
	_pivot_x = src._pivot_x;
	_pivot_y = src._pivot_y;
}

CompositeAnimation::~CompositeAnimation()
{
}

int CompositeAnimation::AddAnimation(Drawable& anim, int relx, int rely)
{
	AnimationPos* x = new AnimationPos;
	x->animation_object = &anim;
	x->relx = relx;
	x->rely = rely;
	x->handle = _num_of_animations;
	x->is_enabled = true;
	_animations.push_back(x);
	return _num_of_animations++;
}

void CompositeAnimation::Draw(BITMAP* dest, int x, int y, fixed alpha)
{
	std::vector<AnimationPos*>::iterator i;
	for (i = _animations.begin(); i < _animations.end(); i++)
	{
		if ((*i)->handle != ANIMATION_NO_HANDLE)
		{
			if ((*i)->is_enabled) 
			{

				if ((*i)->animation_object->isRotatable())
				{
					const int relative_subanimation_x = (*i)->relx - _pivot_x;
					const int relative_subanimation_y = (*i)->rely - _pivot_y;
//					const float float_alpha = fixtof(alpha);
//					const float rotated_subanimation_x = relative_subanimation_x * cosf(float_alpha) - relative_subanimation_y * sinf(float_alpha);
//					const float rotated_subanimation_y = relative_subanimation_x * sinf(float_alpha) + relative_subanimation_y * cosf(float_alpha);
					const float rotated_subanimation_x = relative_subanimation_x * fixtof(fixcos(alpha)) - relative_subanimation_y * fixtof(fixsin(alpha));
					const float rotated_subanimation_y = relative_subanimation_x * fixtof(fixsin(alpha)) + relative_subanimation_y * fixtof(fixcos(alpha));
					(*i)->animation_object->Draw(dest, x + rotated_subanimation_x, y + rotated_subanimation_y, 0,0, alpha);
				}
				else
				{
					(*i)->animation_object->Draw(dest, x+(*i)->relx, y+(*i)->rely, 0 ,0, 0);
				}
			}
		}
	}
}

void CompositeAnimation::Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha)
{
	Draw(dest, x, y, alpha);
}

void CompositeAnimation::Disable(int handle)
{
	std::vector<AnimationPos*>::iterator i;
	for (i = _animations.begin(); i < _animations.end(); i++)
	{
		if ((*i)->handle == handle)
			(*i)->is_enabled = false;
	}
	
}

void CompositeAnimation::Enable(int handle)
{
	std::vector<AnimationPos*>::iterator i;
	for (i = _animations.begin(); i < _animations.end(); i++)
	{
		if ((*i)->handle == handle)
			(*i)->is_enabled = true;
	}
}

void CompositeAnimation::setPivot(int pivot_x, int pivot_y)
{
	_pivot_x = pivot_x;
	_pivot_y = pivot_y;
}


int CompositeAnimation::GetAnimationCount() const
{
	return _num_of_animations;
}


void CompositeAnimation::Clear()
{
	_animations.clear();
	_num_of_animations = 0;
}

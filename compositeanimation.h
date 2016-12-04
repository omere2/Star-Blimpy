#ifndef __COMPOSITEANIMATION_H__
#define __COMPOSITEANIMATION_H__

#include <vector>
#include "Animation.h"

const int ANIMATION_NO_HANDLE = 0xffffffff;

class CompositeAnimation : public Drawable
{
public:
	CompositeAnimation(int pivot_x = 0 , int pivot_y = 0);
	CompositeAnimation(CompositeAnimation&); // copy ctor
	~CompositeAnimation();

	int AddAnimation(Drawable&, int relx, int rely);
	void Draw(BITMAP* dest, int x, int y, fixed alpha = 0);
	void Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha = 0);
	void Disable(int handle);
	void Enable(int handle);
	void setPivot(int pivot_x, int pivot_y);
	int GetAnimationCount() const;
	void Clear();
private:
	void operator=(CompositeAnimation&); // prevent = operator
	struct AnimationPos
	{
		int handle;
		bool is_enabled;
		Drawable* animation_object;
		int relx;
		int rely;
	};

	int _pivot_x, _pivot_y;

	std::vector<AnimationPos*> _animations;
	int _num_of_animations;
};

#endif
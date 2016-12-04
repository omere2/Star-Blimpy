#ifndef __ANIMATION_BAR_H__
#define __ANIMATION_BAR_H__

#include <memory>
#include "Drawable.h"
#include "compositeanimation.h"

class AnimationBar : public Drawable
{
public:
	AnimationBar(int x, int y, int width, int height, int border_color = 0x00e000, 
				 std::string text = "", int text_color = 0xe000e0);

	virtual ~AnimationBar();
	
	virtual void Draw(BITMAP* dest);
	
	// inherited from Drawable
	virtual void Draw(BITMAP* dest, int x, int y, fixed alpha);
	virtual void Draw(BITMAP* dest, int x, int y, int cx, int cy, fixed alpha);

	virtual void Update(CompositeAnimation &new_animation);
	virtual void SetTransperancy(int r, int g, int b, int a);

protected:
	int m_x, m_y;
	int m_width, m_height;
	int m_border_color;
	std::string m_text;
	int m_text_color;
	std::auto_ptr<CompositeAnimation> m_animation;

private:	
	int m_trans_r;
	int m_trans_g;
	int m_trans_b;
	int m_trans_alpha;
	BITMAP* m_bitmap;
};


#endif
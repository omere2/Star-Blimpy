#include <assert.h>
#include "BaseException.h"
#include "BasicAnimation.h"
#include <windows.h>
#include <stdlib.h>



BasicAnimation::BasicAnimation(unsigned long cycle_image):
	_number_of_images(0), _current_image(0),
	_last_update_time(0), _bitmaps(NULL)
{
	_cycle_image = cycle_image;
}

BasicAnimation::BasicAnimation(const BasicAnimation& src):
	_number_of_images(src._number_of_images), _current_image(0),
	_last_update_time(0), _bitmaps(NULL)
{
	for (int i = 0; i < src._bitmaps.size(); i++)
	{
		RefBitmap* current_bitmap = new RefBitmap(*src._bitmaps[i]);
		_bitmaps.push_back(current_bitmap);
	}
	_cycle_image = src._cycle_image;
}

// frees all bitmaps acuired for animation	
BasicAnimation::~BasicAnimation()
{
	std::vector<RefBitmap*>::iterator i;
	for (i = _bitmaps.begin(); i < _bitmaps.end(); i++)
	{
		delete *i;
	}
}

// Load an image to the animation sequence.
void BasicAnimation::LoadImage(std::string filename)
{
	//RGB pal[256];
	RefBitmap* current_bitmap = new RefBitmap(filename);
	
	_bitmaps.push_back(current_bitmap);
	_number_of_images++;
}

// Upon starting the animation, make current image the first one.
void BasicAnimation::StartAnimation()
{
	_current_image = 0;
}

// Return the next image in the animation sequence.
// Parameter states the number of milliseconds must pass from last call in order
// to advance the current animation frame.
const BITMAP* BasicAnimation::GetNextImage(DWORD milliseconds)
{
	//static DWORD 
	DWORD current_time = GetTickCount();
	//_last_update_time = GetTickCount();

	assert(_last_update_time <= current_time);
	assert(_number_of_images != 0);

	if (_last_update_time + milliseconds <= current_time)
	{
		IncreaseCurrentImage();
		_last_update_time = current_time;
	}


	assert(_bitmaps[_current_image]->Get() != NULL);
	
	return _bitmaps[_current_image]->Get();
}

// Advance current image. Wrap if passed number of images in animation
void BasicAnimation::IncreaseCurrentImage()
{
	_current_image++;
	if (_current_image >= _number_of_images)
		_current_image = _cycle_image;

	assert(_bitmaps[_current_image]->Get() != NULL);
}


void BasicAnimation::operator=(const BasicAnimation& src)
{
	_number_of_images = src._number_of_images;
	_current_image = 0;
	_last_update_time = 0;
	_bitmaps.clear();

	for (int i = 0; i < src._bitmaps.size(); i++)
	{
		RefBitmap* current_bitmap = new RefBitmap(*src._bitmaps[i]);
		_bitmaps.push_back(current_bitmap);
	}

	_cycle_image = src._cycle_image;
}

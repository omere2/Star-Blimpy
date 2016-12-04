#ifndef __BASICANIMATION_H__
#define __BASICANIMATION_H__

#include <allegro.h>
#include <winalleg.h>
#include <string>
#include <vector>
#include "RefBitmap.h"



// Class BasicAnimation provides basic facilities for animation.
// The class can load images into the animation sequence, and
// display them by order.
class BasicAnimation
{
public:
	BasicAnimation(unsigned long cycle_image = 0);
	BasicAnimation(const BasicAnimation&); // copy constructor
	virtual ~BasicAnimation();

	// Load an image from the harddisk.
	// This method can throw LoadImageError if failed to
	// load file or isn't a bitmap file
	void LoadImage(std::string filename);
	
	// Make sure current image is the first image
	void StartAnimation();

	// Get next image only if passed at least the given number of milliseconds
	// from last call to the function. Otherwise, return the current image.
	const BITMAP* GetNextImage(DWORD milliseconds = 0);
protected:
	void operator=(const BasicAnimation&); // prevent assignment operator


	// Increase _current_image with overlapping
	void IncreaseCurrentImage();

	unsigned long _number_of_images; // number of array slots occupied by images
	unsigned long _current_image; // current image in the animation
	unsigned long _cycle_image; // image where to cycle
	DWORD _last_update_time;
	
	std::vector<RefBitmap*> _bitmaps; // vector of images of the animation
};

#endif
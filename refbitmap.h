#ifndef __REFBITMAP_H__
#define __REFBITMAP_H__

#include <allegro.h>
#include <winalleg.h>
#include <string>
#include "BaseException.h"

// Declare the exception class thrown by Animation class
class LoadImageError : public BaseException
{
public:
	LoadImageError(std::string error_description = std::string());
};


// Export BITMAP* with reference count
class RefBitmap
{
public:
	RefBitmap(const std::string); // Load an image from drive
	RefBitmap(const RefBitmap&); // Copy an existing image
	~RefBitmap(); 

	const BITMAP* Get() const; // Get BITMAP* associated with current object
private:
	RefBitmap& operator=(RefBitmap&); // do not allow opertor=
	BITMAP* _bitmap;
	int* _ref_count;
};


#endif
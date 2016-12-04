#include <assert.h>
#include "refbitmap.h"
#include "png\loadpng.h"

LoadImageError::LoadImageError(std::string error_description):
	BaseException(error_description)
{
}

RefBitmap::RefBitmap(const std::string filename):
	_bitmap(NULL), _ref_count(NULL)
{
	RGB pal[256];
	BITMAP* current_bitmap;
	
	if (filename.find(".png") != std::string::npos)
	{
		current_bitmap = load_png(filename.c_str(), pal);
	}
	else
	{
		current_bitmap = load_bitmap(filename.c_str(), pal);
	}
	if (NULL == current_bitmap)
	{
		std::string error_str;
		error_str = "load_bitmap(" + filename + ") failed!";
		throw LoadImageError(error_str);
	}

	_ref_count = new int;
	*_ref_count = 1;

	_bitmap = current_bitmap;
}

RefBitmap::RefBitmap(const RefBitmap& src)
{
	assert(src._bitmap != NULL);
	assert(src._ref_count != NULL);
	assert((*src._ref_count) != 0);
	_bitmap = src._bitmap;
	_ref_count = src._ref_count;
	(*_ref_count)++;
}

RefBitmap::~RefBitmap()
{
	assert(_ref_count != NULL);
	assert(*_ref_count > 0);

	(*_ref_count)--;
	if ((*_ref_count) == 0)
	{
		destroy_bitmap(_bitmap);
		_bitmap = NULL;
		delete _ref_count;
		_ref_count = NULL;
	}
}

const BITMAP* RefBitmap::Get() const
{
	assert(_bitmap != NULL);

	return _bitmap;
}
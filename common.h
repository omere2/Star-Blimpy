#ifndef __COMMON_H__
#define __COMMON_H__

#pragma warning(disable: 4786)

#include <allegro.h>
#include <winalleg.h>

#define VIDEO_BUFFERS (3)

typedef double scalar;

struct vector_2D
{
	vector_2D() { x = y = 0;} ;
	vector_2D(scalar new_x, scalar new_y) { x = new_x; y = new_y; };
	scalar x;
	scalar y;
};

#endif
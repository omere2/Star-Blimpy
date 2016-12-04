   #pragma warning (disable: 4786)

#include <map>
#include <fstream>
#include <strstream>
#include "AnimationFactory.h"
#include "animation.h"


using namespace std;

Animation& AnimationFactory(const std::string& name)
{
	static map<string, Animation> loaded_animations;
	
	if (loaded_animations.find(name) == loaded_animations.end()) 
	{
		// Load animation

		ifstream animation_info(("animations\\" + name + "\\animation_info.txt").c_str());
		int frame_rate;
		int cycle_image;
		int number_of_images;
		animation_info >> number_of_images;
		animation_info >> frame_rate;
		animation_info >> cycle_image;

		Animation anim(frame_rate, cycle_image);

		for (int i=1; i<=number_of_images; i++)
		{
			char image_name[1000];
			try {
				sprintf(image_name, "animations\\%s\\%d.pcx", name.c_str(), i);
				anim.LoadImage(image_name);
			}
			catch (LoadImageError&)
			{
				sprintf(image_name, "animations\\%s\\%d.png", name.c_str(), i);
				anim.LoadImage(image_name);
			}
		}
		loaded_animations[name] = anim;
	} 

	Animation* t = new Animation(loaded_animations[name]);
	return *t;
}

void PreloadAnimations()
{
	WIN32_FIND_DATA data;
	HANDLE dir = FindFirstFile(".\\animations\\*", &data);

	if (dir != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(dir, &data) != 0)
		{
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				Animation* t = &(AnimationFactory(data.cFileName));
				delete t;
			}
		}
	}
}
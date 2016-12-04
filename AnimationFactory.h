#ifndef __ANIMATION_FACTORY_H__
#define __ANIMATION_FACTORY_H__

#include <string>
#include "animation.h"

// ./animations/kewl_explosion/animation_info.xml
Animation& AnimationFactory(const std::string& name);

// preload animations so it doesn't take time during first show in the game
void PreloadAnimations();



#endif
#ifndef __HEALTH_INFO_BAR_H__
#define __HEALTH_INFO_BAR_H__

#include <string>
#include "infobar.h"
#include "observer.h"
#include "Entity.h"

class HealthInfoBar : public InfoBar, public Observer
{
public:
	HealthInfoBar::HealthInfoBar(Entity* observed_entity,
		int x, int y, int width, int height,
		std::string text = "", 
		int text_color = 0xe000e0, int fill_color = 0xff0000, int border_color = 0x00e000);
		
	virtual HealthInfoBar::~HealthInfoBar();

	virtual void ObserverUpdate(Observable&);

protected:
};

#endif
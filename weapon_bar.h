#ifndef __WEAPON_INFO_BAR_H__
#define __WEAPON_INFO_BAR_H__

#include "animation_bar.h"
#include "Observer.h"
#include "Ship.h"
#include "compositeanimation.h"

class WeaponInfoBar : public Observer, public AnimationBar
{
public:
	WeaponInfoBar(Ship *observable, int x, int y, int border_color = 0x00e000, 
					std::string text = "", int text_color = 0xe000e0);

	~WeaponInfoBar();


	// Update: called by the object being observed to indicate a change that requires observing	//
	virtual void ObserverUpdate(Observable&);


protected:
	Weapon* m_selected_weapon;
	Weapon* m_current_primary;
	Weapon* m_current_secondary;
	
	AnimationBar m_primary_bar;
	AnimationBar m_secondary_bar;
	AnimationBar m_selected_bar;
};

#endif



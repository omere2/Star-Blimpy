#include "weapon_bar.h"
#include "AnimationFactory.h"

WeaponInfoBar::WeaponInfoBar(Ship *observable, int x, int y, int border_color,
							 std::string text, int text_color):
	Observer(OBSERVE_WEAPONS),
	AnimationBar(x, y, 80, 90, 0xff00ff, text, text_color),
	m_primary_bar(5, 5, 30, 30, border_color, "P", text_color),
	m_secondary_bar(45,5, 30, 30, border_color, "S", text_color),
	m_selected_bar(25, 50, 30, 30, border_color, "I", text_color)
{
	// Add the bars	to m_animation	//
	m_animation->AddAnimation(m_primary_bar,5,5);
	m_animation->AddAnimation(m_secondary_bar,45,5);
	m_animation->AddAnimation(m_selected_bar,25,50);

	if (m_optimized_observable != NO_OBSERVABLE)
	{
		AddObservable(*observable);
		(observable)->AddObserver(*this);
		m_selected_weapon = ((Ship*)observable)->GetWeapon(Ship::SELECTED_WEAPON);
		m_current_primary = ((Ship*)observable)->GetWeapon(Ship::PRIMARY_WEAPON);
		m_current_secondary = ((Ship*)observable)->GetWeapon(Ship::SECONDARY_WEAPON);
	}
	else
	{
		m_selected_weapon = NO_WEAPON;
		m_current_primary = NO_WEAPON;
		m_current_secondary = NO_WEAPON;
	}

	m_primary_bar.Update(*(new CompositeAnimation(m_current_primary->GetInventoryAnimation())));
	m_secondary_bar.Update(*(new CompositeAnimation(m_current_secondary->GetInventoryAnimation())));
	m_selected_bar.Update(*(new CompositeAnimation(m_selected_weapon->GetInventoryAnimation())));
}


WeaponInfoBar::~WeaponInfoBar()
{
}


void WeaponInfoBar::ObserverUpdate(Observable& observable)
{
	if (m_optimized_observable != NULL)
	{
		Weapon* selected_weapon = ((Ship*)m_optimized_observable)->GetWeapon(Ship::SELECTED_WEAPON);
		Weapon* current_primary = ((Ship*)m_optimized_observable)->GetWeapon(Ship::PRIMARY_WEAPON);
		Weapon* current_secondary = ((Ship*)m_optimized_observable)->GetWeapon(Ship::SECONDARY_WEAPON);

		// update weapons that were changed	//
		if (current_primary != m_current_primary)
		{
			m_current_primary = current_primary;
			m_primary_bar.Update(*(new CompositeAnimation(m_current_primary->GetInventoryAnimation())));
		}
		if (current_secondary != m_current_secondary)
		{
			m_current_secondary = current_secondary;
			m_secondary_bar.Update(*(new CompositeAnimation(m_current_secondary->GetInventoryAnimation())));
		}
		if (selected_weapon != m_selected_weapon)
		{
			m_selected_weapon = selected_weapon;
			m_selected_bar.Update(*(new CompositeAnimation(m_selected_weapon->GetInventoryAnimation())));
		}
	}
}
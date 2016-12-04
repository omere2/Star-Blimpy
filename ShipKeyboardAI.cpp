#include "ShipKeyboardAI.h"

ShipKeyboardAI::ShipKeyboardAI(const game_keys keys):
	KeyboardAI(keys)
{
}

ShipKeyboardAI::~ShipKeyboardAI()
{
}

void ShipKeyboardAI::UpdateEntity(DynamicEntity *ship, scalar time_delta)
{
	KeyboardAI::UpdateEntity(ship, time_delta);
	if (key[m_keys.fire_primary])
	{
//    MessageBox(NULL, "Fire Primary", "ShipKeyboardAI::UpdateEntity", MB_OK);
		((Ship *)ship)->Fire(Ship::PRIMARY_WEAPON);
	}
	else if (key[m_keys.fire_secondary])
	{
//    MessageBox(NULL, "Fire Secondary", "ShipKeyboardAI::UpdateEntity", MB_OK);
		((Ship *)ship)->Fire(Ship::SECONDARY_WEAPON);
	}
	else if (key[m_keys.toggle_weapon])
	{
//    MessageBox(NULL, "Toggle", "ShipKeyboardAI::UpdateEntity", MB_OK);
		((Ship *)ship)->ToggleWeapon();
	}
	else if (key[m_keys.set_weapon_primary])
	{
//    MessageBox(NULL, "Set Primary", "ShipKeyboardAI::UpdateEntity", MB_OK);
		((Ship *)ship)->changeWeapon(Ship::PRIMARY_WEAPON);
	}
	else if (key[m_keys.set_weapon_secondary])
	{
//    MessageBox(NULL, "Set Secondary", "ShipKeyboardAI::UpdateEntity", MB_OK);
		((Ship *)ship)->changeWeapon(Ship::SECONDARY_WEAPON);
	}

}
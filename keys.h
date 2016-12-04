#ifndef __KEYS_H__
#define __KEYS_H__

const char NO_KEY = 0;

struct game_keys
{
	char accelerate;
	char left;
	char right;
	char fire_primary;
	char fire_secondary;
	char toggle_weapon;
	char set_weapon_primary;
	char set_weapon_secondary;
	char toggle_target;
	game_keys(	char _accelerate = NO_KEY, char _left = NO_KEY, char _right = NO_KEY, 
				char _fire_primary = NO_KEY, char _fire_secondary = NO_KEY, 
				char _toggle_weapon = NO_KEY, 
				char _set_weapon_primary = NO_KEY, char _set_weapon_secondary = NO_KEY,
				char _toggle_target = NO_KEY)
	{
		accelerate = _accelerate;
		left = _left;
		right = _right;
		fire_primary = _fire_primary;
		fire_secondary = _fire_secondary;
		toggle_weapon = _toggle_weapon;
		toggle_target = _toggle_target;
		set_weapon_primary = _set_weapon_primary;
		set_weapon_secondary = _set_weapon_secondary;
	};
};


static game_keys DEFAULT_KEYPAD(KEY_8_PAD, KEY_4_PAD, KEY_6_PAD,	// Forward, Left, Right			//
								KEY_0_PAD, KEY_DEL_PAD,				// Fire (primary, secondary)	//
								KEY_PLUS_PAD, KEY_1_PAD, KEY_3_PAD,	// Toggle and set weapons		//
								KEY_5_PAD);							// Toggle targets				//

#endif

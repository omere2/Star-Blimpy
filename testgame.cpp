//#include <allegro.h>
//#include <winalleg.h>
//#include <windows.h>
#include "common.h"

#include <stdio.h>
#include <vector>
#include "BaseException.h"
#include "Animation.h"
#include "CompositeAnimation.h"
#include "AnimationFactory.h"
#include "EntityFactory.h"
#include "EntityPool.h"
#include "GameEngine.h"
#include "missile.h"
#include "Ship.h"
#include "MissileLauncher.h"
#include "Gun.h"
#include "NullWeapon.h"

const int screenx = 1024;
const int screeny = 768;

void Initialize();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  
					LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;

	try {
		Initialize();

		hwnd = win_get_window();

		PreloadAnimations();

		NullWeapon null_weapon;
		NO_WEAPON = &null_weapon;
		


		EntityFactory* e_factory = EntityFactory::GetInstance();

		MissileLauncher* launcher = new MissileLauncher(NULL, 1000, MissileLauncher::MISSILE_NORMAL);
		MissileLauncher* launcher2 = new MissileLauncher(NULL, 3000, MissileLauncher::MISSILE_CRUISE);
		Gun* gun = new 	Gun(NULL, 300,0.3);

		Entity& enterprise = e_factory->CreateEntity(e_factory->E_USERSHIP1, vector_2D(750,550), 1);
		Entity& enterprise2 = e_factory->CreateEntity(e_factory->E_USERSHIP2, vector_2D(30,30), 1);
		Entity& star = e_factory->CreateEntity(e_factory->E_STAR, vector_2D(400,300), 0);
		Entity& mlauncher_carrier = *e_factory->CreateWeaponCarrier(vector_2D(200, 200), 0, vector_2D(), launcher);
		Entity& cmlauncher_carrier = *e_factory->CreateWeaponCarrier(vector_2D(200, 400), 0, vector_2D(), launcher2);
		Entity& gun_carrier2 = *e_factory->CreateWeaponCarrier(vector_2D(200, 300), 0, vector_2D(), gun);
		Entity& shield1 = *e_factory->CreateActiveShield(enterprise, 50);
		Entity& shield2 = *e_factory->CreateActiveShield(enterprise, 50, INFINITE_HEALTH, INFINITE_TTL, 400<<12);
		Entity& shield3 = *e_factory->CreateActiveShield(enterprise, 50, INFINITE_HEALTH, INFINITE_TTL, 800<<12);
		Entity& shield4 = *e_factory->CreateActiveShield(enterprise, 50, INFINITE_HEALTH, INFINITE_TTL, 1200<<12);
		Entity& shield5 = *e_factory->CreateActiveShield(enterprise, 50, INFINITE_HEALTH, INFINITE_TTL, 1600<<12);

		GameEngine::GetInstance()->RegisterEntity(enterprise);
		GameEngine::GetInstance()->RegisterEntity(enterprise2);
		GameEngine::GetInstance()->RegisterEntity(star);
		GameEngine::GetInstance()->RegisterEntity(mlauncher_carrier);
		GameEngine::GetInstance()->RegisterEntity(cmlauncher_carrier);
		GameEngine::GetInstance()->RegisterEntity(gun_carrier2);
		
		GameEngine::GetInstance()->RegisterEntity(shield1);
		GameEngine::GetInstance()->RegisterEntity(shield2);
		GameEngine::GetInstance()->RegisterEntity(shield3);
		GameEngine::GetInstance()->RegisterEntity(shield4);
		GameEngine::GetInstance()->RegisterEntity(shield5);
		
		GameEngine::GetInstance()->Run();
	}
	catch (BaseException& x)
	{
		MessageBox(hwnd, x.GetDescription().c_str(), "Exception occured", MB_OK);
	}
	catch (...)
	{
		MessageBox(hwnd, "Unhandled error!!!", "Panic!", MB_OK);
	}

	return 0;
}

void Initialize()
{
	
	allegro_init();
	set_color_depth(32);
//  if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screenx, screeny, 0, 0)!= 0)
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenx, screeny, 0, 0)!= 0)
		{
		throw BaseException("set_gfx_mode() failed");
	}
	if (install_keyboard() != 0)
	{
		throw BaseException("install_keyboard() failed");
	}
//	enable_triple_buffer();
}

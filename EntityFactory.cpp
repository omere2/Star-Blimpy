#include "EntityFactory.h"
#include "Engine.h"
#include "keys.h"
#include "Ship.h"
#include "ShipKeyboardAI.h"
#include "Missile.h"
#include "CruiseMissile.h"
#include "Star.h"
#include "Explosion.h"
#include "Shot.h"
#include "Gun.h"
#include "MissileLauncher.h"
#include "WeaponCarrier.h"
#include "health_infobar.h"
#include "weapon_bar.h"
#include "WorldView.h"
#include "GameEngine.h"
#include "ActiveShield.h"

extern std::vector<WorldView*> global_view;


EntityFactory EntityFactory::ms_instance;

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}


EntityFactory* EntityFactory::GetInstance()		
{
	return &ms_instance;
}

Entity& EntityFactory::CreateEntity(const unsigned short type, vector_2D position, fixed alpha, vector_2D velocity)
{
	// Create an empty entity
	Entity* ent = NULL;

	// check 
	switch (type)
	{
	case E_USERSHIP1:
		ent = CreateShip(position, alpha, velocity);
		break;
	case E_USERSHIP2:
		ent = CreateShip2(position, alpha, velocity);
		break;
	case E_SHOT:
		ent = CreateShot(position, alpha, velocity);
		break;
	case E_MISSILE:
		ent = CreateMissile(position, alpha, velocity);
		break;
	case E_STAR:
		ent = CreateStar(position, alpha);
		break;
	case E_EXPLOSION:
		ent = CreateExplosion(position, alpha, velocity);
		break;
	default:
		throw BaseException("EntityFactory() Failed: no such entity.");
		break;
	}

	// make sure we got ourselves an entity	//
	if (ent == NULL)
	{
		throw BaseException("EntityFactory() Failed: Could not create entity.");
	}

	// return it...	//
	return *ent;
}



Entity* EntityFactory::CreateShip(vector_2D position, fixed alpha, vector_2D velocity)
{
	// Load Animations	//
	Animation& FireAnimation = AnimationFactory("fire2");
	Animation& ShipAnimation = AnimationFactory("Chmmr");

	// Create CompositeAnimation	//
	CompositeAnimation* ShipCAnimation = new CompositeAnimation(20,20);

	// And add animations to it	//
	ShipCAnimation->AddAnimation(ShipAnimation, 0, 0 );
	int flame_handle = ShipCAnimation->AddAnimation(FireAnimation, -50, 3);
//	int flame_handle = ANIMATION_NO_HANDLE;

	// Create Keyboard Controller	//
	AI* ai = new ShipKeyboardAI(DEFAULT_KEYPAD);

	Engine ship_engine;
	ship_engine.setEngineAccelerationHandle(flame_handle);

	Ship* new_entity = new Ship(*ShipCAnimation, 100, 20, SHIP_DEFAULT_HEALTH, INFINITE_TTL, alpha, position,
		 velocity, ship_engine, *ai);

	new_entity->setName("Player 1");

	WeaponInfoBar* weapon_bar = new WeaponInfoBar(new_entity, 600, 50);
	weapon_bar->SetTransperancy(200,200,200,200);

	HealthInfoBar* 	health_bar = new HealthInfoBar(new_entity, 600,20, 80, 6, new_entity->getName());
	health_bar->SetTransperancy(128,128,128,128);

	GameEngine::GetInstance()->AddWidget(weapon_bar);
	GameEngine::GetInstance()->AddWidget(health_bar);

	global_view.push_back(new WorldView(0, 0, 0, 0, 800*1.2, 600*1.2));
//	new_entity->AddObserver(*global_view[0]);

	return new_entity;
}

Entity* EntityFactory::CreateShip2(vector_2D position, fixed alpha, vector_2D velocity)
{
	// Load Animations	//
	Animation& FireAnimation = AnimationFactory("fire2");
	Animation& ShipAnimation = AnimationFactory("tinyship");

	// Create CompositeAnimation	//
	CompositeAnimation ShipCAnimation(72,15);

	// And add animations to it	//
	ShipCAnimation.AddAnimation(ShipAnimation, 60, 2 );
	int flame_handle = ShipCAnimation.AddAnimation(FireAnimation, 4, 0);

	Engine ship_engine;
	ship_engine.setEngineAccelerationHandle(flame_handle);

	AI* ai = new ShipKeyboardAI(game_keys(KEY_W, KEY_A, KEY_D, KEY_TILDE, KEY_1));
	Ship* new_entity =  new Ship(ShipCAnimation, 100, 15, SHIP_DEFAULT_HEALTH, INFINITE_TTL, 
								alpha, position, velocity, ship_engine,
								*ai);

	new_entity->setName("Player 2");

	WeaponInfoBar* weapon_bar = new WeaponInfoBar(new_entity, 200, 50);
	weapon_bar->SetTransperancy(200,200,200,200);

	HealthInfoBar* 	health_bar = new HealthInfoBar(new_entity, 200,20, 80, 6, new_entity->getName());
	health_bar->SetTransperancy(128,128,128,128);

	GameEngine::GetInstance()->AddWidget(weapon_bar);
	GameEngine::GetInstance()->AddWidget(health_bar);

/*
	HealthInfoBar* 	health_bar = new HealthInfoBar(new_entity, 0,0, 20, 4, "");
	new_entity->AddObserver(*health_bar);

	new_entity->getCompositeAnimation().AddAnimation(*health_bar, -10, 20);
*/	
/*
	global_view.push_back(new WorldView(new_entity, 0, 0, 400, 600));
	new_entity->AddObserver(*global_view[1]);
*/
	return new_entity;
}

Entity* EntityFactory::CreateShot(vector_2D position, fixed alpha, vector_2D velocity, long ttl, scalar start_velocity)
{
	Animation& ShotAnimation = AnimationFactory("Shot");
	CompositeAnimation* ShotCAnimation = new CompositeAnimation(3,3);

	ShotCAnimation->AddAnimation(ShotAnimation, 0,0);

	velocity.x += fixtof(fixcos(alpha)) * start_velocity;
	velocity.y += fixtof(fixsin(alpha)) * start_velocity;

	return new Shot(*ShotCAnimation, 1, 3, ttl, alpha, position, velocity);
}


Entity* EntityFactory::CreateMissile(vector_2D position, fixed alpha, vector_2D velocity)
{
	// Load Animations	//
	Animation& FireAnimation = AnimationFactory("fire");
	Animation& MissileAnimation = AnimationFactory("Missile");

	// Create CompositeAnimation	//
	CompositeAnimation* MissileCAnimation = new CompositeAnimation(16,16);

	// And add animations to it	//
	MissileCAnimation->AddAnimation(MissileAnimation, 2, 2 );
	int flame_handle = MissileCAnimation->AddAnimation(FireAnimation, 0, 12);

	Engine missile_engine;
	/*
	missile_engine.setEngineAcceleration(0.0015);
	missile_engine.setEngineAccelerationHandle(flame_handle);
	missile_engine.setEngineFriction(0.9995);
	*/
	missile_engine.setEngineAcceleration(0.0003);
	missile_engine.setEngineAccelerationHandle(flame_handle);
	missile_engine.setEngineFriction(0.9995);
	AI* missile_ai = new KeyboardAI(game_keys(0, KEY_LEFT, KEY_RIGHT));

//	return new Missile(*MissileCAnimation, 100, 18, 3000, 4000, alpha, position, velocity, missile_engine, 400);
	return new CruiseMissile(*MissileCAnimation, 100, 18, 3000, 4000, alpha, position, velocity, missile_engine, *missile_ai, 3000);
}


Entity* EntityFactory::CreateStar(vector_2D position, fixed alpha)
{
	// Load Animations	//
	Animation& StarAnimation = AnimationFactory("Earth");

	// Create CompositeAnimation	//
	CompositeAnimation* StarCAnimation = new CompositeAnimation(40,40);

	// And add animations to it	//
	StarCAnimation->AddAnimation(StarAnimation, 0, 0);

	return new Star(*StarCAnimation, 100, 37, INFINITE_TTL, 
					alpha, position);
}

Entity* EntityFactory::CreateExplosion(vector_2D position, fixed alpha, vector_2D velocity)
{
	// Load Animations	//
	Animation& ExplosionAnimation = AnimationFactory("CoolExplode");

	// Create CompositeAnimation	//
	CompositeAnimation* ExplosionCAnimation = new CompositeAnimation(128,96);

	// And add animations to it	//
	ExplosionCAnimation->AddAnimation(ExplosionAnimation, 0, 0);

	return new Explosion(*ExplosionCAnimation, 100, 0, 650, alpha, position, velocity);
}


Entity* EntityFactory::CreateWeaponCarrier(vector_2D position, fixed alpha, vector_2D velocity, Weapon* weapon)
{
	return new WeaponCarrier(INFINITE_TTL, alpha, position, velocity, weapon);
}


Entity* EntityFactory::CreateActiveShield(Entity& protectee, scalar protectee_range, long health, DWORD ttl, fixed start_alpha)
{
	// Add active shield	//
	Animation& ShieldAnimation = AnimationFactory("ActiveShield");

	// Create CompositeAnimation	//
	CompositeAnimation* ShieldCAnimation = new CompositeAnimation(9,9);
	ShieldCAnimation->AddAnimation(ShieldAnimation, 0, 0 );
	ActiveShield* new_shield = new ActiveShield(*ShieldCAnimation, 10, health, ttl, 0, protectee, protectee_range, start_alpha);

	return new_shield;
}
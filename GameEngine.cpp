#include "GameEngine.h"
#include "callback.h"
#include "EntityFactory.h"
#include "DeathException.h"
#include "WorldView.h"
#include "allegro.h"
#include "NullWeapon.h"

//NullWeapon null_weapon;
Weapon temp_null_weapon(NULL, 1000000);
Weapon* NO_WEAPON = &temp_null_weapon;

std::vector<WorldView*> global_view;

GameEngine GameEngine::ms_instance;

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

GameEngine* GameEngine::GetInstance()
{
	return &ms_instance;
}


// RegisterEntity(): add an entity to the active entities pool	//
void GameEngine::RegisterEntity(Entity &entity)
{
	m_infants.RegisterEntity(entity);
}

void GameEngine::RegisterEntities()
{
	for (int i=0; i < m_infants.GetEntityCount(); i++)
	{
		m_epool.RegisterEntity(m_infants.GetEntity(i));
	}
	m_infants.Clear();
}

// DeRegisterEntity(): remove an entity from the active entities pool, and move it to the graveyard	//
void GameEngine::DeRegisterEntity(Entity &entity)
{
	m_graveyard.RegisterEntity(entity);
}

bool GameEngine::IsAlive(Entity &entity)
{
	return m_epool.HasEntity(entity);
}


BITMAP* GLOBAL_CURRENT_BITMAP;
int DEBUG_LINE_POS = 10;
// Main GameEngine loop	//
void GameEngine::Run()
{
	unsigned int current_buffer = 0;
	scalar time_passed = 0;
	DWORD last_iteration_tickcount = GetTickCount();
	DWORD s_time = GetTickCount();

	int frames = 0;
	float fps = 0;

	// Create Video buffers	//
	BITMAP* video_maps[VIDEO_BUFFERS];
	BITMAP* memory_maps[VIDEO_BUFFERS];
	for (int i=0; i < VIDEO_BUFFERS; i++)
	{
		video_maps[i] = create_video_bitmap(screenx,screeny);
		memory_maps[i] = create_bitmap(screenx*2, screeny*2);
	}

	while (!key[KEY_ESC])
	{
		BITMAP* screen_bitmap = video_maps[current_buffer%VIDEO_BUFFERS];
		BITMAP* memory_bitmap = memory_maps[current_buffer%VIDEO_BUFFERS];
		clear_to_color(memory_bitmap, 0xff00ff);
		clear_bitmap(screen_bitmap);

		GLOBAL_CURRENT_BITMAP = screen_bitmap; // for DEBUG purposes

		DWORD tick_count = GetTickCount();
		time_passed = ((float)tick_count - last_iteration_tickcount);
		last_iteration_tickcount = tick_count;

		// check for callbacks before starting iteration
		Callback::GetInstance()->CheckForCallback();

		int i;
		// draw entities
		for (i=0; i < m_epool.GetEntityCount(); i++)
		{
			Entity& temp_entity = m_epool.GetEntity(i);
			for (int view = 0; view < global_view.size(); view++)
			{
//				rect(memory_bitmap, global_view[view]->getDrawPosX(), global_view[view]->getDrawPosY(), 
//					global_view[view]->getWidth(), global_view[view]->getHeight(), 0xff00ff);
				if (global_view[view]->InView(temp_entity.getX(), temp_entity.getY()))
				{
					temp_entity.Draw(memory_bitmap, global_view[view]->getDrawPosX()+temp_entity.getX()-global_view[view]->getX(), global_view[view]->getDrawPosY()+temp_entity.getY()-global_view[view]->getY());
				}
			}
		}

		// iterate entities
		for (i=0; i < m_epool.GetEntityCount(); i++)
		{
			Entity& temp_entity = m_epool.GetEntity(i);
			temp_entity.Iterate(time_passed);
		}

		// Check for collisions between entities
		CollisionDetection();

//		stretch_blit(screen_bitmap, temp_bitmap, 0, 0, src_width, src_height, 0, 0, dst_width, dst_height);

//		_blit(memory_bitmap, screen_bitmap, 0, 0, 0, 0, screenx, screeny);

//		stretch_sprite(screen_bitmap, memory_bitmap, 0, 0, screenx, screeny);

		masked_stretch_blit(memory_bitmap, screen_bitmap, 0, 0, screenx*1, screeny*1, 0, 0, screenx, screeny);
		
		// draw widgets on screen, such as health bar
		DrawWidgets(screen_bitmap);


		// DEBUG //
		char s[100];
		sprintf(s, "Entities#: %d", m_epool.GetEntityCount());
		textout(screen_bitmap, font, s, 10,DEBUG_LINE_POS,0xff00ff);
		DEBUG_LINE_POS += 20;

		fps = (float)frames*1000/(GetTickCount()-s_time);
		sprintf(s, "fps: %.0f", fps);
		textout(screen_bitmap, font, s, 10,DEBUG_LINE_POS,0xff00ff);
		DEBUG_LINE_POS += 20;	
		// DEBUG //


		show_video_bitmap(screen_bitmap);
		current_buffer++;
		
		// Deregister and cleanup entities that have just died during the last iteration
		CleanGraveYard();

		// Register newly created entites into the main pool
		RegisterEntities();

		DEBUG_LINE_POS = 10;
		frames++;	
	}

	return;
}


void GameEngine::CleanGraveYard()
{
	// go over all the corpses in the graveyard and get rid of them	//
	for (unsigned int i=0; i < m_graveyard.GetEntityCount(); i++)
	{
		Entity& temp_entity = m_graveyard.GetEntity(i);
		m_epool.DeRegisterEntity(temp_entity);
		
		delete(&temp_entity);
	}
	
	// burn all the corpses	//	
	m_graveyard.Clear();
}

void GameEngine::CollisionDetection()
{
	for (int i=0; i < m_epool.GetEntityCount(); i++)
	{
		for (int j=i+1; j < m_epool.GetEntityCount(); j++)
		{
			Entity& e1 = m_epool.GetEntity(i);
			Entity& e2 = m_epool.GetEntity(j);
			if (isCollision(e1, e2))
			{
 				e1.Collide(e2);
				e2.Collide(e1);
			}
		}

	}
}

bool GameEngine::isCollision(const Entity& e1, const Entity& e2) const
{
	vector_2D pos_e1 = e1.getPosition();
	vector_2D pos_e2 = e2.getPosition();

	// if entity has radius 0 then no collision will occur anyway
	if (e1.getRadius() * e2.getRadius() == 0)
	{
		return false;
	}
	
	//rect(GLOBAL_CURRENT_BITMAP, e1.getX(), e1.getY(), e1.getX()+e1.getWidth(), e1.getY()+e1.getHeight(), 0xff00ff);
	//rect(GLOBAL_CURRENT_BITMAP, e2.getX(), e2.getY(), e2.getX()+e2.getWidth(), e2.getY()+e2.getHeight(), 0xff00ff);
/*
	circle(GLOBAL_CURRENT_BITMAP, e1.getX()-global_view->getX(), e1.getY()-global_view->getY(), e1.getRadius(), 0xff00ff);
	circle(GLOBAL_CURRENT_BITMAP, e2.getX()-global_view->getX(), e2.getY()-global_view->getY(), e2.getRadius(), 0xff00ff);
	line(GLOBAL_CURRENT_BITMAP, e1.getX()-global_view->getX()-3, e1.getY()-global_view->getY(), e1.getX()-global_view->getX()+3, e1.getY()-global_view->getY(), 0xff0000);
	line(GLOBAL_CURRENT_BITMAP, e1.getX()-global_view->getX(), e1.getY()-global_view->getY()-3, e1.getX()-global_view->getX(), e1.getY()-global_view->getY()+3, 0xff0000);
	line(GLOBAL_CURRENT_BITMAP, e2.getX()-global_view->getX()-3, e2.getY()-global_view->getY(), e2.getX()-global_view->getX()+3, e2.getY()-global_view->getY(), 0xff0000);
	line(GLOBAL_CURRENT_BITMAP, e2.getX()-global_view->getX(), e2.getY()-global_view->getY()-3, e2.getX()-global_view->getX(), e2.getY()-global_view->getY()+3, 0xff0000);
*/

	scalar dx = pos_e1.x-pos_e2.x;
	scalar dy = pos_e1.y-pos_e2.y;
	scalar d = dx*dx + dy*dy;

	scalar radius = e1.getRadius()+e2.getRadius();
	if (d < radius*radius)
	{
		return true;
	}

	return false;



	return true;
}


void GameEngine::AddWidget(Drawable* widget)
{
	m_widgets.push_back(widget);
}

void GameEngine::DrawWidgets(BITMAP* dest)
{
	std::vector<Drawable*>::iterator i;

	for (i = m_widgets.begin(); i < m_widgets.end(); i++)
	{
		(*i)->Draw(dest);
	}
}



std::vector<Entity*> GameEngine::GetEntitiesInRadius(vector_2D center, scalar radius, bool exclude_self)
{
	std::vector<Entity*> entities;

	// iterate entities
	for (int i=0; i < m_epool.GetEntityCount(); i++)
	{
		Entity& temp_entity = m_epool.GetEntity(i);
		vector_2D position = temp_entity.getPosition();
		scalar dx = center.x - position.x;
		scalar dy = center.y - position.y;

		// if not self, or not excluding self	//
		if ((!exclude_self) || ((dx) && (dy)))
		{
			// if the distance between the points is smaller then the radius	// 
			if (((dx*dx) + (dy*dy)) <= radius*radius)
			{
				entities.push_back(&temp_entity);
			}
		}
	}

	// return the vector	//
	return entities;
}



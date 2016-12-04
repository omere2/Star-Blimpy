#include "health_infobar.h"
#include "baseexception.h"

HealthInfoBar::HealthInfoBar(Entity* observed_entity,
		int x, int y, int width, int height,
		std::string text, 
		int text_color, int fill_color, int border_color):
		Observer(OBSERVE_HEALTH),
		InfoBar(x, y, width, height, 0, text, text_color, fill_color, border_color)
{
	if (observed_entity == NULL)
	{
		throw BaseException("call HealthInfoBar constructor with NULL parameter!");
	}
	else
	{
		AddObservable(*observed_entity);
		observed_entity->AddObserver(*this);
	}
	m_capacity = observed_entity->getHealth();
	m_progress = m_capacity;
}

HealthInfoBar::~HealthInfoBar()
{
}

void HealthInfoBar::ObserverUpdate(Observable& observable)
{
	if (m_optimized_observable != NULL)
	{
		InfoBar::Update(((Entity*)m_optimized_observable)->getHealth());
	}
	else
	{
		InfoBar::Update(0);
	}
}

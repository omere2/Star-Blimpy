#include "KeyboardAI.h"


KeyboardAI::KeyboardAI(const game_keys keys):
	m_keys(keys)
{
}

KeyboardAI::~KeyboardAI()
{
}

void KeyboardAI::UpdateEntity(DynamicEntity *entity, scalar time_delta)
{
	if (m_keys.accelerate != 0)
	{
		if (key[m_keys.accelerate])
		{
			entity->SetAcceleration(entity->getEngineAcceleration());
		}
		else
		{
			entity->SetAcceleration(0);
		}
	}
	else
	{
		entity->SetAcceleration(entity->getEngineAcceleration());
	}

	if (key[m_keys.right])
	{
		entity->ChangeAngle((entity->getEngineRotateVelocity()*(DWORD)time_delta)<<12);
	}
	if (key[m_keys.left])
	{
		entity->ChangeAngle(((-1)*entity->getEngineRotateVelocity()*(DWORD)time_delta)<<12);
	}
}

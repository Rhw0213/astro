#include "BulletSystem.h"
#include "Component.h"
#include "Setting.h"

namespace astro
{
	void BulletSystem::Init()
	{
		auto& setting = GameSettingManager::Instance();
		int playerBulletCount = 0;

		for (const auto& bullet : objects)
		{
			if (bullet && bullet.get()->IsEnable())
			{
				auto* bulletComponent = bullet.get()->GetComponent<BulletComponent>(ComponentType::BULLET_COMPONENT);
				InstanceID& bulletOwner = bulletComponent->bulletOwner;



				bullet.get()->SetEnable(false);
			}
		}

	}

	void BulletSystem::Process()
	{
	}
}

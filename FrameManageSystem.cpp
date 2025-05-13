#include "FrameManageSystem.h"
#include <iostream>
#include "Setting.h"
#include "Utility.h"
#include "EventManager.h"
#include "Event.h"

namespace astro
{
	FrameManageSystem::FrameManageSystem(std::shared_ptr<ObjectManager> objectManager)
		: objectManager(objectManager)
	{
	}

	void FrameManageSystem::Init()
	{
	}

	void FrameManageSystem::Process()
	{
		auto& setting = GameSettingManager::Instance();
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(static_cast<uint64_t>(ComponentType::FRAME_MANAGE_COMPONENT));

		for (auto& archetype : archetypes)
		{
			auto* frameManageComponents = archetype->GetComponents<FrameManageComponent>();

			if (frameManageComponents)
			{ 
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					auto& frameManageComponent = frameManageComponents[i];

					auto& trigerTime	= frameManageComponent.trigerTime;
					auto& frameNowIndex	= frameManageComponent.frameNowIndex;
					auto& frameMaxIndex	= frameManageComponent.frameMaxIndex;
					auto& trigerMaxTime = setting.frameEnableTrigerMaxTime;

					trigerTime += GetFrameTime();

					if (trigerTime >= trigerMaxTime)
					{
						trigerTime = 0;
						frameNowIndex++;

						if (frameNowIndex >= frameMaxIndex)
						{
							frameNowIndex = 0;
						}
					}
				}
			}
		}
	}
}

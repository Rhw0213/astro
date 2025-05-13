#include "MissileSystem.h"
#include "Component.h"
#include "Setting.h"
#include "EventManager.h"

namespace astro
{
	MissileSystem::MissileSystem(std::shared_ptr<ObjectManager> objectManager)
		: objectManager(objectManager)
	{
	}
	
	void MissileSystem::Init()
	{
		auto& setting = GameSettingManager::Instance();
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::MISSILE_COMPONENT) |
			static_cast<uint64_t>(ComponentType::ACTIVE_COMPONENT)
		);

		for (auto& archetype : archetypes)
		{
			auto* activeComponents = archetype->GetComponents<ActiveComponent>();
			auto* missileComponents = archetype->GetComponents<MissileComponent>();

			if (missileComponents && activeComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					bool& enable = activeComponents[i].enable;

					EventManager::Instance().RegisterEvent<MissileFireEvent>([&enable](const MissileFireEvent* e) {
						enable = true;
					});
				}
			}
		}
	}

	void MissileSystem::Process()
	{
		auto& setting = GameSettingManager::Instance();
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::MISSILE_COMPONENT |
									ComponentType::ACTIVE_COMPONENT |
									ComponentType::TRANSFORM_COMPONENT) 
		);

		for (auto& archetype : archetypes)
		{
			auto* activeComponents = archetype->GetComponents<ActiveComponent>();
			auto* missileComponents = archetype->GetComponents<MissileComponent>();
			auto* transformComponents = archetype->GetComponents<TransformComponent>();

			if (missileComponents && activeComponents && transformComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					auto& activeComponent = activeComponents[i];
					auto& missileComponent = missileComponents[i];
					auto& transformComponent = transformComponents[i];

					if (activeComponent.enable)
					{
						auto missileOwner = objectManager->GetObject(missileComponent.missileOwner);

						if (missileOwner->GetType() == ObjectType::PLAYER_ID)
						{
							auto* ownerTransformComponent = CM.GetComponent<TransformComponent>(missileOwner->GetComponentMask(), missileOwner->GetInstanceID());
							
							transformComponent.localPosition = ownerTransformComponent->localPosition;
							transformComponent.localRotation = ownerTransformComponent->localRotation;
						}
					}
				}
			}
		}
	}
}

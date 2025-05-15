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
									ComponentType::TRANSFORM_COMPONENT |
									ComponentType::MOVE_COMPONENT) 
		);

		for (auto& archetype : archetypes)
		{
			auto* activeComponents = archetype->GetComponents<ActiveComponent>();
			auto* missileComponents = archetype->GetComponents<MissileComponent>();
			auto* transformComponents = archetype->GetComponents<TransformComponent>();
			auto* moveComponents = archetype->GetComponents<MoveComponent>();

			if (missileComponents && activeComponents && transformComponents && moveComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					auto& activeComponent = activeComponents[i];
					auto& missileComponent = missileComponents[i];
					auto& transformComponent = transformComponents[i];
					auto& moveComponent = moveComponents[i];

					if (activeComponent.enable)
					{
						auto missileOwner = objectManager->GetObject(missileComponent.missileOwner);

						auto* ownerTransformComponent = CM.GetComponent<TransformComponent>(missileOwner->GetComponentMask(), missileOwner->GetInstanceID());
						auto* ownerMoveComponent = CM.GetComponent<MoveComponent>(missileOwner->GetComponentMask(), missileOwner->GetInstanceID());

						if (missileOwner->GetType() == ObjectType::PLAYER_ID && !missileComponent.firstFire && !missileComponent.secondFire)
						{
							transformComponent.localPosition = ownerTransformComponent->localPosition;
							transformComponent.localRotation = ownerTransformComponent->localRotation;
							float randomRadian	= Angle::DregreeToRadian(Random::missileRange(Random::gen));

							Angle angle = transformComponent.localRotation;
							angle.radian += randomRadian;
							moveComponent.direction = {cosf(angle.radian), sinf(angle.radian)};
							moveComponent.speed = 500.f + ownerMoveComponent->speed;
							missileComponent.firstFire = true;
						}

						if (missileComponent.firstFire)
						{
							moveComponent.speed *= 0.8f;
							if (moveComponent.speed <= 100.f)
							{
								Angle ownerAngle = ownerTransformComponent->localRotation;
								MyVector2 ownerPosition = ownerTransformComponent->localPosition;

								MyVector2 target = MyVector2{ cosf(ownerAngle.radian), sinf(ownerAngle.radian) }.Normalize();
								MyVector2 direction = moveComponent.direction.Normalize();

								MyVector2 force = target - direction;
								moveComponent.force = force.Normalize();

								std::cout << force.x() << ", " << force.y() << std::endl;
								missileComponent.firstFire = false;
								missileComponent.secondFire = true;
								EventManager::Instance().RunEvent<MissileFireEvent>(MissileFireEvent(missileComponent.missileOwner));
							}
						}

						if (missileComponent.secondFire)
						{
							MyVector2& force = moveComponent.force;
							force += (force * GetFrameTime());
							moveComponent.speed += 5.f;
						}
					}
				}
			}
		}
	}
}

#include "MoveSystem.h"
#include "ComponentManager.h"

namespace astro
{
	void MoveSystem::Init()
	{
	}

	void MoveSystem::Process()
	{
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::TRANSFORM_COMPONENT |
									ComponentType::MOVE_COMPONENT)
		);

		for (auto& archetype : archetypes)
		{
			auto* transformComponents = archetype->GetComponents<TransformComponent>();
			auto* moveComponents = archetype->GetComponents<MoveComponent>();

			if (transformComponents && moveComponents)
			{ 
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					auto& transformComponent	= transformComponents[i];
					auto& moveComponent			= moveComponents[i];

					MyVector2&			localPosition	= transformComponent.localPosition;
					const MyVector2&	moveDirection	= moveComponent.direction.Normalize();
					const float&		speed			= moveComponent.speed;
					MyVector2&			force			= moveComponent.force;
					MyVector2			velocity		= moveDirection * speed * GetFrameTime();

					localPosition += velocity;
					localPosition += force;
					//localPosition += {0, 1};
				}
			}
		}
	}
}

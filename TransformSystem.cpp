#include "TransformSystem.h"
#include "ComponentManager.h"
#include "Component.h"
#include "ObjectManager.h"
#include <vector>
#include <cmath>

namespace astro
{
	TransformSystem::TransformSystem(std::shared_ptr<ObjectManager> objectManager)
		: objectManager(objectManager), frameNumber(0)
	{
	}

	void TransformSystem::Init()
	{
	}

	void TransformSystem::Process()
	{
		frameNumber++;

		if (frameNumber >= INT_MAX)
		{
			frameNumber = 0;
		}

		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::ACTIVE_COMPONENT | 
									ComponentType::TRANSFORM_COMPONENT)
		);

		for (auto* archetype : archetypes)
		{ 
			auto* activeComponents = archetype->GetComponents<ActiveComponent>();
			auto* transformComponents = archetype->GetComponents<TransformComponent>();

			if (activeComponents && transformComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					auto& enable = activeComponents[i].enable;
					auto& transformComponent = transformComponents[i];

				    if (enable)
				    { 
				    	UpdateParentWorld(transformComponent);
				    }
				}
			}
		}
	}

	void TransformSystem::UpdateParentWorld(TransformComponent& transformComponent)
	{
		auto& CM = ComponentManager::Instance();

		if (transformComponent.frameUpdateNumber == frameNumber)
		{
			return;
		}

		transformComponent.frameUpdateNumber = frameNumber;

		InstanceID	parentId		= transformComponent.parentId;
		MyVector2&	worldPosition	= transformComponent.worldPosition;
		Angle&		worldRotation	= transformComponent.worldRotation;
		float&		worldScale		= transformComponent.worldScale;
		MyVector2&	localPosition	= transformComponent.localPosition;
		Angle&		localRotation	= transformComponent.localRotation;
		float&		localScale		= transformComponent.localScale;

		if (parentId == 0)
		{
			worldPosition = localPosition;
			worldRotation = localRotation;
			worldScale = localScale;
			return;
		}

		auto* parentTransformComponent = CM.GetComponent<TransformComponent>(
			static_cast<uint64_t>(ComponentType::TRANSFORM_COMPONENT), parentId);

		if (parentTransformComponent)
		{ 
			UpdateParentWorld(*parentTransformComponent);

			const MyVector2& parentWorldPosition = parentTransformComponent->worldPosition;
			const Angle& parentWorldRotation = parentTransformComponent->worldRotation;
			const float parentWorldScale = parentTransformComponent->worldScale;

			worldRotation.radian = parentWorldRotation.radian + localRotation.radian;
			worldScale = parentWorldScale * localScale;

			//float cosValue = cosf(parentWorldRotation.radian);
			//float sinValue = sinf(parentWorldRotation.radian);

			MyVector2 scaledLocalPos = localPosition * parentWorldScale;

			//float rotatedX = scaledLocalPos.x() * cosValue - scaledLocalPos.y() * sinValue;
			//float rotatedY = scaledLocalPos.x() * sinValue + scaledLocalPos.y() * cosValue;

			//worldPosition = parentWorldPosition + MyVector2{ rotatedX, rotatedY };
			worldPosition = parentWorldPosition + scaledLocalPos.Rotate(parentWorldRotation);
		}
		else
		{
			worldPosition = localPosition;
			worldRotation = localRotation;
			worldScale = localScale;
		}
	}
}

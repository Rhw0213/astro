#include "FrameSystem.h"
#include <iostream>
#include "Setting.h"
#include "Utility.h"
#include "EventManager.h"
#include "Event.h"

namespace astro
{
	FrameSystem::FrameSystem(std::shared_ptr<ObjectManager> objectManager)
		: objectManager(objectManager)
	{
	}

	void FrameSystem::Init()
	{
		auto& setting = GameSettingManager::Instance();

		for (const auto& object : objects)
		{
			if (object)
			{
				auto* frameComponent		= object.get()->GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);
				auto* transformComponent	= object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
				auto* rotationComponent		= object.get()->GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);
				auto* moveComponent			= object.get()->GetComponent<MoveComponent>(ComponentType::MOVE_COMPONENT);
				auto* renderComponent		= object.get()->GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);

				//target
				auto targetObject				= objectManager->GetObject(frameComponent->target);
				auto* targetTransformComponent	= targetObject->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

				MyVector2& direction			= transformComponent->direction;
				float& frameSpeed				= frameComponent->speed;
				float& time						= frameComponent->time;
				float& moveSpeed				= moveComponent->speed;
				float& size						= transformComponent->size;
				Angle& angle					= rotationComponent->angle;
				const MyVector2& targetPosition = targetTransformComponent->position;
				MyVector2& framePosition		= transformComponent->position;
				auto& renderPoints				= renderComponent->points;
				float& increaseSizeOffset		= frameComponent->increaseSizeOffset;

				direction				= targetTransformComponent->direction * -1.f;
				angle.radian			= atan2f(direction.y() , direction.x());
				framePosition			= targetPosition;
				moveSpeed				= 0.f;
				time					= 0.f;
				renderPoints[0]			= framePosition;
				frameSpeed				= setting.frameSpeed;
				increaseSizeOffset		= setting.frameIncreaseFrameDefaultSize;

				if (targetObject->GetType() == ObjectType::PLAYER_ID)
				{
					size = setting.framePlayerSize;
				}

				object.get()->SetEnable(false);

				EventManager::Instance().RegisterEvent<WarpStartEvent>([&increaseSizeOffset](const WarpStartEvent* e) {
					increaseSizeOffset = e->increaseFrameSizeOffset ;
				});

				EventManager::Instance().RegisterEvent<WarpStopEvent>([&increaseSizeOffset](const WarpStopEvent* e) {
					increaseSizeOffset = e->increaseFrameSizeOffset ;
				});
			}
		}
	}

	void FrameSystem::Process()
	{
		auto& setting = GameSettingManager::Instance();

		for (auto& object : objects)
		{
			if (object && object.get()->IsEnable())
			{
				auto* frameComponent			= object.get()->GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);
				auto* renderComponent			= object.get()->GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);
				auto* frameTransformComponent	= object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
				auto* moveComponent				= object.get()->GetComponent<MoveComponent>(ComponentType::MOVE_COMPONENT);
				auto targetObject				= objectManager->GetObject(frameComponent->target);
				auto* targetTransformComponent	= targetObject->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

				MyVector2&		 frameDirection			= frameTransformComponent->direction;
				float&			 size					= frameTransformComponent->size;
				MyVector2&		 moveDirection			= moveComponent->direction;
				MyVector2&		 position				= frameTransformComponent->position;
				float&			 moveSpeed				= moveComponent->speed;
				const MyVector2& targetDirection		= targetTransformComponent->direction;
				MyVector2		 targetPosition			= targetTransformComponent->position;
				const float&	 frameSpeed				= frameComponent->speed;
				float&			 rotationDirection		= frameComponent->rotationDirection;
				float&			 increaseSizeOffset		= frameComponent->increaseSizeOffset;
				auto&			 renderPoints			= renderComponent->points;
				float&			 time					= frameComponent->time;

				time += GetFrameTime();

				if (time > setting.frameLifeTime)
				{
					time = 0.f;
					object.get()->SetEnable(false);
				}

				float targetRadian = atan2f(targetDirection.y(), targetDirection.x());
				float randomRadian = Angle::DregreeToRadian(Random::distributionFrameRange(Random::gen));

				rotationDirection = randomRadian;
				targetRadian += randomRadian;

				moveDirection = { -cosf(targetRadian), -sinf(targetRadian) };
				frameDirection = { -cosf(targetRadian), -sinf(targetRadian) };

				renderPoints[0] = position;
				size += GetFrameTime() * increaseSizeOffset;
			}
		}
	}
}

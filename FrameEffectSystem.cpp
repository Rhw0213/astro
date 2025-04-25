#include "FrameEffectSystem.h"
#include "Component.h"
#include "Object.h"
#include "Utility.h"
#include "Setting.h"
#include <iostream> 

namespace astro
{
	using ObjectVector = std::vector<std::shared_ptr<Object>>;

	void FrameEffectSystem::Init()
	{
		for (const auto& object : objects)
		{
			auto* frameEffectComponent = object.get()->GetComponent<FrameEffectComponent>(ComponentType::FRAME_EFFECT_COMPONENT);

			if (frameEffectComponent)
			{
				const ObjectType&	frameOfObjectType	= frameEffectComponent->frameOfObjectType;
				ObjectVector&		frameEffectObjects	= frameEffectComponent->frames;
				float&				enableTrigerTime	= frameEffectComponent->enableTrigerTime;
				ObjectVector		allFrames			= objectManager.get()->GetObjects(ObjectType::FRAME_ID);

				enableTrigerTime = static_cast<float>(INT_MAX);

				for (const auto& frame : allFrames)
				{
					auto*		frameComponent		= frame.get()->GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);
					InstanceID	targetID			= frameComponent->target;
					auto		targetObject		= objectManager.get()->GetObject(targetID);

					if (targetObject.get()->GetType() == frameOfObjectType)
					{
						frameEffectObjects.push_back(frame);
					}
				}

				size_t frameSize = frameEffectObjects.size();

				for (size_t i = 0; i < frameSize; i++)
				{
					auto* frameComponent = frameEffectObjects[i].get()->GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);

					Color& color = frameComponent->color;

					//std::vector<Color> colors { 
					//	{ 255, 255, 220, 200 },
					//	{ 255, 255, 0, 180 },
					//	{ 255, 200, 0, 150 },
					//	{ 255, 130, 0, 120 },
					//	{ 255, 60, 0, 90 },
					//	{ 255, 0, 0, 60 }
					//};

					std::vector<Color> colors { 
						{ 255, 0, 0, 200 },
						{ 255, 127, 0, 200 },
						{ 255, 255, 0, 200 },
						{ 0, 255, 0, 200},
						{ 0, 0, 255, 200 },
						{ 75, 0, 130, 200 },
						{ 148, 0, 211, 200 },
					};

					//color = colors[Random::randColor(Random::gen)];
					color = { 255, 255, 255, 200};
				}
			}
		}
	}

	void FrameEffectSystem::Process()
	{
		auto& setting = GameSettingManager::Instance();

		for (const auto& object : objects)
		{
			if (object && object.get()->IsEnable())
			{
				auto* frameEffectComponent	= object.get()->GetComponent<FrameEffectComponent>(ComponentType::FRAME_EFFECT_COMPONENT);

				const ObjectType	frameOfObjectType	= frameEffectComponent->frameOfObjectType;
				auto&				frames				= frameEffectComponent->frames;

				if (frameEffectComponent)
				{
					float&			enableTrigerTime	= frameEffectComponent->enableTrigerTime;
					int&			frameNowIndex		= frameEffectComponent->frameNowIndex;
					ObjectVector&	frames				= frameEffectComponent->frames;
					size_t			framesSize			= frames.size();

					auto* frameComponent			= frames[frameNowIndex].get()->GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);
					auto* moveComponent				= frames[frameNowIndex].get()->GetComponent<MoveComponent>(ComponentType::MOVE_COMPONENT);
					auto* frameTransformComponent	= frames[frameNowIndex].get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
					auto* renderComponent			= frames[frameNowIndex].get()->GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);

					InstanceID	targetId			= frameComponent->target;
					auto		targetObject		= objectManager.get()->GetObject(targetId);

					auto* targetTransformComponent  = targetObject.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

					float&		rotationDirection	= frameComponent->rotationDirection;
					MyVector2&	moveDirection		= moveComponent->direction;
					float		moveSpeed			= moveComponent->speed;
					float		frameSpeed			= frameComponent->speed;
					MyVector2&	framePosition		= frameTransformComponent->position;
					float&		size				= frameTransformComponent->size;
					MyVector2	targetPosition		= targetTransformComponent->position;
					MyVector2	targetDirection		= targetTransformComponent->direction;
					auto&		renderPoints		= renderComponent->points;


					enableTrigerTime += GetFrameTime() * 0.5f;

					if (frameNowIndex >= framesSize - 1)
					{
						frameNowIndex = 0;
					}

					if (enableTrigerTime >= GetFrameTime())
					{
						{
							moveSpeed = frameSpeed;
							frames[frameNowIndex].get()->SetEnable(true);

							//framePosition = targetPosition;
							TranslatePosition(targetObject, frames[frameNowIndex], 
												{setting.frameTargetOffsetX, setting.frameTargetOffsetY});
							renderPoints[0] = framePosition;

							enableTrigerTime = 0.f;
							frameNowIndex++;
							size = setting.framePlayerSize;
						}
					}
				}
			}
		}
	}
}
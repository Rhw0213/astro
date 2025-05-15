#include "FrameSystem.h"
#include "Component.h"
#include "Object.h"
#include "Utility.h"
#include "Setting.h"
#include "ComponentManager.h"
#include "EventManager.h"
#include <iostream> 

namespace astro
{
	void FrameSystem::Init()
	{
		auto& setting = GameSettingManager::Instance();
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::FRAME_COMPONENT |
									ComponentType::ACTIVE_COMPONENT) 
		);

		for (auto& archetype : archetypes)
		{
			auto* frameComponents = archetype->GetComponents<FrameComponent>();
			auto* activeComponents = archetype->GetComponents<ActiveComponent>();

			if (frameComponents && activeComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					float&				frameSize	= frameComponents[i].size;
					const InstanceID&	ownerId		= frameComponents[i].target;
					const InstanceID&	manageId	= frameComponents[i].manage;
					size_t&				index		= frameComponents[i].index;
					bool&				enable		= activeComponents[i].enable;

					auto ownerObject = objectManager->GetObject(ownerId);
					auto manageObject = objectManager->GetObject(manageId);

					auto* frameManageComponent = CM.GetComponent<FrameManageComponent>(manageObject->GetComponentMask(), manageObject->GetInstanceID());
					size_t& maxIndex = frameManageComponent->frameMaxIndex;

					index = maxIndex++;

					if(ownerObject->GetType() == ObjectType::PLAYER_ID)
					{ 
						frameSize = setting.frameSize;
						EventManager::Instance().RegisterEvent<WarpStartEvent>([&frameSize](const WarpStartEvent* e) {
							frameSize = e->frameSize;
						});

						EventManager::Instance().RegisterEvent<WarpStopEvent>([&frameSize](const WarpStopEvent* e) {
							frameSize = e->frameSize;
						});

						frameManageComponent->enable = true;
					}
				}
			}
		}
	}

	void FrameSystem::Process()
	{
		auto& setting = GameSettingManager::Instance();
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::FRAME_COMPONENT |
									ComponentType::MOVE_COMPONENT |
									ComponentType::TRANSFORM_COMPONENT |
									ComponentType::ACTIVE_COMPONENT) 
		);

		for (auto& archetype : archetypes)
		{
			auto* frameComponents		= archetype->GetComponents<FrameComponent>();
			auto* activeComponents		= archetype->GetComponents<ActiveComponent>();
			auto* moveComponents		= archetype->GetComponents<MoveComponent>();
			auto* transformComponents	= archetype->GetComponents<TransformComponent>();

			if (frameComponents && activeComponents && moveComponents && transformComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					//if (activeComponents[i].enable)
					{ 
						bool&		enable				= activeComponents[i].enable;
						float&		time				= frameComponents[i].time;
						InstanceID&	targetId			= frameComponents[i].target;
						InstanceID&	manageId			= frameComponents[i].manage;
						size_t&		frameIndex			= frameComponents[i].index;
						float&		frameSpeed			= frameComponents[i].speed;

						float&		moveSpeed			= moveComponents[i].speed;
						MyVector2&	moveDirection		= moveComponents[i].direction;

						float&		localScale			= transformComponents[i].localScale;
						MyVector2&	frameLocalPosition	= transformComponents[i].localPosition;

						auto manage = objectManager.get()->GetObject(manageId);

						auto* frameManageComponent = CM.GetComponent<FrameManageComponent>(manage->GetComponentMask(), manage->GetInstanceID());

						size_t& frameNowIndex = frameManageComponent->frameNowIndex;
						InstanceID& frameOwner = frameManageComponent->frameOwner;

						if (!enable && (targetId == frameOwner) && (frameIndex == frameNowIndex))
						{
							if (frameManageComponent->enable)
							{ 
								auto targetObject = objectManager.get()->GetObject(targetId);
								auto* targetTransformComponent = CM.GetComponent<TransformComponent>(targetObject->GetComponentMask(), targetObject->GetInstanceID());

								const Angle& targetRotation	= targetTransformComponent->worldRotation;
								float randomRadian	= Angle::DregreeToRadian(Random::distributionFrameRange(Random::gen));
								randomRadian		+= targetRotation.radian;

								moveDirection		= { -cosf(randomRadian), -sinf(randomRadian) };
								frameLocalPosition	= TranslatePosition(targetObject, { setting.frameTargetOffsetX, setting.frameTargetOffsetY });
								moveSpeed			= frameSpeed;
								localScale			= 1.f;
								enable				= true;
							}
						}

						if (enable)
						{	
							time += GetFrameTime();

							if (time > setting.frameLifeTime)
							{
								time = 0.f;
								enable = false;
							}

							float factorOut = 1.f - powf(1.f - Normalize(time, 0.f, 1.f), 2.f);
							moveSpeed = frameSpeed * (1.f - factorOut);
							localScale *= 0.95f;

							if (localScale <= 0.f)
							{
								localScale = 1.f;
							}
						}
					}
				}
			}
		}
	}
}
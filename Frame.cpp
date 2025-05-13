#include "Frame.h"
#include "Setting.h"
#include "ComponentManager.h"
#include <iostream> 

namespace astro
{
	Frame::Frame(InstanceID parentId, InstanceID manageId)
		: parentId(parentId)
		, manageId(manageId)
	{
		componentMask = static_cast<uint64_t>(
			ComponentType::ACTIVE_COMPONENT |
			ComponentType::TRANSFORM_COMPONENT |
			ComponentType::MOVE_COMPONENT |
			ComponentType::FRAME_COMPONENT |
			ComponentType::RENDER_COMPONENT 
			);
	}

	void Frame::Init()
	{
		auto& setting	= GameSettingManager::Instance();
		auto& CM		= ComponentManager::Instance();

		auto* activeComponent			= CM.GetComponent<ActiveComponent>		(componentMask, instanceId);
		auto* renderComponent			= CM.GetComponent<RenderComponent>		(componentMask, instanceId);
		auto* transformComponent		= CM.GetComponent<TransformComponent>	(componentMask, instanceId);
		auto* frameComponent			= CM.GetComponent<FrameComponent>		(componentMask, instanceId);
		auto* moveComponent				= CM.GetComponent<MoveComponent>		(componentMask, instanceId);

		//target
		if (activeComponent && renderComponent && transformComponent && frameComponent && moveComponent)
		{
			bool&		enable			= activeComponent->enable;
			float&		frameSpeed		= frameComponent->speed;
			float&		time			= frameComponent->time;
			InstanceID&	target			= frameComponent->target;
			InstanceID&	manage			= frameComponent->manage;
			float&		moveSpeed		= moveComponent->speed;
			MyVector2&	localPosition	= transformComponent->localPosition;
			auto&		renderPoints	= renderComponent->points;
			ObjectType&	objectType		= renderComponent->objectType;
			float&		frameSize		= frameComponent->size;
			Color&		color			= frameComponent->color;

			moveSpeed			= 0.f;
			time				= 0.f;
			localPosition		= {0, 0};
			frameSize			= setting.frameSize;
			frameSpeed			= setting.frameSpeed;
			color				= { 255, 255, 255, 125 };
			objectType			= ObjectType::FRAME_ID;
			target				= parentId;
			manage				= manageId;

			renderPoints.push_back({0, 0});
			enable = false;
		}
	}

	void Frame::Update()
	{
	}
}

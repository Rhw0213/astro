#include "Missile.h"
#include "Component.h"
#include "Setting.h"
#include "ComponentManager.h"

namespace astro
{
	Missile::Missile(InstanceID missileOwner, InstanceID frameManageId)
		: missileOwner(missileOwner)
		, frameManageId(frameManageId)
	{
		componentMask = static_cast<uint64_t>(
			ComponentType::ACTIVE_COMPONENT |
			ComponentType::TRANSFORM_COMPONENT |
			ComponentType::RENDER_COMPONENT |
			ComponentType::MISSILE_COMPONENT |
			ComponentType::MOVE_COMPONENT 
			);
	}

	void Missile::Init()
	{
		auto& setting	= GameSettingManager::Instance();
		auto& CM		= ComponentManager::Instance();
		auto* activeComponent		= CM.GetComponent<ActiveComponent>	(componentMask, instanceId);

		if (activeComponent->enable)
		{ 
			auto* transformComponent	= CM.GetComponent<TransformComponent>	(componentMask, instanceId);
			auto* renderComponent		= CM.GetComponent<RenderComponent>		(componentMask, instanceId);
			auto* missileComponent		= CM.GetComponent<MissileComponent>		(componentMask, instanceId);
			
			MyVector2&	localPosition	= transformComponent->localPosition;
			bool&		enable			= activeComponent->enable;
			auto&		renderPoints	= renderComponent->points;
			auto&		objectType		= renderComponent->objectType;
			float&		speed			= missileComponent->speed;
			InstanceID& missileOwner	= missileComponent->missileOwner;

			speed		= setting.bulletSpeed;
			objectType	= ObjectType::MISSILE_ID;
			missileOwner = this->missileOwner;

			renderPoints.push_back({ 0, 0 });

			enable = false;
		}
	}

	void Missile::Update()
	{
	}
}

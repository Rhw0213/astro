#include "Missile.h"
#include "Component.h"
#include "Setting.h"
#include "ComponentManager.h"

namespace astro
{
	Missile::Missile(InstanceID missileOwner)
		: missileOwner(missileOwner)
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

			speed		= setting.bulletSpeed;
			objectType	= ObjectType::MISSILE_ID;

			renderPoints.push_back({ 0, 0 });

			enable = false;
		}
	}

	void Missile::Update()
	{
		//auto& CM		= ComponentManager::Instance();
		//if (this->IsEnable())
		//{ 
		//	auto* transformComponent	= Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		//	auto* bulletComponent		= Object::GetComponent<MissileComponent>(ComponentType::MISSILE_COMPONENT);
		//	auto* moveComponent			= Object::GetComponent<MoveComponent>(ComponentType::MOVE_COMPONENT);

		//	const float&	speed		= bulletComponent->speed;
		//	float&			moveSpeed	= moveComponent->speed;

		//	moveSpeed = speed;
		//}
	}
}

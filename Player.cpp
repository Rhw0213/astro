#include "Player.h"
#include "Component.h"
#include "ComponentManager.h"
#include "PlayerState.h"
#include "CameraState.h"
#include "Setting.h"
#include <cmath> 
#include <iostream> 

namespace astro
{
	Player::Player(const MyVector2& position)
	{
		componentMask = static_cast<uint64_t>(
			ComponentType::ACTIVE_COMPONENT |
			ComponentType::TRANSFORM_COMPONENT |
			ComponentType::RENDER_COMPONENT |
			ComponentType::INPUT_COMPONENT |
			ComponentType::MOVE_COMPONENT |
			ComponentType::CAMERA_COMPONENT
			);
	}

	void Player::Init()
	{                 
		auto& setting	= GameSettingManager::Instance();
		auto& CM		= ComponentManager::Instance();

		auto* renderComponent		= CM.GetComponent<RenderComponent>(componentMask, instanceId);
		auto* transformComponent	= CM.GetComponent<TransformComponent>(componentMask, instanceId);
		auto& camera				= CM.GetComponent<CameraComponent>(componentMask, instanceId)->camera;

		if (transformComponent && renderComponent)
		{
			transformComponent->localScale = 1;
			renderComponent->points.reserve(3);

			const MyVector2&	worldPosition	= transformComponent->worldPosition;
			const Angle&		localRotation	= transformComponent->localRotation;
			float				localScale		= transformComponent->localScale;

			auto&				points			= renderComponent->points;
			auto&				objectType		= renderComponent->objectType;

			const float deg_to_rad = PI / 180.0f;

			float playerSize = setting.playerSize;

			//render
			objectType = ObjectType::PLAYER_ID;
			points.push_back(MyVector2{ playerSize * std::cosf(localRotation.radian), playerSize * std::sinf(localRotation.radian) });
			points.push_back(MyVector2{ playerSize * std::cosf(localRotation.radian + 120.0f * deg_to_rad), playerSize * std::sinf(localRotation.radian + 120.0f * deg_to_rad) });
			points.push_back(MyVector2{ playerSize * std::cosf(localRotation.radian+ 240.0f * deg_to_rad), playerSize * std::sinf(localRotation.radian + 240.0f * deg_to_rad) });

			//shader
			//auto& shaderName = shaderComponent;
			//shaderName.push_back(ShaderName::FRAME);
			//framePosition

			//camera
			camera.offset = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			camera.rotation = 0.f;
			camera.target = worldPosition;
			camera.zoom = 1.f;
		}

		PlayerState::Instance().Update(shared_from_this());
	}

	void Player::Update()
	{
		PlayerState::Instance().Update(shared_from_this());
	}
}

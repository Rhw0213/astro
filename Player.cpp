#include "Player.h"
#include "Component.h"
#include "PlayerState.h"
#include <cmath> 

namespace astro
{
	Player::Player(const MyVector2& position)
	{
		Object::AddComponent(std::make_shared<TransformComponent>(position));
		Object::AddComponent(std::make_shared<RotationComponent>());
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<InputComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>());
		Object::AddComponent(std::make_shared<CameraComponent>());
	}

	void Player::Init()
	{
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		auto* rotationComponent = Object::GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);


		auto& camera= Object::GetComponent<CameraComponent>(ComponentType::CAMERA_COMPONENT)->camera;

		if (transformComponent && renderComponent && rotationComponent)
		{
			transformComponent->direction = { 0, -1 };
			transformComponent->size = 25;
			renderComponent->points.reserve(3);
			rotationComponent->angle = { atan2f(-1, 0) };
			rotationComponent->previousAngle = rotationComponent->angle;

			const auto& direction = transformComponent->direction.Normalize();
			const auto& position = transformComponent->position;
			auto& points = renderComponent->points;
			float size = transformComponent->size;
			Angle angle = rotationComponent->angle;

			const float deg_to_rad = PI / 180.0f;

			//render
			points.push_back(position + MyVector2{ size * std::cosf(angle.radian), size * std::sinf(angle.radian) });
			points.push_back(position + MyVector2{ size * std::cosf(angle.radian + 120.0f * deg_to_rad), size * std::sinf(angle.radian + 120.0f * deg_to_rad) });
			points.push_back(position + MyVector2{ size * std::cosf(angle.radian+ 240.0f * deg_to_rad), size * std::sinf(angle.radian + 240.0f * deg_to_rad) });

			//shader
			//auto& shaderName = shaderComponent;
			//shaderName.push_back(ShaderName::FRAME);
			//framePosition

			//camera
			camera.offset = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			camera.rotation = 0.f;
			camera.target = position;
			camera.zoom = 1.f;
		}

		PlayerState::Instance().Update(shared_from_this());
	}

	void Player::Update()
	{
		PlayerState::Instance().Update(shared_from_this());

		auto* rotationComponent = Object::GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		auto* frameComponent = Object::GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);

		Angle& angle = rotationComponent->angle;
		const MyVector2& direction = transformComponent->direction;
		
		angle.radian = atan2f(direction.y(), direction.x());
	}
}

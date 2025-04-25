#include "Frame.h"
#include <iostream> 

namespace astro
{
	Frame::Frame(InstanceID targetId)
	{
		Object::AddComponent(std::make_shared<TransformComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>());
		Object::AddComponent(std::make_shared<RotationComponent>());
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<FrameComponent>(targetId));
	}

	void Frame::Init()
	{
		auto* renderComponent			= Object::GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);
		auto* transformComponent		= Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

		if (renderComponent && transformComponent)
		{
			const MyVector2 position	= transformComponent->position;
			auto& renderPoints			= renderComponent->points;

			renderPoints.push_back(position);
		}
	}

	void Frame::Update()
	{
		if (Object::IsEnable())
		{
			auto* moveComponent = Object::GetComponent<MoveComponent>(ComponentType::MOVE_COMPONENT);
			auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
			auto* frameComponent = Object::GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);
			auto* rotationComponent = Object::GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);

			float& moveSpeed = moveComponent->speed;
			const float& frameSpeed = frameComponent->speed;
			float				time = frameComponent->time;
			float				rotationDirection = frameComponent->rotationDirection;
			MyVector2& direction = transformComponent->direction;
			Angle& angle = rotationComponent->angle;

			angle.radian += (2.f * PI * GetFrameTime() * rotationDirection);
			direction = MyVector2{ cosf(angle.radian), sinf(angle.radian) };

			float factorOut = 1.f - powf(1.f - Normalize(time, 0.f, 1.f), 2.f);

			moveSpeed = frameSpeed * (1.f - factorOut);
		}
	}
}

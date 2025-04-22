#include "Frame.h"

namespace astro
{
	Frame::Frame(InstanceID targetId)
	{
		Object::AddComponent(std::make_shared<TransformComponent>());
		Object::AddComponent(std::make_shared<RotationComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>());
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<FrameComponent>(targetId));
	}

	void Frame::Init()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		auto* rotationComponent = Object::GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);
		auto* frameComponent = Object::GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);

		if (transformComponent && rotationComponent && renderComponent && frameComponent)
		{
			MyVector2& position = transformComponent->position;
			MyVector2& direction = transformComponent->direction;
			Angle& angle = rotationComponent->angle;
			auto& framePositions = frameComponent->positions;
			auto& renderPoints = renderComponent->points;

			angle.radian = atan2f(direction.y() , direction.x());

			int frameCount = 6;
			framePositions.reserve(frameCount);

			for (size_t i = 0; i < frameCount; i++)
			{
				framePositions.push_back({ 0, 0 });
				float offset = 10.f;
				renderPoints.push_back({-offset, -offset});
				renderPoints.push_back({offset, -offset});
				renderPoints.push_back({-offset, offset});
				renderPoints.push_back({offset, offset});
			}
		}
	}

	void Frame::Update()
	{
		auto* frameComponent = Object::GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);
	}
}

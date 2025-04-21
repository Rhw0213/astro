#include "RotationSystem.h"

namespace astro
{
	void RotationSystem::Init()
	{

	}

	void RotationSystem::Process()
	{
		for (const auto& object : objects)
		{
			auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
			auto* rotationComponent = object.get()->GetComponent<RotationComponent>(ComponentID::ROTATION_COMPONENT);
			auto* renderComponent = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);

			const MyVector2& position = transformComponent->position;
			float& currentAngle = rotationComponent->angle.radian;
			float& previousAngle = rotationComponent->previousAngle.radian;
			auto& points = renderComponent->points;

			if (std::abs(currentAngle - previousAngle) > 1e-7f)
			{
				float deltaAngle = currentAngle - previousAngle;
				
				deltaAngle = atan2f(sinf(deltaAngle), cosf(deltaAngle));

				float cosDelta = cosf(deltaAngle);
				float sinDelta = sinf(deltaAngle);

				for (auto& point : points)
				{
					float x = point.x() - position.x();
					float y = point.y() - position.y();

					float rotatedX = x * cosDelta - y * sinDelta;
					float rotatedY = x * sinDelta + y * cosDelta;

					point.x() = position.x() + static_cast<float>(rotatedX);
					point.y() = position.y() + static_cast<float>(rotatedY);
				}

				previousAngle = currentAngle;
			}
		}
	}
}

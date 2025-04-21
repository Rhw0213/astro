#include "Frame.h"

namespace astro
{
	Frame::Frame(const MyVector2& position)
	{
		Object::AddComponent(std::make_shared<TransformComponent>(position));
		Object::AddComponent(std::make_shared<RotationComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>());
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<ShaderComponent>());
		Object::AddComponent(std::make_shared<FrameComponent>());
	}

	void Frame::Init()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* rotationComponent = Object::GetComponent<RotationComponent>(ComponentID::ROTATION_COMPONENT);
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		auto* frameComponent = Object::GetComponent<FrameComponent>(ComponentID::FRAME_COMPONENT);

		if (transformComponent && rotationComponent && renderComponent && frameComponent)
		{
			MyVector2& position = transformComponent->position;
			MyVector2& direction = transformComponent->direction;
			Angle& angle = rotationComponent->angle;

			angle.radian = atan2f(direction.y() , direction.x());

			for (size_t i = 0; i < 6; i++)
			{
				frameComponent->positions.push_back( { 0, 0 } );

				for (size_t i = 0; i < 4; i++)
				{
					renderComponent->points.push_back()

				}

			}
		}
	}

	void Frame::Update()
	{
	}
}

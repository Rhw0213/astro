#include "MoveSystem.h"

namespace astro
{
	void MoveSystem::Init()
	{
	}

	void MoveSystem::Process()
	{
		for (const auto& object : objects)
		{
			auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
			auto* moveComponent = object.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
			auto* renderComponent = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);

			if (object && transformComponent && moveComponent && renderComponent)
			{
				auto& points = renderComponent->points;

				MyVector2& position = transformComponent->position;
				const MyVector2& moveDirection = moveComponent->direction.Normalize();
				const float& speed = moveComponent->speed;
				MyVector2& slowVelocity = moveComponent->slowVelocity;

				//속도 계산
				MyVector2 velocity = moveDirection * speed * GetFrameTime();
				float velocityLength = velocity.Length();

				if (velocityLength > slowVelocity.Length())
				{
					slowVelocity += (velocity * 0.05f);
				}
				else
				{
					slowVelocity *= 0.95f;
				}

				//랜더위치 이동
				for (auto& point : points)
				{
					point += slowVelocity;
				}

				position += slowVelocity;
			}
		}
	}
}

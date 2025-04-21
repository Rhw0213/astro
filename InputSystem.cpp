#include "InputSystem.h"
#include "raylib.h"
#include "EventManager.h"
#include "Event.h"

namespace astro
{
	void InputSystem::Init()
	{
	}

	void InputSystem::Process()
	{
		for (const auto& object: objects)
		{
			if (object && object.get()->GetID() == ObjectID::PLAYER_ID)
			{
				auto* moveComponent = object.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
				auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);

				MyVector2& position = transformComponent->position;
				MyVector2& direction = transformComponent->direction;
				MyVector2& moveDirection = moveComponent->direction;
				float& moveSpeed = moveComponent->speed;

				const Camera2D& camera = cameraComponent->camera;
				const MyVector2& mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);

				if (!IsKeyDown(KEY_SPACE))
				{
					direction = position.DirectionTo(mousePosition);
				}

				if (moveComponent)
				{
					MyVector2 move = { 0, 0 };
					float speed = 0.f;
					bool isSpacePressed = false;

					if (IsKeyDown(KEY_W))
					{
						speed = 500.f;
						move += { direction.x(), direction.y() };

						if (IsKeyDown(KEY_SPACE))
						{
							speed = 2000.f;
							isSpacePressed = true;
						}
					}

					if (IsKeyDown(KEY_A) && !isSpacePressed)
					{
						speed = 500.f;
						move += { direction.y(), -direction.x() };
					}

					if (IsKeyDown(KEY_D) && !isSpacePressed)
					{
						speed = 500.f;
						move += { -direction.y(), direction.x() };
					}

					if (IsKeyDown(KEY_S) && !isSpacePressed)
					{
						speed = 300.f;
						move += { -direction.x(), -direction.y() };
					}

					if (IsKeyReleased(KEY_SPACE))
					{
						EventManager::Instance().RunEvent<WarpStopEvent>(WarpStopEvent());
					}
					
					if (IsKeyPressed(KEY_SPACE))
					{
						EventManager::Instance().RunEvent<WarpStartEvent>(WarpStartEvent());
					}

					moveDirection = move;
					moveSpeed = speed;
				}
			}
		}
	}
}

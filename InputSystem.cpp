#include "InputSystem.h"
#include "raylib.h"
#include "EventManager.h"
#include "Event.h"
#include "Setting.h"

namespace astro
{
	void InputSystem::Init()
	{
	}

	void InputSystem::Process()
	{
		auto& setting = GameSettingManager::Instance();

		for (const auto& object: objects)
		{
			if (object && object.get()->IsEnable() && object.get()->GetType() == ObjectType::PLAYER_ID)
			{
				auto* moveComponent = object.get()->GetComponent<MoveComponent>(ComponentType::MOVE_COMPONENT);
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
				auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentType::CAMERA_COMPONENT);

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
						EventManager::Instance().RunEvent<WarpStopEvent>(WarpStopEvent(setting.frameIncreaseFrameDefaultSize));
					}
					
					if (IsKeyPressed(KEY_SPACE))
					{
						EventManager::Instance().RunEvent<WarpStartEvent>(WarpStartEvent(setting.frameIncreaseFrameWarpSize));
					}

					moveDirection = move;
					moveSpeed = speed;
				}
			}
		}
	}
}

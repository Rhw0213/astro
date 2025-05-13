#include "InputSystem.h"
#include "raylib.h"
#include "EventManager.h"
#include "Event.h"
#include "Setting.h"
#include "ComponentManager.h"
#include "PlayerState.h"

namespace astro
{
	void InputSystem::Init()
	{
	}

	void InputSystem::Process()
	{
		auto& setting = GameSettingManager::Instance();
		auto& CM = ComponentManager::Instance();
		auto player = PlayerState::Instance().GetPlayer();

		uint64_t mask = player->GetComponentMask();
		InstanceID instanceId = player->GetInstanceID();

		auto* moveComponent		 = CM.GetComponent<MoveComponent>(mask, instanceId);
		auto* transformComponent = CM.GetComponent<TransformComponent>(mask, instanceId);
		auto* cameraComponent	 = CM.GetComponent<CameraComponent>(mask, instanceId);

		MyVector2&	localPosition	= transformComponent->localPosition;
		Angle&		localRotation	= transformComponent->localRotation;
		MyVector2&	moveDirection	= moveComponent->direction;
		float&		moveSpeed		= moveComponent->speed;

		const Camera2D& camera = cameraComponent->camera;
		const MyVector2& mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);

		MyVector2 direction = localPosition.DirectionTo(mousePosition);

		if (!IsKeyDown(KEY_SPACE))
		{
			float radian = 0;
			localRotation.radian = atan2f(direction.y(), direction.x());
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
				EventManager::Instance().RunEvent<WarpStopEvent>(WarpStopEvent(setting.frameSize));
			}
			
			if (IsKeyPressed(KEY_SPACE))
			{
				EventManager::Instance().RunEvent<WarpStartEvent>(WarpStartEvent(setting.frameWarpSize));
			}

			moveDirection = move;
			moveSpeed = speed;
		}
	}
}

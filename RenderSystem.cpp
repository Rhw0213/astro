#include "RenderSystem.h"
#include "CameraState.h"
#include "EventManager.h"

namespace astro
{
	RenderSystem::RenderSystem()
		: texture(LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
	}
	void RenderSystem::Init()
	{
		//UI
		for (const auto& object : objects)
		{
			if (object.get()->GetID() == ObjectID::CONTROLL_UI_ID)
			{
				std::shared_ptr<UI> uiPtr = std::dynamic_pointer_cast<UI>(object);

				if (uiPtr)
				{
					uiObjects.push_back(uiPtr);
				}
			}
		}

		// 카메라   오브젝트 찾기
		for (const auto& object : objects)
		{
			if (object.get()->GetID() == ObjectID::PLAYER_ID)
			{
				cameraObjects.push_back(std::shared_ptr<Object>(object));
			}
		}

	}

	void RenderSystem::Process()
	{
		BeginTextureMode(texture);
		ClearBackground(BLANK);

		//Camera
		for (const auto& object: cameraObjects)
		{
			auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);
			if (cameraComponent)
			{
				Camera2D& camera = cameraComponent->camera;
				BeginMode2D(camera);
			}
		}

		for (const auto& object: objects)
		{
			if (object.get()->GetID() == ObjectID::CONTROLL_UI_ID)
			{
				continue;
			}

			//Object
			if (object)
			{
				auto& points = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT)->points;
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				const MyVector2& direction = transformComponent->direction;
				const MyVector2& position = transformComponent->position;
				const float& size = transformComponent->size;

				size_t pointsSize = points.size();

				if (object->GetID() == ObjectID::STAR_ID)
				{
					auto* effectComponent = object.get()->GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);
					int bright = effectComponent->bright;
					float maxSize = effectComponent->maxSize;
					Color starColor = effectComponent->color;
					
					enum DrawIndex
					{
						CIRCLE,
						LINE
					};

					pointsSize = pointsSize == 1 ? 1 : pointsSize - 1;

					for (size_t i = 0; i < pointsSize; i++)
					{
						if (i == CIRCLE)
						{
							MyVector2 renderPosition = points[CIRCLE];
							DrawCircle(static_cast<int>(renderPosition.x()),
										static_cast<int>(renderPosition.y()), 
										size, 
										{ starColor.r, starColor.g, starColor.b, (unsigned char)bright });
						}
						else if (i == LINE)
						{
							//선굶기
							float lineThickness = maxSize * 2.f;
							DrawLineEx(points[i], points[i + 1], lineThickness, 
								{ starColor.r, starColor.g, starColor.b, (unsigned char)bright });
						}
					}

				}
				else if (object.get()->GetID() == ObjectID::PLAYER_ID)
				{
					for (size_t i = 0; i < pointsSize; i++)
					{
						MyVector2& startPoint = points[i];
						MyVector2& endPoint = points[(i + 1) % pointsSize];

						DrawLineEx(startPoint, endPoint, 3.f, WHITE);
					}

					MyVector2 endPoint = position + direction * 100;

					DrawLine(static_cast<int>(position.x()),
						static_cast<int>(position.y()),
						static_cast<int>(endPoint.x()),
						static_cast<int>(endPoint.y()), YELLOW);
				}
				else if (object.get()->GetID() == ObjectID::ASTEROID_ID)
				{
					if (pointsSize > 3)
					{
						for (size_t i = 0; i < pointsSize - 1; i++) {
							DrawLineEx(points[i], points[i + 1], 1.0f, WHITE);
						}
						DrawLineEx(points.back(), points[0], 1.0f, WHITE);
					}
					MyVector2 endPoint = position + direction * 100;

					DrawLine(static_cast<int>(position.x()),
						static_cast<int>(position.y()),
						static_cast<int>(endPoint.x()),
						static_cast<int>(endPoint.y()), YELLOW);
				}
			}
		}

		//카메라 모드 끝 
		EndMode2D();

		// ui render
		for (const auto& object : uiObjects)
		{
			object.get()->Draw();
		}

		EndTextureMode();

		EventManager::Instance().RunEvent(ObjectRenderEndEvent(&texture));
	}
}

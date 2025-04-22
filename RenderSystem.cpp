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
			if (object.get()->GetType() == ObjectType::CONTROLL_UI_ID)
			{
				std::shared_ptr<UI> uiPtr = std::dynamic_pointer_cast<UI>(object);

				if (uiPtr)
				{
					uiObjects.push_back(uiPtr);
				}
			}
		}

		// ī�޶�   ������Ʈ ã��
		for (const auto& object : objects)
		{
			if (object.get()->GetType() == ObjectType::PLAYER_ID)
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
			auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentType::CAMERA_COMPONENT);
			if (cameraComponent)
			{
				Camera2D& camera = cameraComponent->camera;
				BeginMode2D(camera);
			}
		}

		for (const auto& object: objects)
		{
			if (object.get()->GetType() == ObjectType::CONTROLL_UI_ID)
			{
				continue;
			}

			//Object
			if (object)
			{
				auto& points = object.get()->GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT)->points;
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

				const MyVector2& direction = transformComponent->direction;
				const MyVector2& position = transformComponent->position;
				const float& size = transformComponent->size;

				size_t pointsSize = points.size();

				if (object->GetType() == ObjectType::STAR_ID)
				{
					auto* brightEffectComponent = object.get()->GetComponent<BrightEffectComponent>(ComponentType::BRIGHT_EFFECT_COMPONENT);
					int bright = brightEffectComponent->bright;
					float maxSize = brightEffectComponent->maxSize;
					Color starColor = brightEffectComponent->color;
					
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
							//������
							float lineThickness = maxSize * 2.f;
							DrawLineEx(points[i], points[i + 1], lineThickness, 
								{ starColor.r, starColor.g, starColor.b, (unsigned char)bright });
						}
					}

				}
				else if (object.get()->GetType() == ObjectType::PLAYER_ID)
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
				else if (object.get()->GetType() == ObjectType::ASTEROID_ID)
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

		//ī�޶� ��� �� 
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

#include "RenderSystem.h"
#include "CameraState.h"
#include "EventManager.h"
#include "rlgl.h"

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
			if (object && object.get()->IsEnable())
			{
				auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentType::CAMERA_COMPONENT);
				if (cameraComponent)
				{
					Camera2D& camera = cameraComponent->camera;
					BeginMode2D(camera);
				}
			}
		}

		for (const auto& object: objects)
		{
			if (object && object.get()->IsEnable())
			{
				if (object.get()->GetType() == ObjectType::CONTROLL_UI_ID)
				{
					continue;
				}

				//Object
				auto& points = object.get()->GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT)->points;
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
				auto* rotationComponent = object.get()->GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);

				const MyVector2& direction = transformComponent->direction;
				const MyVector2& position = transformComponent->position;
				const float& size = transformComponent->size;
				const Angle& angle = rotationComponent->angle;

				size_t pointsSize = points.size();

				if (pointsSize == 0)
				{
					ObjectType type = object->GetType();
				}

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
							float lineThickness = maxSize * 2.f;
							DrawLineEx(points[i], points[i + 1], lineThickness,
								{ starColor.r, starColor.g, starColor.b, (unsigned char)bright });
						}
					}
				}
				else if ((object.get()->GetType() == ObjectType::ASTEROID_ID) ||
					(object.get()->GetType() == ObjectType::PLAYER_ID))
				{
					rlPushMatrix();

					rlTranslatef(position.x(), position.y(), 0);
					float rotationDegree = Angle::RadianToDegree(angle.radian);
					rlRotatef(rotationDegree, 0, 0, 1);

					MyVector2 p0 = points[0];
					for (size_t i = 1; i < points.size() - 1; i++)
					{
						MyVector2 p1 = points[i];
						MyVector2 p2 = points[i + 1];

						DrawTriangle(p0, p2, p1, GRAY);
					}

					rlPopMatrix();

					MyVector2 endPoint = position + direction * 100;

					DrawLine(static_cast<int>(position.x()),
						static_cast<int>(position.y()),
						static_cast<int>(endPoint.x()),
						static_cast<int>(endPoint.y()), YELLOW);
				}
				else if (object.get()->GetType() == ObjectType::FRAME_ID)
				{
					auto* transform = object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
					auto* rotation = object.get()->GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);
					auto* frameComponent = object.get()->GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);

					if (transform && rotation && frameComponent)
					{
						Rectangle rec = { points[0].x(), points[0].y(), size, size };
						Vector2 origin = { size / 2.0f, size / 2.0f };
						Color color = frameComponent->color;

						//DrawRectanglePro(rec, origin, Angle::RadianToDegree(angle.radian), color);
						DrawCircle(static_cast<int>(points[0].x()), 
									static_cast<int>(points[0].y()), size /2.f, color);

						//MyVector2 endPoint = transform->position + transform->direction * 100;

						//DrawLine(static_cast<int>(transform->position.x()),
						//		 static_cast<int>(transform->position.y()),
						//		 static_cast<int>(endPoint.x()),
						//		 static_cast<int>(endPoint.y()), YELLOW);
					}
				}
			}
		}

		EndMode2D();

		// ui render
		for (const auto& object : uiObjects)
		{
			if (object && object.get()->IsEnable())
			{
				object.get()->Draw();
			}
		}

		EndTextureMode();

		EventManager::Instance().RunEvent(ObjectRenderEndEvent(&texture));
	}
}

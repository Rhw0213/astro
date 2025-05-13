#include "RenderSystem.h"
#include "CameraState.h"
#include "EventManager.h"
#include "ComponentManager.h"
#include "rlgl.h"

namespace astro
{
	RenderSystem::RenderSystem()
		: texture(LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
	}
	void RenderSystem::Init()
	{

	}

	void RenderSystem::Process()
	{
		BeginTextureMode(texture);
		ClearBackground(BLANK);

		auto& CM = ComponentManager::Instance();

		auto cameraArchetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::CAMERA_COMPONENT)
		);

		//Camera
		for (auto& archetype : cameraArchetypes)
		{
			auto* cameraComponents = archetype->GetComponents<CameraComponent>();

			if (cameraComponents)
			{ 
				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					auto& cameraComponent = cameraComponents[i];
					Camera2D& camera = cameraComponent.camera;
					BeginMode2D(camera);
					
					Render();

					EndMode2D();
				}
			}
		}

		//for (const auto& object : uiObjects)
		//{
		//	if (object && object.get()->IsEnable())
		//	{
		//		object.get()->Draw();
		//	}
		//}

		EndTextureMode();
		EventManager::Instance().RunEvent(ObjectRenderEndEvent(&texture));
	}

	void RenderSystem::Render()
	{
		auto& CM = ComponentManager::Instance();
		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::RENDER_COMPONENT |
									ComponentType::TRANSFORM_COMPONENT |
									ComponentType::ACTIVE_COMPONENT)
		);

		for (auto* archetype : archetypes)
		{
			auto* renderComponents			= archetype->GetComponents<RenderComponent>();
			auto* activeComponents			= archetype->GetComponents<ActiveComponent>();
			auto* transformComponents		= archetype->GetComponents<TransformComponent>();
			auto* brightEffectComponents	= archetype->GetComponents<BrightEffectComponent>();
			auto* frameComponents			= archetype->GetComponents<FrameComponent>();

			if (renderComponents && transformComponents && activeComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					if (activeComponents[i].enable)
					{ 
						auto& points			= renderComponents[i].points;
						auto& objectType		= renderComponents[i].objectType;
						auto& transformComponent = transformComponents[i];

						const MyVector2&	worldPosition	= transformComponent.worldPosition;
						const Angle&		worldRotation	= transformComponent.worldRotation;
						const float&		worldScale		= transformComponent.worldScale;

						const MyVector2&	localPosition	= transformComponent.localPosition;
						const Angle&		localRotation	= transformComponent.localRotation;
						const float&		localScale		= transformComponent.localScale;

						rlPushMatrix();

						rlTranslatef(worldPosition.x(), worldPosition.y(), 0);
						rlRotatef(Angle::RadianToDegree(worldRotation.radian), 0, 0, 1);
						rlScalef(worldScale, worldScale, 1);

						size_t pointsSize = points.size();

						if (objectType == ObjectType::STAR_ID && brightEffectComponents)
						{
							int		bright		= brightEffectComponents[i].bright;
							float	maxSize		= brightEffectComponents[i].maxSize;
							Color	starColor	= brightEffectComponents[i].color;

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
									DrawCircle(static_cast<int>(points[i].x()), 
												static_cast<int>(points[i].y()), 
												localScale, 
												starColor);
								}
								else if (i == LINE)
								{
									float lineThickness = maxSize * 2.f;
									DrawLineEx(points[i], points[i + 1], lineThickness, starColor);
								}
							}
						}
						else if ((objectType == ObjectType::ASTEROID_ID) || (objectType == ObjectType::PLAYER_ID))
						{
							MyVector2 p0 = points[0];

							for (size_t i = 1; i < points.size() - 1; i++)
							{
								MyVector2 p1 = points[i];
								MyVector2 p2 = points[i + 1];

								DrawTriangle(p0, p2, p1, GRAY);
							}

							MyVector2 offset = { cosf(localRotation.radian), sinf(localRotation.radian) };
							MyVector2 endPoint = localPosition + offset * 100;

							//DrawLine(static_cast<int>(localPosition.x()), static_cast<int>(localPosition.y()), static_cast<int>(endPoint.x()), static_cast<int>(endPoint.y()), YELLOW);
						}
						else if (objectType == ObjectType::FRAME_ID)
						{

							if (frameComponents)
							{
								//Rectangle rec = { points[0].x(), points[0].y(), localScale, localScale };
								//Vector2 origin = { localScale / 2.0f, localScale / 2.0f };
								Color color = frameComponents[i].color;
								float size = frameComponents[i].size;

								//DrawRectanglePro(rec, origin, Angle::RadianToDegree(angle.radian), color);
								DrawCircle(static_cast<int>(points[0].x()), 
											static_cast<int>(points[0].y()), size, color);

								//MyVector2 endPoint = transform->position + transform->direction * 100;

								//DrawLine(static_cast<int>(transform->position.x()),
								//		 static_cast<int>(transform->position.y()),
								//		 static_cast<int>(endPoint.x()),
								//		 static_cast<int>(endPoint.y()), YELLOW);
							}
						}
						rlPopMatrix();
					}
				}

			}
		}
	}
}

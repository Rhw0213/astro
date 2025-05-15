#include "RenderSystem.h"
#include "CameraState.h"
#include "ObjectCountState.h"
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
		auto& objectCounts = ObjectCountState::Instance();
		size_t count = 0;

		count = objectCounts.GetObjectCount(ObjectType::ASTEROID_ID);
		batchs[ObjectType::ASTEROID_ID] = BatchData();
		batchs[ObjectType::ASTEROID_ID].vertices.reserve(count);

		count = objectCounts.GetObjectCount(ObjectType::PLAYER_ID);
		batchs[ObjectType::PLAYER_ID] = BatchData();
		batchs[ObjectType::PLAYER_ID].vertices.reserve(count);

		count = objectCounts.GetObjectCount(ObjectType::MISSILE_ID);
		batchs[ObjectType::MISSILE_ID] = BatchData();
		batchs[ObjectType::MISSILE_ID].vertices.reserve(count);

		count = objectCounts.GetObjectCount(ObjectType::STAR_ID);
		batchs[ObjectType::STAR_ID] = BatchData();
		batchs[ObjectType::STAR_ID].vertices.reserve(count * 12 * 3);

		count = objectCounts.GetObjectCount(ObjectType::FRAME_ID);
		batchs[ObjectType::FRAME_ID] = BatchData();
		batchs[ObjectType::FRAME_ID].vertices.reserve(count);
	}

	void RenderSystem::Process()
	{
		UpdateBatchData();
		RenderBathces();
		//BeginTextureMode(texture);
		//ClearBackground(BLANK);

		//auto& CM = ComponentManager::Instance();

		//auto cameraArchetypes = CM.GetArchetypeQuery(
		//	static_cast<uint64_t>(ComponentType::CAMERA_COMPONENT)
		//);

		////Camera
		//for (auto& archetype : cameraArchetypes)
		//{
		//	auto* cameraComponents = archetype->GetComponents<CameraComponent>();

		//	if (cameraComponents)
		//	{ 
		//		for (size_t i = 0; i < archetype->objectCount; i++)
		//		{ 
		//			auto& cameraComponent = cameraComponents[i];
		//			Camera2D& camera = cameraComponent.camera;
		//			BeginMode2D(camera);
		//			
		//			Render();

		//			EndMode2D();
		//		}
		//	}
		//}

		////for (const auto& object : uiObjects)
		////{
		////	if (object && object.get()->IsEnable())
		////	{
		////		object.get()->Draw();
		////	}
		////}

		//EndTextureMode();
		//EventManager::Instance().RunEvent(ObjectRenderEndEvent(&texture));
	}

	void RenderSystem::Render()
	{
		//auto& CM = ComponentManager::Instance();
		//auto archetypes = CM.GetArchetypeQuery(
		//	static_cast<uint64_t>(ComponentType::RENDER_COMPONENT |
		//							ComponentType::TRANSFORM_COMPONENT |
		//							ComponentType::ACTIVE_COMPONENT)
		//);

		//for (auto* archetype : archetypes)
		//{
		//	auto* renderComponents			= archetype->GetComponents<RenderComponent>();
		//	auto* activeComponents			= archetype->GetComponents<ActiveComponent>();
		//	auto* transformComponents		= archetype->GetComponents<TransformComponent>();
		//	auto* brightEffectComponents	= archetype->GetComponents<BrightEffectComponent>();
		//	auto* frameComponents			= archetype->GetComponents<FrameComponent>();

		//	if (renderComponents && transformComponents && activeComponents)
		//	{
		//		for (size_t i = 0; i < archetype->objectCount; i++)
		//		{ 
		//			if (activeComponents[i].enable)
		//			{ 
		//				auto& points			= renderComponents[i].points;
		//				auto& objectType		= renderComponents[i].objectType;
		//				auto& transformComponent = transformComponents[i];

		//				const MyVector2&	worldPosition	= transformComponent.worldPosition;
		//				const Angle&		worldRotation	= transformComponent.worldRotation;
		//				const float&		worldScale		= transformComponent.worldScale;

		//				const MyVector2&	localPosition	= transformComponent.localPosition;
		//				const Angle&		localRotation	= transformComponent.localRotation;
		//				const float&		localScale		= transformComponent.localScale;

		//				rlPushMatrix();

		//				rlTranslatef(worldPosition.x(), worldPosition.y(), 0);
		//				rlRotatef(Angle::RadianToDegree(worldRotation.radian), 0, 0, 1);
		//				rlScalef(worldScale, worldScale, 1);

		//				size_t pointsSize = points.size();

		//				if (objectType == ObjectType::STAR_ID && brightEffectComponents)
		//				{
		//					int		bright		= brightEffectComponents[i].bright;
		//					float	maxSize		= brightEffectComponents[i].maxSize;
		//					Color	starColor	= brightEffectComponents[i].color;

		//					enum DrawIndex
		//					{
		//						CIRCLE,
		//						LINE
		//					};

		//					pointsSize = pointsSize == 1 ? 1 : pointsSize - 1;

		//					for (size_t i = 0; i < pointsSize; i++)
		//					{
		//						if (i == CIRCLE)
		//						{
		//							MyVector2 renderPosition = points[CIRCLE];
		//							DrawCircle(static_cast<int>(points[i].x()), 
		//										static_cast<int>(points[i].y()), 
		//										localScale, 
		//										starColor);
		//						}
		//						else if (i == LINE)
		//						{
		//							float lineThickness = maxSize * 2.f;
		//							DrawLineEx(points[i], points[i + 1], lineThickness, starColor);
		//						}
		//					}
		//				}
		//				else if ((objectType == ObjectType::ASTEROID_ID) || (objectType == ObjectType::PLAYER_ID))
		//				{
		//					MyVector2 p0 = points[0];

		//					for (size_t i = 1; i < points.size() - 1; i++)
		//					{
		//						MyVector2 p1 = points[i];
		//						MyVector2 p2 = points[i + 1];

		//						DrawTriangle(p0, p2, p1, GRAY);
		//					}

		//					MyVector2 offset = { cosf(localRotation.radian), sinf(localRotation.radian) };
		//					MyVector2 endPoint = localPosition + offset * 100;

		//					//DrawLine(static_cast<int>(localPosition.x()), static_cast<int>(localPosition.y()), static_cast<int>(endPoint.x()), static_cast<int>(endPoint.y()), YELLOW);
		//				}
		//				else if (objectType == ObjectType::FRAME_ID)
		//				{
		//					if (frameComponents)
		//					{
		//						Color color = frameComponents[i].color;
		//						float size = frameComponents[i].size;

		//						DrawCircle(static_cast<int>(points[0].x()), 
		//									static_cast<int>(points[0].y()), size, color);
		//					}
		//				}
		//				else if (objectType == ObjectType::MISSILE_ID)
		//				{
		//					DrawRectangle(static_cast<int>(points[0].x()),
		//									static_cast<int>(points[0].y()),
		//									20, 10, WHITE
		//						);
		//				}
		//				rlPopMatrix();
		//			}
		//		}

		//	}
		//}
	}

	void RenderSystem::UpdateBatchData()
	{
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::RENDER_COMPONENT |
									ComponentType::TRANSFORM_COMPONENT |
									ComponentType::ACTIVE_COMPONENT)
		);

		for (auto& batch : batchs)
		{
			batch.second.vertices.clear();
			batch.second.dirty = true;
		}

		for (auto* archetype : archetypes)
		{
			auto* renderComponents = archetype->GetComponents<RenderComponent>();
			auto* transformComponents = archetype->GetComponents<TransformComponent>();
			auto* activeComponents = archetype->GetComponents<ActiveComponent>();

			auto* brightEffectComponents = archetype->GetComponents<BrightEffectComponent>();
			auto* frameComponents = archetype->GetComponents<FrameComponent>();

			if (renderComponents && transformComponents && activeComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					auto& activeComponent = activeComponents[i];
					if (activeComponent.enable)
					{ 
						auto& renderComponent = renderComponents[i];
						auto& transformComponent = transformComponents[i];

						BatchData& batch = batchs[renderComponent.objectType];

						switch (renderComponent.objectType)
						{
							case ObjectType::ASTEROID_ID:
							{
								break;
							}
							case ObjectType::PLAYER_ID:
							{
								auto colorArray = ColorToFloatArray(GRAY);

								if (renderComponent.points.size() >= 3)
								{
									MyVector2 point_0 = renderComponent.points[0];
									MyVector2 point_1 = renderComponent.points[1];
									MyVector2 point_2 = renderComponent.points[2];

									AddWorldVertex(batch.vertices, point_0, transformComponent, colorArray);
									AddWorldVertex(batch.vertices, point_2, transformComponent, colorArray);
									AddWorldVertex(batch.vertices, point_1, transformComponent, colorArray);
								}
								break;
							}
							case ObjectType::STAR_ID:
							{
								if (brightEffectComponents)
								{
									auto colorArray = ColorToFloatArray(brightEffectComponents[i].color);
									float starRadius = transformComponent.worldScale;

									MyVector2 centerPosition = renderComponent.points[0];

									size_t segments = 12;

									for (size_t j = 0; j < segments; j++)
									{
										float angle_1 = static_cast<float>(j) / segments * 2.f * static_cast<float>(PI);
										float angle_2 = static_cast<float>(j + 1) / segments * 2.f * static_cast<float>(PI);

										MyVector2 point_1 = { centerPosition.x() + starRadius * cosf(angle_1),
											centerPosition.y() + starRadius * sinf(angle_1) };

										MyVector2 point_2 = { centerPosition.x() + starRadius * cosf(angle_2),
											centerPosition.y() + starRadius * sinf(angle_2) };

										AddWorldVertex(batch.vertices, centerPosition, transformComponent, colorArray);
										AddWorldVertex(batch.vertices, point_2, transformComponent, colorArray);
										AddWorldVertex(batch.vertices, point_1, transformComponent, colorArray);
									}
								}
								break;
							}
							case ObjectType::FRAME_ID:
							{

							}
						}
					}
				}
			}
		}

	}

	void RenderSystem::RenderBathces()
	{
		auto& CM = ComponentManager::Instance();
		auto cameraArchetypes = CM.GetArchetypeQuery(static_cast<uint64_t>(ComponentType::CAMERA_COMPONENT));
		Camera2D camera = { 0 };

		for (auto& archetype : cameraArchetypes)
		{
			auto* cameraComponent = archetype->GetComponents<CameraComponent>();

			if (cameraComponent)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					camera = cameraComponent->camera;
				}
			}
		}

		BeginTextureMode(texture);
		ClearBackground(BLANK);
		
		BeginMode2D(camera);

		for (auto& pair : batchs) // 'batches'가 올바른 변수명이라고 가정
		{
			BatchData& currentBatch = pair.second;

			if (currentBatch.vertices.empty()) 
			{
				// 정점이 없으면 그릴 것도 없고, VBO 업데이트할 필요도 없음
				// isDirty를 false로 설정하여 불필요한 VBO 생성을 막을 수 있지만,
				// UpdateBatchData에서 vertices.clear() 후 isDirty=true로 했다면 여기서 처리
				currentBatch.dirty = false;
				continue;
			}

			int numVerticesInBatch = static_cast<int>(currentBatch.vertices.size() / 6);
			if (numVerticesInBatch == 0) 
			{ 
				// 이것도 위와 동일하게 처리
				currentBatch.dirty = false;
				continue;
			}

			// VBO 데이터 업데이트 (isDirty 플래그가 true일 때만)
			if (currentBatch.dirty) 
			{
				if (currentBatch.vboId == 0 && currentBatch.vaoId == 0) 
				{ // VBO가 없으면 새로 생성
					currentBatch.vaoId = rlLoadVertexArray();
					rlEnableVertexArray(currentBatch.vaoId);

					currentBatch.vboId = rlLoadVertexBuffer(
						currentBatch.vertices.data(),
						static_cast<int>(currentBatch.vertices.size() * sizeof(float)),
						false // dynamic: true (데이터가 자주 바뀔 수 있음)
					);

				}
				else if (currentBatch.vboId != 0)
				{ 
					// VBO가 있으면 데이터만 업데이트
					rlUpdateVertexBuffer(
						currentBatch.vboId,
						currentBatch.vertices.data(),
						static_cast<int>(currentBatch.vertices.size() * sizeof(float)),
						0 // offset: 0 (처음부터 업데이트)
					);
				}
				currentBatch.dirty = false; // VBO에 반영했으므로 dirty 상태 해제
			}

			// VBO를 사용하여 그리기
			if (currentBatch.vboId != 0) 
			{ 
				int stride = 6 * sizeof(float); // x,y,r,g,b,a = 6 floats

				// 위치 속성 (셰이더의 layout location = 0)
				rlSetVertexAttribute(0, 2, RL_FLOAT, false, stride, 0);
				// 색상 속성 (셰이더의 layout location = 1)
				rlSetVertexAttribute(1, 4, RL_FLOAT, false, stride, (void*)(2 * sizeof(float)));

				rlEnableVertexAttribute(0); // 위치 속성 활성화
				rlEnableVertexAttribute(1); // 색상 속성 활성화

				//rlSetTexture(rlGetTextureIdDefault()); // 기본 텍스처 사용

				//rlDrawVertexArray(0, numVerticesInBatch); // VBO의 0번 정점부터 numVerticesInBatch개 그리기

				rlDisableVertexAttribute(0);
				rlDisableVertexAttribute(1);
				rlDisableVertexBuffer();
			}
		}

		EndMode2D();
		EndTextureMode();

		EventManager::Instance().RunEvent(ObjectRenderEndEvent(&texture));
	}
}

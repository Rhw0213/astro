#include "Asteroid.h"
#include "Component.h"
#include "ComponentManager.h"

namespace astro
{
	Asteroid::Asteroid(InstanceID parentId)
	{
		componentMask = static_cast<uint64_t>(
			ComponentType::TRANSFORM_COMPONENT |
			ComponentType::MOVE_COMPONENT |
			ComponentType::RENDER_COMPONENT 
			);
	}

	void Asteroid::Init()
	{
		auto& CM		= ComponentManager::Instance();

		auto* transformComponent			= CM.GetComponent<TransformComponent>	(componentMask, instanceId);
		auto* moveComponent					= CM.GetComponent<MoveComponent>		(componentMask, instanceId);

		transformComponent->localScale		= Random::randAsteroidSize(Random::gen);
		transformComponent->localPosition	= { Random::randScreenX(Random::gen), Random::randScreenY(Random::gen)};
		moveComponent->speed				= Random::randAsteroidSpeed(Random::gen);

		SetVertex();
	}

	void Asteroid::Update()
	{
		auto& CM		= ComponentManager::Instance();

		auto* transformComponent			= CM.GetComponent<TransformComponent>	(componentMask, instanceId);
		auto* moveComponent					= CM.GetComponent<MoveComponent>		(componentMask, instanceId);

		const MyVector2&	localPosition	= transformComponent->localPosition;
		Angle&				localRotation	= transformComponent->localRotation;
		MyVector2&			moveDirection	= moveComponent->direction;

		MyVector2 randomPosition = { 
			static_cast<float>(perlinNoise.noise(localPosition.x(), 0)),
			static_cast<float>(perlinNoise.noise(0, localPosition.y()))
		};

		// ?
		if (randomPosition.x() == 0.f && randomPosition.y() == 0.f)
		{
			randomPosition.x() = Random::randMinusToPlusFormOneFloat(Random::gen);
			randomPosition.y() = Random::randMinusToPlusFormOneFloat(Random::gen);
		}

		moveDirection = localPosition.DirectionTo(randomPosition + localPosition);
		localRotation.radian = PI * GetFrameTime() * Random::randMinusToPlusFormOneFloat(Random::gen);
	}

	void Asteroid::SetVertex()
	{
		auto& CM		= ComponentManager::Instance();

		auto* renderComponent			= CM.GetComponent<RenderComponent>(componentMask, instanceId);
		auto* transformComponent		= CM.GetComponent<TransformComponent>(componentMask, instanceId);

		const float&	localScale		= transformComponent->localScale;

		int	countVertex = Random::randAsteroidVertex(Random::gen);
		float angleStep = 2.f * PI / countVertex;
		float baseAngle = 0.f;

		for (size_t i = 0; i < countVertex; i++)
		{
			float angleOffset = Random::randZeroToOneFloat(Random::gen) * 0.5f * angleStep; 
			float currentAngle = baseAngle + angleOffset;

			float distanceFactor = 0.5f + Random::randZeroToOneFloat(Random::gen) * 0.7f; // 0.5~1.2
			float currentDistance = localScale * distanceFactor;

			float vertexOffsetX = currentDistance * cosf(currentAngle);
			float vertexOffsetY = currentDistance * sinf(currentAngle);

			float x = vertexOffsetX;
			float y = vertexOffsetY;

			renderComponent->points.push_back({ x, y });

			baseAngle += angleStep * (0.8f + Random::randZeroToOneFloat(Random::gen) * 0.4f);
		}
	}
}

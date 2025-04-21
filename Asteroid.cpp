#include "Asteroid.h"
#include "Component.h"

namespace astro
{
	Asteroid::Asteroid(const MyVector2& position)
	{
		Object::AddComponent(std::make_shared<TransformComponent>(position));
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>());
		Object::AddComponent(std::make_shared<RotationComponent>());
	}

	void Asteroid::Init()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* moveComponent = Object::GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
		auto* rotationComponent = Object::GetComponent<RotationComponent>(ComponentID::ROTATION_COMPONENT);

		transformComponent->size = Random::randAsteroidSize(Random::gen);
		transformComponent->position = { Random::randScreenX(Random::gen), Random::randScreenY(Random::gen)};
		transformComponent->direction = MyVector2{ Random::randZeroToOneFloat(Random::gen), Random::randZeroToOneFloat(Random::gen)}.Normalize();

		const MyVector2& direction = transformComponent->direction;

		rotationComponent->angle = { atan2f(direction.y(), direction.x()) };
		rotationComponent->previousAngle = rotationComponent->angle;

		moveComponent->speed = Random::randAsteroidSpeed(Random::gen);

		SetVertex();
	}

	void Asteroid::Update()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* moveComponent = Object::GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
		auto* rotationComponent = Object::GetComponent<RotationComponent>(ComponentID::ROTATION_COMPONENT);

		const MyVector2& position = transformComponent->position;
		MyVector2& direction = transformComponent->direction;
		MyVector2& moveDirection = moveComponent->direction;
		Angle& angle = rotationComponent->angle;

		MyVector2 randomPosition = { 
			static_cast<float>(perlinNoise.noise(position.x(), 0)),
			static_cast<float>(perlinNoise.noise(0, position.y()))
		};

		// ?
		if (randomPosition.x() == 0.f && randomPosition.y() == 0.f)
		{
			randomPosition.x() = Random::randMinusToPlusFormOneFloat(Random::gen);
			randomPosition.y() = Random::randMinusToPlusFormOneFloat(Random::gen);
		}

		moveDirection = position.DirectionTo(randomPosition + position);
		angle.radian += PI * GetFrameTime();
		direction = {cosf(angle.radian), sinf(angle.radian)};
	}

	void Asteroid::SetVertex()
	{
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

		const float& size = transformComponent->size;
		const MyVector2 position = transformComponent->position;

		int countVertex = Random::randAsteroidVertex(Random::gen);

		float angleStep = 2.f * PI / countVertex;
		float baseAngle = 0.f;

		for (size_t i = 0; i < countVertex; i++)
		{
			float angleOffset = Random::randZeroToOneFloat(Random::gen) * 0.5f * angleStep; 
			float currentAngle = baseAngle + angleOffset;

			float distanceFactor = 0.5f + Random::randZeroToOneFloat(Random::gen) * 0.7f; // 0.5~1.2
			float currentDistance = size * distanceFactor;

			float vertexOffsetX = currentDistance * cosf(currentAngle);
			float vertexOffsetY = currentDistance * sinf(currentAngle);

			float x = position.x() + vertexOffsetX;
			float y = position.y() + vertexOffsetY;

			renderComponent->points.push_back({ x, y });

			baseAngle += angleStep * (0.8f + Random::randZeroToOneFloat(Random::gen) * 0.4f);
		}
	}
}

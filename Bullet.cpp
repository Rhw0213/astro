#include "Bullet.h"
#include "Component.h"

namespace astro
{
	Bullet::Bullet()
	{
		Object::AddComponent(std::make_shared<TransformComponent>());
		Object::AddComponent(std::make_shared<RotationComponent>());
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<MoveComponent>());
	}

	void Bullet::Init()
	{
		auto* transformComponent	= Object::GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		auto* renderComponent		= Object::GetComponent<RenderComponent>(ComponentType::RENDER_COMPONENT);
		auto* rotationComponent		= Object::GetComponent<RotationComponent>(ComponentType::ROTATION_COMPONENT);
		
		MyVector2& position		= transformComponent->position;
		auto& renderPoints		= renderComponent->points;
	}

	void Bullet::Update()
	{
	}
}

#include "Star.h"
#include "Component.h"
#include "CameraState.h"
#include "PlayerState.h"
#include <memory>
#include <algorithm>

namespace astro
{
	Star::Star(const MyVector2& position)
	{
		Object::AddComponent(std::make_shared<TransformComponent>(position));
		Object::AddComponent(std::make_shared<MoveComponent>());
		Object::AddComponent(std::make_shared<RenderComponent>());
		Object::AddComponent(std::make_shared<EffectComponent>());
		Object::AddComponent(std::make_shared<WarpComponent>());
	}

	void Star::Init()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
		auto* effectComponent = Object::GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);

		if (renderComponent && transformComponent && effectComponent)
		{
			float margin = 300.f;
			std::uniform_real_distribution<float> randPosX(-margin, astro::SCREEN_WIDTH + margin);
			std::uniform_real_distribution<float> randPosY(-margin, astro::SCREEN_HEIGHT + margin);

			effectComponent->bright = Random::randBright(Random::gen);
			effectComponent->twinkle = Random::randTwinkle(Random::gen);

			Color starColors[] = {
				{150, 180, 255, 255}, // 파란 별 (뜨거움)
				{200, 220, 255, 255}, // 연한 파랑
				{255, 245, 235, 255}, // 흰색 (태양 비슷)
				{255, 255, 200, 255}, // 연한 노랑
				{255, 200, 150, 255}, // 주황색
				{255, 150, 100, 255}  // 붉은 별 (차가움)
			};
			effectComponent->color = starColors[Random::randColor(Random::gen)];

			transformComponent->size = Random::randSize(Random::gen);
			transformComponent->position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			float sizeRatio = (transformComponent->size - MIN_STAR_SIZE) / (MAX_STAR_SIZE - MIN_STAR_SIZE);
			effectComponent->distanceDepth = 1.0f - sizeRatio;
			effectComponent->maxSize = transformComponent->size;
			effectComponent->distanceDepth = std::clamp(effectComponent->distanceDepth, 0.1f, 1.0f);

			renderComponent->points.push_back(transformComponent->position);
		}
	}

	void Star::Update()
	{
		auto* transformComponent = Object::GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
		MyVector2& position = transformComponent->position;

		Move();

		Bound bound = CalculaterBoundLine();
		IsLineOut isLineOut = CheckCameraRangeOut(bound, position);
		
		SetRandomPosition(bound, isLineOut, position);
	}

	void Star::Move()
	{
		auto* moveComponent = Object::GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT);
		auto* effectComponent = Object::GetComponent<EffectComponent>(ComponentID::EFFECT_COMPONENT);
		
		if (moveComponent && effectComponent)
		{
			std::shared_ptr<Player> player = PlayerState::Instance().GetPlayer();

			const MyVector2& playerMoveDirection = player.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT)->direction;
			const float& playerSpeed = player.get()->GetComponent<MoveComponent>(ComponentID::MOVE_COMPONENT)->speed;

			const float& depth = effectComponent->distanceDepth;

			moveComponent->direction = playerMoveDirection;
			moveComponent->speed = playerSpeed * depth;
		}
	}

	Star::IsLineOut Star::CheckCameraRangeOut(Bound bound, const MyVector2& position)
	{
		float margin = 300.f;

		return IsLineOut{ position.x() <= bound.left - margin,
					position.x() >= bound.right + margin,
					position.y() <= bound.top - margin,
					position.y() >= bound.bottom + margin 
		};
	}

	Star::Bound Star::CalculaterBoundLine()
	{
		const Camera2D& camera = CameraState::Instance().GetCamera();
		const MyVector2& cameraTarget = camera.target;
		MyVector2 viewScreen = ViewScreenSize();
		viewScreen /= 2.f;

		float leftBound = cameraTarget.x() - viewScreen.x();
		float rightBound = cameraTarget.x() + viewScreen.x();
		float topBound = cameraTarget.y() - viewScreen.y();
		float bottomBound = cameraTarget.y() + viewScreen.y();

		return Bound{ leftBound, rightBound, topBound, bottomBound };
	}

	void Star::SetRandomPosition(Bound bound, IsLineOut isLineOut, MyVector2& position)
	{
		auto* renderComponent = Object::GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);

		float margin = 300.f;
		Rectangle spotRange{ 0,0,0,0 };
		const MyVector2& viewScreen = ViewScreenSize();

		if (isLineOut.left)
		{
			spotRange = { bound.right, bound.top, margin, viewScreen.y()};
		}
		else if (isLineOut.right)
		{
			spotRange = { bound.left - margin, bound.top, margin, viewScreen.y()};
		}
		else if (isLineOut.top)
		{
			spotRange = { bound.left, bound.bottom, viewScreen.x(), margin};
		}
		else if (isLineOut.bottom)
		{
			spotRange = { bound.left, bound.top - margin, viewScreen.x(), margin};
		}

		if (isLineOut.left || isLineOut.right || isLineOut.top || isLineOut.bottom)
		{
			std::uniform_real_distribution<float> randPosX(spotRange.x, spotRange.x + spotRange.width);
			std::uniform_real_distribution<float> randPosY(spotRange.y, spotRange.y + spotRange.height);

			position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			auto& points = renderComponent->points;
			MyVector2 jumpPoint{ 0, 0 };

			for (size_t i = 0; i < points.size(); i++)
			{
				if (i == 0)
				{
					jumpPoint = position - points[i];
					points[i] = position;
				}
				else
				{
					points[i] += jumpPoint;
				}
			}
		}
	}

	const MyVector2& Star::ViewScreenSize()
	{
		const Camera2D& camera = CameraState::Instance().GetCamera();
		const float& zoom = camera.zoom;

		float viewWidth = SCREEN_WIDTH / zoom;
		float viewHeight = SCREEN_HEIGHT / zoom;

		return MyVector2{ viewWidth, viewHeight };
	}
}

#include "StarSystem.h"
#include "ComponentManager.h"
#include "PlayerState.h"
#include "CameraState.h"

namespace astro
{ 
	void StarSystem::Init()
	{
	}

	void StarSystem::Process()
	{
		auto& CM = ComponentManager::Instance();
		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::TRANSFORM_COMPONENT |
									ComponentType::ACTIVE_COMPONENT |
									ComponentType::BRIGHT_EFFECT_COMPONENT |
									ComponentType::MOVE_COMPONENT)
		);

		for (auto& archetype : archetypes)
		{ 
			auto* activeComponents			= archetype->GetComponents<ActiveComponent>();
			auto* transformComponents		= archetype->GetComponents<TransformComponent>();
			auto* brightEffectComponents	= archetype->GetComponents<BrightEffectComponent>();
			auto* moveComponents			= archetype->GetComponents<MoveComponent>();

			if (activeComponents && transformComponents && brightEffectComponents && moveComponents)
			{ 
				std::shared_ptr<Player> player = PlayerState::Instance().GetPlayer();
				InstanceID playerId = player.get()->GetInstanceID();
				uint64_t componentMask = player.get()->GetComponentMask();

				const MyVector2& playerMoveDirection = CM.GetComponent<MoveComponent>(componentMask, playerId)->direction;
				const float& playerSpeed = CM.GetComponent<MoveComponent>(componentMask, playerId)->speed;

				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					if (activeComponents[i].enable)
					{ 
						MyVector2& localPosition = transformComponents[i].localPosition;
						const float& depth = brightEffectComponents[i].distanceDepth;

						moveComponents[i].direction = playerMoveDirection;
						moveComponents[i].speed = playerSpeed * depth;

						Bound bound = CalculaterBoundLine();
						IsLineOut isLineOut = CheckCameraRangeOut(bound, localPosition);

						SetRandomPosition(bound, isLineOut, localPosition);
					}
				}
			}
		}
	}

	StarSystem::IsLineOut StarSystem::CheckCameraRangeOut(Bound bound, const MyVector2& position)
	{
		float margin = 300.f;

		return IsLineOut{ position.x() <= bound.left - margin,
					position.x() >= bound.right + margin,
					position.y() <= bound.top - margin,
					position.y() >= bound.bottom + margin
		};
	}

	StarSystem::Bound StarSystem::CalculaterBoundLine()
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

	void StarSystem::SetRandomPosition(Bound bound, IsLineOut isLineOut, MyVector2& position)
	{
		float margin = 300.f;
		Rectangle spotRange{ 0,0,0,0 };
		const MyVector2& viewScreen = ViewScreenSize();

		if (isLineOut.left)
		{
			spotRange = { bound.right, bound.top, margin, viewScreen.y() };
		}
		else if (isLineOut.right)
		{
			spotRange = { bound.left - margin, bound.top, margin, viewScreen.y() };
		}
		else if (isLineOut.top)
		{
			spotRange = { bound.left, bound.bottom, viewScreen.x(), margin };
		}
		else if (isLineOut.bottom)
		{
			spotRange = { bound.left, bound.top - margin, viewScreen.x(), margin };
		}

		if (isLineOut.left || isLineOut.right || isLineOut.top || isLineOut.bottom)
		{
			std::uniform_real_distribution<float> randPosX(spotRange.x, spotRange.x + spotRange.width);
			std::uniform_real_distribution<float> randPosY(spotRange.y, spotRange.y + spotRange.height);

			position = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };
		}
	}

	MyVector2 StarSystem::ViewScreenSize()
	{
		const Camera2D& camera = CameraState::Instance().GetCamera();
		float zoom = camera.zoom;

		zoom = zoom == 0.f ? 1.f : zoom;

		return { SCREEN_WIDTH / zoom, SCREEN_HEIGHT / zoom };
	}
}

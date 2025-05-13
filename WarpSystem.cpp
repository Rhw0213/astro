#include "WarpSystem.h"
#include "Component.h"
#include "EventManager.h"
#include "Event.h"
#include "PlayerState.h"
#include "Setting.h"
#include "ComponentManager.h"

namespace astro
{
    void WarpSystem::Init()
    {
		EventManager::Instance().RegisterEvent<WarpStartEvent>([](const WarpStartEvent* e) {
			auto& setting = GameSettingManager::Instance();
			auto& CM = ComponentManager::Instance();

			auto archetypes = CM.GetArchetypeQuery(
				static_cast<uint64_t>(ComponentType::RENDER_COMPONENT |
										ComponentType::TRANSFORM_COMPONENT |
										ComponentType::WARP_COMPONENT)
			);

			for (auto& archetype: archetypes)
			{
				auto* renderComponents = archetype->GetComponents<RenderComponent>();
				auto* transformComponents = archetype->GetComponents<TransformComponent>();
				auto* warpComponents = archetype->GetComponents<WarpComponent>();

				if (renderComponents && transformComponents && warpComponents)
				{
					for (size_t i = 0; i < archetype->objectCount; i++)
					{
						auto& renderComponent = renderComponents[i];
						auto& transformComponent = transformComponents[i];
						auto& warpComponent = warpComponents[i];

						auto& renderPoints = renderComponent.points;
						bool& isWarp = warpComponent.isWarp;
						float localScale = transformComponent.localScale;

						uint64_t playerMask = PlayerState::Instance().GetPlayer()->GetComponentMask();
						InstanceID playerInstanceId = PlayerState::Instance().GetPlayer()->GetInstanceID();

						const Angle& localRotation = CM.GetComponent<TransformComponent>(playerMask, playerInstanceId)->localRotation;
						MyVector2		effectDirection = { -cosf(localRotation.radian), -sinf(localRotation.radian) };
						MyVector2		effectLine = effectDirection.Normalize() * 2.f;

						renderPoints.push_back({ 0,0 });
						renderPoints.push_back(effectLine * localScale * setting.warpStarTailLength);

						isWarp = true;
					}
				}
			}
		});

		EventManager::Instance().RegisterEvent<WarpStopEvent>([](const WarpStopEvent* e) {
			auto& CM = ComponentManager::Instance();
			auto archetypes = CM.GetArchetypeQuery(
				static_cast<uint64_t>(ComponentType::WARP_COMPONENT)
			);

			for (auto& archetype: archetypes)
			{
				auto* warpComponents = archetype->GetComponents<WarpComponent>();

				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					auto& warpComponent = warpComponents[i];
					warpComponent.isWarp = false;
				}
			}
		});
    }

    void WarpSystem::Process()
	{
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::RENDER_COMPONENT |
									ComponentType::TRANSFORM_COMPONENT |
									ComponentType::WARP_COMPONENT)
		);

        for (auto& archetype: archetypes)
        {
			auto* renderComponents = archetype->GetComponents<RenderComponent>();
			auto* transformComponents = archetype->GetComponents<TransformComponent>();
			auto* warpComponents = archetype->GetComponents<WarpComponent>();

			if (renderComponents && transformComponents && warpComponents)
			{
				for (size_t i = 0; i < archetype->objectCount; i++)
				{
					auto& renderComponent = renderComponents[i];
					auto& transformComponent = transformComponents[i];
					auto& warpComponent = warpComponents[i];

					auto&	renderPoints	= renderComponent.points;
					float	localScale		= transformComponent.localScale;
					bool	isWarp			= warpComponent.isWarp;

					if (isWarp)
					{
						EventManager::Instance().RunEvent(CameraZoomEvent(0.7f, 0.02f));

						float distance = renderPoints[1].Distance(renderPoints[2]);

						if (distance < localScale * 3.f)
						{
							//renderPoints[2] *= 1.01f;
						}
					}
					else if (!isWarp && renderPoints.size() >= 3)
					{
						float distance = renderPoints[1].Distance(renderPoints[2]);
						renderPoints[2] *= 0.9f;

						if (distance < 3.f)
						{
							renderPoints.clear();

							renderPoints.push_back({ 0, 0 });
							EventManager::Instance().RunEvent(CameraZoomEvent(1.f, 0.02f));
						}
					}
				}
			}
        }
	}
}

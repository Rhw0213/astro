#include "BrightEffectSystem.h"
#include "Component.h"
#include "PlayerState.h"
#include "ComponentManager.h"

namespace astro
{
    void BrightEffectSystem::Init()
    {
    }

    void BrightEffectSystem::Process()
    {
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::TRANSFORM_COMPONENT |
									ComponentType::BRIGHT_EFFECT_COMPONENT)
		);

        for (auto& archetype : archetypes)
        {
			auto* transformComponents = archetype->GetComponents<TransformComponent>();
			auto* brightEffectComponents = archetype->GetComponents<BrightEffectComponent>();

            if (transformComponents && brightEffectComponents)
            {
				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					auto& effectComponent = brightEffectComponents[i];
					auto& transformComponent = transformComponents[i];

					int& bright = effectComponent.bright;
					float& twinkle = effectComponent.twinkle;
					float& time = effectComponent.time;
					float& localScale = transformComponent.localScale;
					float maxSize = effectComponent.maxSize;

					// 반짝이는 효과
					time += GetFrameTime() * twinkle;
					localScale = maxSize * ((sinf(time) * 0.5f) + 0.5f);
					bright = static_cast<int>(127 + 127 * sinf(time));
				}
            }
        }
    }
}

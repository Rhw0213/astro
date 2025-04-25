#include "BrightEffectSystem.h"
#include "Component.h"
#include "PlayerState.h"

namespace astro
{
    void BrightEffectSystem::Init()
    {
    }

    void BrightEffectSystem::Process()
    {
        for (const auto& object : objects)
        {
            if (object && object.get()->IsEnable())
            {
                auto* effectComponent = object.get()->GetComponent<BrightEffectComponent>(ComponentType::BRIGHT_EFFECT_COMPONENT);
                auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

                int& bright = effectComponent->bright;
                float& twinkle = effectComponent->twinkle;
                float& time = effectComponent->time;
                float& size = transformComponent->size;
                float maxSize = effectComponent->maxSize;

                // 반짝이는 효과
                time += GetFrameTime() * twinkle;
                size = maxSize * ((sinf(time) * 0.5f) + 0.5f);
                bright = static_cast<int>(127 + 127 * sinf(time));
            }
        }
    }
}

#include "Star.h"
#include "Component.h"
#include "CameraState.h"
#include "PlayerState.h"
#include "Setting.h"
#include "ComponentManager.h"
#include <memory>
#include <algorithm>
#include <iostream>

namespace astro
{
	Star::Star(InstanceID parentId)
	{
		componentMask = static_cast<uint64_t>(
			ComponentType::ACTIVE_COMPONENT |
			ComponentType::TRANSFORM_COMPONENT |
			ComponentType::MOVE_COMPONENT |
			ComponentType::RENDER_COMPONENT |
			ComponentType::BRIGHT_EFFECT_COMPONENT |
			ComponentType::WARP_COMPONENT
			);
	}

	void Star::Init()
	{
		auto& setting	= GameSettingManager::Instance();
		auto& CM		= ComponentManager::Instance();

		auto* transformComponent	= CM.GetComponent<TransformComponent>	(componentMask, instanceId);
		auto* renderComponent		= CM.GetComponent<RenderComponent>		(componentMask, instanceId);
		auto* brightEffectComponent = CM.GetComponent<BrightEffectComponent>(componentMask, instanceId);

		if (renderComponent && transformComponent && brightEffectComponent)
		{
			float margin = 300.f;
			std::uniform_real_distribution<float> randPosX(-(SCREEN_WIDTH / 2.f) - margin, astro::SCREEN_WIDTH / 2.f + margin);
			std::uniform_real_distribution<float> randPosY(-(SCREEN_HEIGHT / 2.f) - margin, astro::SCREEN_HEIGHT /2.f + margin);
			//std::uniform_real_distribution<float> randPosX(0, SCREEN_WIDTH);
			//std::uniform_real_distribution<float> randPosY(0, SCREEN_HEIGHT);

			brightEffectComponent->bright = Random::randBright(Random::gen);
			brightEffectComponent->twinkle = Random::randTwinkle(Random::gen);

			Color starColors[] = {
				{150, 180, 255, 255}, // 파란 별 (뜨거움)
				{200, 220, 255, 255}, // 연한 파랑
				{255, 245, 235, 255}, // 흰색 (태양 비슷)
				{255, 255, 200, 255}, // 연한 노랑
				{255, 200, 150, 255}, // 주황색
				{255, 150, 100, 255}  // 붉은 별 (차가움)
			};
			brightEffectComponent->color = starColors[Random::randColor(Random::gen)];

			transformComponent->localScale = Random::randSize(Random::gen);
			transformComponent->localPosition = MyVector2{ randPosX(Random::gen), randPosY(Random::gen) };

			float sizeRatio = (transformComponent->localScale - setting.minStarSize) 
								/ (setting.maxStarSize- setting.minStarSize);

			brightEffectComponent->distanceDepth	= 1.0f - sizeRatio;
			brightEffectComponent->maxSize			= transformComponent->localScale;
			brightEffectComponent->distanceDepth	= std::clamp(brightEffectComponent->distanceDepth, 0.1f, 1.0f);

			renderComponent->points.push_back({0, 0});
			renderComponent->objectType = ObjectType::STAR_ID;
		}
	}

	void Star::Update()
	{
	}
}

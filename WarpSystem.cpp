#include "WarpSystem.h"
#include "Component.h"
#include "EventManager.h"
#include "Event.h"
#include "PlayerState.h"

namespace astro
{
    void WarpSystem::Init()
    {
        for (const auto& object : objects)
        {
            EventManager::Instance().RegisterEvent<WarpStartEvent>([&](const WarpStartEvent* e)
                {
                    auto* renderComponent = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
                    auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
                    auto* warpComponent = object.get()->GetComponent<WarpComponent>(ComponentID::WARP_COMPONENT);

                    auto& points = renderComponent->points;
                    float size = transformComponent->size;
                    bool& isWarp = warpComponent->isWarp;

                    MyVector2 effectDirection =
                        PlayerState::Instance()
                        .GetPlayer()
                        .get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT)->direction;
                    effectDirection *= -1.0f;

                    MyVector2 effectLine = effectDirection * 2.f;
                    MyVector2 startPoint = transformComponent->position;
                    MyVector2 endPoint = startPoint + effectLine;

                    points.push_back(startPoint);
                    points.push_back(endPoint);

                    isWarp = true;
                }
            );

            EventManager::Instance().RegisterEvent<WarpStopEvent>([&](const WarpStopEvent* e) {
                auto* warpComponent = object.get()->GetComponent<WarpComponent>(ComponentID::WARP_COMPONENT);
                warpComponent->isWarp = false;
            });
        }
    }

    void WarpSystem::Process()
	{
        for (const auto& object : objects)
        {
            auto* renderComponent = object.get()->GetComponent<RenderComponent>(ComponentID::RENDER_COMPONENT);
            auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);
            auto* warpComponent = object.get()->GetComponent<WarpComponent>(ComponentID::WARP_COMPONENT);

            auto& points = renderComponent->points;
            float size = transformComponent->size;
            bool isWarp = warpComponent->isWarp;

            if (object && renderComponent && transformComponent)
            {
                if (isWarp)
                {
                    EventManager::Instance().RunEvent(CameraZoomEvent(0.7f, 0.02f));

                    float distance = points[1].Distance(points[2]);
                    MyVector2 pointTwoDirection = points[1].DirectionTo(points[2]);

                    if (distance < size * 30.f)
                    {
                        points[2] += pointTwoDirection * size * 2.f;
                    }
                }
                else if (!isWarp && points.size() >= 3)
                {
                    float distance = points[1].Distance(points[2]);
                    MyVector2 pointOneDirection = points[2].DirectionTo(points[1]);
                    points[2] += (pointOneDirection * 3.f);

                    if (distance < 3.f)
                    {
                        const MyVector2& point = points[0];
                        points.clear();
                        points.push_back(point);
						EventManager::Instance().RunEvent(CameraZoomEvent(1.f, 0.02f));
                    }
                }
            }
        }
	}
}

#include "CameraSystem.h"
#include "CameraState.h"
#include "Component.h"
#include "EventManager.h"

namespace astro
{
	void CameraSystem::Init()
	{
		for (const auto& object : objects)
		{
			if (object)
			{
				auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);
				Camera2D& camera = cameraComponent->camera;
				float& targetZoom = cameraComponent->targetZoom;
				
				targetZoom = camera.zoom;

				EventManager::Instance().RegisterEvent<CameraZoomEvent>([&](const CameraZoomEvent* e) {
					auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);
					float& targetZoom = cameraComponent->targetZoom;
					float& zoomSpeed = cameraComponent->zoomSpeed;

					targetZoom = e->targetZoom;
					zoomSpeed = e->zoomSpeed;
				});
			}
		}
	}

	void CameraSystem::Process()
	{
		for (const auto& object : objects)
		{
			if (object)
			{
				auto* cameraComponent = object.get()->GetComponent<CameraComponent>(ComponentID::CAMERA_COMPONENT);
				auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentID::TRANSFORM_COMPONENT);

				Camera2D& camera = cameraComponent->camera;
				float& zoom = camera.zoom;
				float targetZoom = cameraComponent->targetZoom;
				float zoomSpeed = cameraComponent->zoomSpeed;
				const MyVector2& position = transformComponent->position;

				camera.target = position;

				if (std::abs(zoom - targetZoom) > 0.02f)
				{
					zoomSpeed = targetZoom - zoom > 0 ? zoomSpeed : -zoomSpeed;
					zoom += zoomSpeed;
				}

				CameraState::Instance().Update(camera);
			}
		}
	}
}

#include "CameraSystem.h"
#include "CameraState.h"
#include "Component.h"
#include "EventManager.h"
#include "ComponentManager.h"
#include "PlayerState.h"

namespace astro
{
	void CameraSystem::Init()
	{
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t>(ComponentType::CAMERA_COMPONENT)
		);

		for (auto* archetype : archetypes)
		{ 
			auto* cameraComponents = archetype->GetComponents<CameraComponent>();

			if (cameraComponents)
			{ 
				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					auto& cameraComponent = cameraComponents[i];

					Camera2D& camera = cameraComponent.camera;
					float& targetZoom = cameraComponent.targetZoom;
					
					targetZoom = camera.zoom;

					EventManager::Instance().RegisterEvent<CameraZoomEvent>([&](const CameraZoomEvent* e) {

						//?
						InstanceID instanceId = PlayerState::Instance().GetPlayer().get()->GetInstanceID();
						uint64_t componentMask = PlayerState::Instance().GetPlayer().get()->GetComponentMask();

						auto* cameraComponent = CM.GetComponent<CameraComponent>(componentMask, instanceId);
						float& targetZoom = cameraComponent->targetZoom;
						float& zoomSpeed = cameraComponent->zoomSpeed;

						targetZoom = e->targetZoom;
						zoomSpeed = e->zoomSpeed;
					});
				}
			}
		}
	}

	void CameraSystem::Process()
	{
		auto& CM = ComponentManager::Instance();

		auto archetypes = CM.GetArchetypeQuery(
			static_cast<uint64_t> (ComponentType::TRANSFORM_COMPONENT | 
									ComponentType::CAMERA_COMPONENT)
		);

		for (auto* archetype : archetypes)
		{ 
			auto* cameraComponents = archetype->GetComponents<CameraComponent>();
			auto* transformComponents = archetype->GetComponents<TransformComponent>();

			if (cameraComponents && transformComponents)
			{ 
				for (size_t i = 0; i < archetype->objectCount; i++)
				{ 
					auto& cameraComponent = cameraComponents[i];
					auto& transformComponent = transformComponents[i];

					Camera2D& camera				= cameraComponent.camera;
					float& zoom						= camera.zoom;
					float targetZoom				= cameraComponent.targetZoom;
					float zoomSpeed					= cameraComponent.zoomSpeed;
					const MyVector2& localPosition	= transformComponent.localPosition;

					camera.target = localPosition;

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
}

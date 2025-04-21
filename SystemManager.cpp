#include "SystemManager.h"
#include "CameraSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "RotationSystem.h"
#include "StarEffectSystem.h"
#include "WarpSystem.h"
#include "RenderSystem.h"

namespace astro
{
	SystemManager::SystemManager()
	{
		RegisterSystem<InputSystem>(std::make_shared<InputSystem>());
		RegisterSystem<CameraSystem>(std::make_shared<CameraSystem>());
		RegisterSystem<MoveSystem>(std::make_shared<MoveSystem>());
		RegisterSystem<StarEffectSystem>(std::make_shared<StarEffectSystem>());
		RegisterSystem<WarpSystem>(std::make_shared<WarpSystem>());
		RegisterSystem<RotationSystem>(std::make_shared<RotationSystem>());
		RegisterSystem<RenderSystem>(std::make_shared<RenderSystem>());
		RegisterSystem<ShaderSystem>(std::make_shared<ShaderSystem>());
	}

	void SystemManager::Init()
	{
		for (const auto& system : systems)
		{
			system.get()->Init();
		}
	}

	void SystemManager::Update()
	{
		for (size_t i = 0; i <= ROTATION_SYSTEM; i++)
		{
			systems[i].get()->Process();
		}
	}

	void SystemManager::Draw()
	{
		BeginDrawing();

		for (size_t i = RENDER_SYSTEM; i <= SHADER_SYSTEM; i++)
		{
			systems[i].get()->Process();
		}

		EndDrawing();
	}
}

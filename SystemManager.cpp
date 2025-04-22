#include "SystemManager.h"
#include "CameraSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "RotationSystem.h"
#include "BrightEffectSystem.h"
#include "WarpSystem.h"
#include "RenderSystem.h"
#include "FrameSystem.h"

namespace astro
{
	SystemManager::SystemManager()
	{
		RegisterSystem<InputSystem>(SystemID::INPUT_SYSTEM, std::make_shared<InputSystem>());
		systemRequirement.insert({ SystemID::INPUT_SYSTEM,{
									static_cast< unsigned int >
									(
										ComponentType::INPUT_COMPONENT
									), RegisterLogic::ALL}
			});

		RegisterSystem<CameraSystem>(SystemID::CAMERA_SYSTEM, std::make_shared<CameraSystem>());
		systemRequirement.insert({ SystemID::CAMERA_SYSTEM,{
									static_cast< unsigned int >
									(
										ComponentType::CAMERA_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<MoveSystem>(SystemID::MOVE_SYSTEM, std::make_shared<MoveSystem>());
		systemRequirement.insert({ SystemID::MOVE_SYSTEM,{
									static_cast< unsigned int >
									(
										ComponentType::MOVE_COMPONENT |
										ComponentType::TRANSFORM_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<BrightEffectSystem>(SystemID::BRIGHT_EFFECT_SYSTEM, std::make_shared<BrightEffectSystem>());
		systemRequirement.insert({ SystemID::BRIGHT_EFFECT_SYSTEM, {
									static_cast< unsigned int >
									(
										ComponentType::BRIGHT_EFFECT_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<WarpSystem>(SystemID::WARP_SYSTEM, std::make_shared<WarpSystem>());
		systemRequirement.insert({ SystemID::WARP_SYSTEM, {
									static_cast< unsigned int >
									(
										ComponentType::WARP_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<RotationSystem>(SystemID::ROTATION_SYSTEM, std::make_shared<RotationSystem>());
		systemRequirement.insert({ SystemID::ROTATION_SYSTEM,{
									static_cast< unsigned int >
									(
										ComponentType::ROTATION_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<FrameSystem>(SystemID::FRAME_SYSTEM, std::make_shared<FrameSystem>());
		systemRequirement.insert({ SystemID::FRAME_SYSTEM,{
									static_cast< unsigned int >
									(
										ComponentType::FRAME_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<RenderSystem>(SystemID::RENDER_SYSTEM, std::make_shared<RenderSystem>());
		systemRequirement.insert({ SystemID::RENDER_SYSTEM, {
									static_cast< unsigned int >
									(
										ComponentType::RENDER_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<ShaderSystem>(SystemID::SHADER_SYSTEM, std::make_shared<ShaderSystem>());
		systemRequirement.insert({ SystemID::SHADER_SYSTEM, {
									static_cast< unsigned int >
									(
										ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT |
										ComponentType::SHADER_FRAME_COMPONENT
									), RegisterLogic::ANY}
		});
	}

	void SystemManager::RegisterObjectOfSystem(std::shared_ptr<GameObject> gameObject)
	{
		unsigned int gameObjectMask = gameObject.get()->GetComponentMask();
		std::bitset<64> bits(gameObjectMask);

		for (const auto& [systemId, systemMask] : systemRequirement)
		{
			bool isRegisterObject = false;

			if (systemMask.registerLogic == RegisterLogic::ANY)
			{
				if (gameObjectMask & systemMask.mask)
				{
					isRegisterObject = true;
				}
			}
			else if (systemMask.registerLogic == RegisterLogic::ALL)
			{
				if ((gameObjectMask & systemMask.mask) == systemMask.mask)
				{
					isRegisterObject = true;
				}
			}
			
			if (isRegisterObject)
			{
				auto it = systems.find(systemId);

				if (it != systems.end())
				{
					it->second.get()->RegisterObject(gameObject);
				}
			}
		}

	}

	void SystemManager::Init()
	{
		for (const auto& [_, system]: systems)
		{
			system.get()->Init();
		}
	}

	void SystemManager::Update()
	{
		for (const auto& [systemId, system]: systems)
		{
			if (systemId != SystemID::RENDER_SYSTEM && systemId != SystemID::SHADER_SYSTEM)
			{
				system.get()->Process();
			}
		}
	}

	void SystemManager::Draw()
	{
		BeginDrawing();
		for ( const auto& [systemId , system] : systems )
		{
			if (systemId == SystemID::RENDER_SYSTEM || systemId == SystemID::SHADER_SYSTEM)
			{
				system.get()->Process();
			}
		}

		EndDrawing();
	}
}

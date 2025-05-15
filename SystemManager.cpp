#include "SystemManager.h"
#include "CameraSystem.h"
#include "InputSystem.h"
#include "StarSystem.h"
#include "TransformSystem.h"
#include "MoveSystem.h"
#include "BrightEffectSystem.h"
#include "WarpSystem.h"
#include "RenderSystem.h"
#include "FrameSystem.h"
#include "FrameManageSystem.h"
#include "MissileSystem.h"

namespace astro
{
	SystemManager::SystemManager(std::shared_ptr<ObjectManager> objectManager)
		: objectManager(objectManager)
	{
		RegisterSystem<InputSystem>(SystemID::INPUT_SYSTEM, std::make_shared<InputSystem>());
		systemRequirement.insert({ SystemID::INPUT_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::INPUT_COMPONENT
									), RegisterLogic::ALL}
			});

		RegisterSystem<MissileSystem>(SystemID::MISSILE_SYSTEM, std::make_shared<MissileSystem>(objectManager));
		systemRequirement.insert({ SystemID::MISSILE_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::MISSILE_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<StarSystem>(SystemID::STAR_SYSTEM, std::make_shared<StarSystem>());
		systemRequirement.insert({ SystemID::STAR_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::ACTIVE_COMPONENT |
										ComponentType::TRANSFORM_COMPONENT |
										ComponentType::MOVE_COMPONENT |
										ComponentType::RENDER_COMPONENT |
										ComponentType::BRIGHT_EFFECT_COMPONENT |
										ComponentType::WARP_COMPONENT
									), RegisterLogic::ALL}
			});

		RegisterSystem<MoveSystem>(SystemID::MOVE_SYSTEM, std::make_shared<MoveSystem>());
		systemRequirement.insert({ SystemID::MOVE_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::MOVE_COMPONENT |
										ComponentType::TRANSFORM_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<TransformSystem>(SystemID::TRANSFORM_SYSTEM, std::make_shared<TransformSystem>(objectManager));
		systemRequirement.insert({ SystemID::TRANSFORM_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::TRANSFORM_COMPONENT
									), RegisterLogic::ALL}
			});

		RegisterSystem<BrightEffectSystem>(SystemID::BRIGHT_EFFECT_SYSTEM, std::make_shared<BrightEffectSystem>());
		systemRequirement.insert({ SystemID::BRIGHT_EFFECT_SYSTEM, {
									static_cast< uint64_t >
									(
										ComponentType::BRIGHT_EFFECT_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<WarpSystem>(SystemID::WARP_SYSTEM, std::make_shared<WarpSystem>());
		systemRequirement.insert({ SystemID::WARP_SYSTEM, {
									static_cast< uint64_t >
									(
										ComponentType::WARP_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<FrameManageSystem>(SystemID::FRAME_MANAGE_SYSTEM, std::make_shared<FrameManageSystem>(objectManager));
		systemRequirement.insert({ SystemID::FRAME_MANAGE_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::FRAME_MANAGE_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<FrameSystem>(SystemID::FRAME_SYSTEM, std::make_shared<FrameSystem>(objectManager));
		systemRequirement.insert({ SystemID::FRAME_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::FRAME_COMPONENT 
									), RegisterLogic::ALL}
		});



		RegisterSystem<CameraSystem>(SystemID::CAMERA_SYSTEM, std::make_shared<CameraSystem>());
		systemRequirement.insert({ SystemID::CAMERA_SYSTEM,{
									static_cast< uint64_t >
									(
										ComponentType::CAMERA_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<RenderSystem>(SystemID::RENDER_SYSTEM, std::make_shared<RenderSystem>());
		systemRequirement.insert({ SystemID::RENDER_SYSTEM, {
									static_cast< uint64_t >
									(
										ComponentType::RENDER_COMPONENT
									), RegisterLogic::ALL}
		});

		RegisterSystem<ShaderSystem>(SystemID::SHADER_SYSTEM, std::make_shared<ShaderSystem>());
		systemRequirement.insert({ SystemID::SHADER_SYSTEM, {
									static_cast< uint64_t >
									(
										ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT |
										ComponentType::SHADER_FRAME_COMPONENT
									), RegisterLogic::ANY}
		});
	}

	void SystemManager::RegisterObjectOfSystem(std::shared_ptr<Object> gameObject)
	{
		//uint64_t gameObjectMask = gameObject.get()->GetComponentMask();
		//std::bitset<64> bits(gameObjectMask);

		//for (const auto& [systemId, systemMask] : systemRequirement)
		//{
		//	bool isRegisterObject = false;

		//	if (systemMask.registerLogic == RegisterLogic::ANY)
		//	{
		//		if ((gameObjectMask & systemMask.mask) != 0)
		//		{
		//			isRegisterObject = true;
		//		}
		//	}
		//	else if (systemMask.registerLogic == RegisterLogic::ALL)
		//	{
		//		if ((gameObjectMask & systemMask.mask) == systemMask.mask)
		//		{
		//			isRegisterObject = true;
		//		}
		//	}
			
			//if (isRegisterObject)
			//{
			//	auto it = systems.find(systemId);

			//	if (it != systems.end())
			//	{
			//		it->second.get()->RegisterObject(gameObject);
			//	}
			//}
		//}
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
		for (const auto& [systemId , system] : systems)
		{
			if (systemId == SystemID::RENDER_SYSTEM || systemId == SystemID::SHADER_SYSTEM)
			{
				system.get()->Process();
			}
		}
	}
}

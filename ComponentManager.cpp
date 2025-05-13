#include "ComponentManager.h"
#include "Component.h"

#define REGISTER_COMPONENT(Type, ComponentStruct)						\
		if ((bitmask & static_cast<uint64_t>(Type)) != 0)				\
		{																\
			RegisterData<ComponentStruct>(bitmask, instanceId);	\
		}

namespace astro
{ 
	std::vector<Archetype*> ComponentManager::GetArchetypeQuery(uint64_t bitMask)
	{
		auto cacheIt = queryCache.find(bitMask);

		if (cacheIt != queryCache.end())
		{
			return cacheIt->second.matchingArchetypes;
		}
		
		std::vector<Archetype*> result;
		for (auto& archetype : archetypes)
		{
			if ((archetype.typeMask & bitMask) == bitMask)
			{
				result.push_back(&archetype);
			}
		}

		queryCache[bitMask].matchingArchetypes = result;

		return result;
	}

	ComponentManager::~ComponentManager()
	{
		for (auto& archetype : archetypes)
		{
			archetype.DestoryComponentData();
		}
	}

	void ComponentManager::RegisterComponent(uint64_t bitmask, InstanceID instanceId)
	{
		REGISTER_COMPONENT(ComponentType::TRANSFORM_COMPONENT, TransformComponent);
		REGISTER_COMPONENT(ComponentType::ACTIVE_COMPONENT, ActiveComponent);
		REGISTER_COMPONENT(ComponentType::RENDER_COMPONENT, RenderComponent);
		REGISTER_COMPONENT(ComponentType::MOVE_COMPONENT, MoveComponent);
		REGISTER_COMPONENT(ComponentType::INPUT_COMPONENT, InputComponent);
		REGISTER_COMPONENT(ComponentType::BRIGHT_EFFECT_COMPONENT, BrightEffectComponent);
		REGISTER_COMPONENT(ComponentType::CAMERA_COMPONENT, CameraComponent);
		REGISTER_COMPONENT(ComponentType::WARP_COMPONENT, WarpComponent);
		REGISTER_COMPONENT(ComponentType::UI_COMPONENT, UIComponent);
		REGISTER_COMPONENT(ComponentType::FRAME_COMPONENT, FrameComponent);
		REGISTER_COMPONENT(ComponentType::FRAME_MANAGE_COMPONENT, FrameManageComponent);
		REGISTER_COMPONENT(ComponentType::MISSILE_COMPONENT, MissileComponent);
		REGISTER_COMPONENT(ComponentType::SHADER_COMPONENT, ShaderComponent);
		REGISTER_COMPONENT(ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT, ShaderColorDiffusionComponent);
		REGISTER_COMPONENT(ComponentType::SHADER_FRAME_COMPONENT, ShaderFrameComponent);
	}
}

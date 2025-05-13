#include "FrameManage.h"
#include "Component.h"
#include "ComponentManager.h"

namespace astro
{
	FrameManage::FrameManage(InstanceID frameOwner)
		:frameOwner(frameOwner)
	{
		componentMask = static_cast<uint64_t>(ComponentType::FRAME_MANAGE_COMPONENT);
	}

	void FrameManage::Init()
	{
		auto& CM = ComponentManager::Instance();

		auto* activeComponent = CM.GetComponent<FrameManageComponent>		(componentMask, instanceId);

		activeComponent->frameOwner = frameOwner;
	}

	void FrameManage::Update()
	{
	}
}

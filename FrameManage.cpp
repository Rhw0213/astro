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

		auto* frameManageComponent = CM.GetComponent<FrameManageComponent>		(componentMask, instanceId);

		frameManageComponent->frameOwner = frameOwner;
		frameManageComponent->frameMaxIndex = 0;
		frameManageComponent->frameNowIndex = 0;
		frameManageComponent->trigerTime = 0;
	}

	void FrameManage::Update()
	{
	}
}

#include "FrameSystem.h"

namespace astro
{
	void FrameSystem::Init()
	{
		objectManager = std::make_unique<ObjectManager>();

		for (const auto& object : objects)
		{
			auto ptr = std::dynamic_pointer_cast<GameObject>(object);
			if (ptr)
			{
				objectManager.get()->InsertObject(ptr);
			}
		}
	}

	void FrameSystem::Process()
	{
		for (const auto& object : objects)
		{
			if (object)
			{
				auto* frameComponent = object.get()->GetComponent<FrameComponent>(ComponentType::FRAME_COMPONENT);
					
			}
		}
	}
}

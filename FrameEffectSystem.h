#pragma once
#include "System.h"
#include "ObjectManager.h"

namespace astro
{
	class FrameEffectSystem : public System
	{
	public:
		FrameEffectSystem(std::shared_ptr<ObjectManager> objectManager)
			: objectManager(objectManager)
		{ }
		void Init() override;
		void Process() override;
	private:
		std::shared_ptr<ObjectManager> objectManager;
	};
}
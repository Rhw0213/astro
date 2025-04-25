#pragma once
#include "System.h"
#include "ObjectManager.h"

namespace astro
{
	class FrameSystem : public System
	{
	public:
		FrameSystem(std::shared_ptr<ObjectManager> objectManager);
		void Init() override;
		void Process() override;
	private:
		std::shared_ptr<ObjectManager> objectManager;
	};
}
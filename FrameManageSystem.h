#pragma once
#include "System.h"
#include "ObjectManager.h"

namespace astro
{
/// @brief FrameSystem
	class FrameManageSystem : public System
	{
	public:
		FrameManageSystem(std::shared_ptr<ObjectManager> objectManager);
		void Init() override;
		void Process() override;
	private:
		std::shared_ptr<ObjectManager> objectManager;
	};
}
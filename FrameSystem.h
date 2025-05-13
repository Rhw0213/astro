#pragma once
#include "System.h"
#include "ObjectManager.h"

namespace astro
{
/// @brief FrameSystem
	class FrameSystem : public System
	{
	public:
		FrameSystem(std::shared_ptr<ObjectManager> objectManager)
			: objectManager(objectManager)
		{ }
		void Init() override;
		void Process() override;
	private:
		std::shared_ptr<ObjectManager> objectManager;
	};
}
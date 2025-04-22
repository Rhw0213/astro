#pragma once
#include "System.h"
#include "ObjectManager.h"

namespace astro
{
	class FrameSystem : public System
	{
	public:
		void Init() override;
		void Process() override;
	private:
		std::unique_ptr<ObjectManager> objectManager;
	};
}
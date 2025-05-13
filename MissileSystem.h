#pragma once
#include "System.h"
#include "ObjectManager.h"

namespace astro
{
	class MissileSystem : public System
	{
	public:
		MissileSystem(std::shared_ptr<ObjectManager> objectManager);
			
		void Init() override;
		void Process() override;
	private:
		std::shared_ptr<ObjectManager> objectManager;
	};
}
#pragma once
#include "System.h"
#include "ObjectManager.h"
#include <memory> 

namespace astro
{
/// @brief TransformSystem
	class TransformSystem : public System
	{
	public:
		TransformSystem(std::shared_ptr<ObjectManager> objectManager);
		void Init() override;
		void Process() override;
		void UpdateParentWorld(TransformComponent& transformComponent);
	private:
		std::shared_ptr<ObjectManager> objectManager;
		int frameNumber = 0;
	};
}
#pragma once
#include "ObjectManager.h"
#include "SystemManager.h"
#include "UIControll.h"
#include <memory> 

namespace astro
{
	class Game
	{
	public:
		Game();
		~Game();
		void Init();
		void Run();

	private:

		std::shared_ptr<ObjectManager> objectManager;

		std::shared_ptr<UIControll> uiControll;

		std::unique_ptr<SystemManager> systemManager;
	};
}

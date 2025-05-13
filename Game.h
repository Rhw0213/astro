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

		void CreateObject();
		void CreateObjectPart(ObjectType type, std::shared_ptr<Object> owner, std::shared_ptr<Object> manage, int count);
		std::shared_ptr<Object> CreateObjectManagePart(ObjectType type, std::shared_ptr<Object> owner, int count);
		std::shared_ptr<Object> CreateObjectOfCount(ObjectType type, int count);

	private:
		std::shared_ptr<ObjectManager>		objectManager;
		std::unique_ptr<SystemManager>		systemManager;

		std::shared_ptr<UIControll>			uiControll;
	};
}

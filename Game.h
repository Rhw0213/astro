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
		InstanceID CreateObjectPart(ObjectType type, InstanceID owner, InstanceID manage);
		InstanceID CreateObjectManagePart(ObjectType type, InstanceID owner);
		std::shared_ptr<Object> CreateObjectOfCount(ObjectType type, size_t count);

	private:
		std::shared_ptr<ObjectManager>		objectManager;
		std::unique_ptr<SystemManager>		systemManager;

		std::shared_ptr<UIControll>			uiControll;
	};
}

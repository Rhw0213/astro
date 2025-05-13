#pragma once
#include <unordered_map>
#include <memory>
#include "GameObject.h" 
#include "ComponentManager.h" 

namespace astro
{
	class ObjectManager
	{
	public:
		ObjectManager() = default;
		~ObjectManager() = default;

		template <typename T, typename... Args>
		std::shared_ptr<T> CreateObject(Args&&... args)
		{
			auto ptr = std::make_shared<T>(std::forward<Args>(args)...);

			if (ptr)
			{
				uint64_t	mask		= ptr.get()->GetComponentMask();
				InstanceID  instanceId	= ptr.get()->GetInstanceID();

				objects[instanceId] = ptr;
				ComponentManager::Instance().RegisterComponent(mask, instanceId);

				auto gameObject = std::dynamic_pointer_cast<GameObject>(ptr);
				if (gameObject)
				{ 
					gameObjects.push_back(gameObject);
				}

				return ptr;
			}

			return ptr;
		}

		//void InsertObject(std::shared_ptr<Object> gameObject);
		std::shared_ptr<Object> GetObject(InstanceID instanceId);
		std::vector<std::shared_ptr<Object>> GetObjects(ObjectType objectType);

		void Init();
		void Update();

	private:
		std::unordered_map<InstanceID, std::shared_ptr<Object>> objects;
		std::vector<std::shared_ptr<GameObject>> gameObjects;

		std::shared_ptr<ComponentManager> componentManager;
	};

}

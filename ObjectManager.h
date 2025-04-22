#pragma once
#include <unordered_map>
#include <memory>
#include "GameObject.h" 

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
			std::shared_ptr<T> ptr = std::make_shared<T>(std::forward<Args>(args)...);

			if (ptr)
			{
				gameObjects.insert( { ptr.get()->GetInstanceID(), ptr } );
				return ptr;
			}

			return ptr;
		}

		void InsertObject(std::shared_ptr<GameObject> gameObject);
		std::shared_ptr<GameObject> GetGameObject(InstanceID instanceId);

		void Init();
		void Update();

	private:
		std::unordered_map<InstanceID, std::shared_ptr<GameObject>> gameObjects;
	};

}

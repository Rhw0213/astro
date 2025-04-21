#pragma once
#include <vector>
#include <memory>
#include "GameObject.h" 

namespace astro
{
	class ObjectManager
	{
	public:
		ObjectManager() = default;
		~ObjectManager() = default;

		template <typename T>
		std::shared_ptr<T> CreateObject()
		{
			std::shared_ptr<T> ptr = std::make_shared<T>();
			objects.push_back(ptr);
			return ptr;
		}

		void Init();
		void Update();

	private:
		std::vector<std::shared_ptr<GameObject>> objects;
	};

}

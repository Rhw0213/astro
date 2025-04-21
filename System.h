#pragma once
#include <vector>
#include <memory>
#include "Object.h"

namespace astro
{
	class System
	{
	public:
		System() = default;
		~System() = default;

		virtual void Init() = 0;
		virtual void Process() = 0;

		void RegisterObject(std::shared_ptr<Object> object)
		{
			for (const auto& obj : objects)
			{
				if (object.get() == obj.get())
				{ 
					return; 
				}
			}

			objects.push_back(std::shared_ptr<Object>(object));
		}
	protected:
		std::vector<std::shared_ptr<Object>> objects;
	};
}

#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include "Common.h"

namespace astro
{
	class Object
	{
	public:
		Object() = default;
		virtual ~Object() = default;
		virtual ObjectID GetID() const = 0;

		void AddComponent(std::shared_ptr<Component> comp)
		{
			for (const auto& component : components)
			{
				if (comp->GetID() == component->GetID())
				{
					return;
				}
			}

			components.push_back(comp);
		}

		template <typename T>
		T* GetComponent(ComponentID id)
		{
			for (const auto& component : components)
			{
				if (component->GetID() == id)
				{
					return static_cast<T*>(component.get());
					break;
				}
			}

			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<Component>> components;
	};
}

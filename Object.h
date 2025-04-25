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
		Object()
			: componentMask(0)
			, enable(true)
		{
			instanceId = staticInstanceId++;
		}

		virtual				~Object() = default;
		virtual	ObjectType	GetType() const = 0;

		InstanceID			GetInstanceID()					const { return instanceId;		};
		unsigned int		GetComponentMask()				const { return componentMask;	};
		bool				IsEnable()						const { return enable;			};

		void				SetEnable(bool enable)				  { this->enable = enable;  };

		void AddComponent(std::shared_ptr<Component> comp)
		{
			for (const auto& component : components)
			{
				if (comp->GetType() == component->GetType())
				{
					return;
				}
			}

			componentMask = componentMask | static_cast<unsigned int>(comp->GetType());
			components.push_back(comp);
		}

		template <typename T>
		T* GetComponent(ComponentType id)
		{
			for (const auto& component : components)
			{
				if (component->GetType() == id)
				{
					return static_cast<T*>(component.get());
					break;
				}
			}

			return nullptr;
		}

	private:
		static InstanceID						staticInstanceId;
		InstanceID								instanceId;
		unsigned int							componentMask;
		bool									enable;
		std::vector<std::shared_ptr<Component>> components;
	};
}

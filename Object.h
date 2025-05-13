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
		{
			instanceId = staticInstanceId++;
		}

		virtual				~Object() = default;
		virtual	ObjectType	GetType() const = 0;

		InstanceID			GetInstanceID()					const { return instanceId;		};
		uint64_t			GetComponentMask()				const { return componentMask;	};

	protected:
		static InstanceID						staticInstanceId;
		InstanceID								instanceId;
		uint64_t								componentMask;
	};
}

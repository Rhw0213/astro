#pragma once
#include "Object.h"
#include <vector>

namespace astro
{
	class GameObject : public Object
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;

		virtual void Init() = 0;
		virtual void Update() = 0;

		virtual ObjectType GetType() const override { return ObjectType::GAMEOBJECT_ID; };
	};
}

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

		ObjectID GetID() const override { return ObjectID::GAMEOBJECT_ID; };
	};
}

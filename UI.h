#pragma once
#include "Object.h"
#include "raylib.h"
#include <vector> 

namespace astro
{
	class UI : public Object
	{
	public:
		ObjectID GetID() const override { return ObjectID::UI_ID; };
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}

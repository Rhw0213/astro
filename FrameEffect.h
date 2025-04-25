#pragma once
#include "Object.h"

namespace astro
{
	class FrameEffect : public Object
	{
	public:
		FrameEffect(const ObjectType& frameOfObject);
		ObjectType GetType() const override { return ObjectType::FRAME_EFFECT_ID; };
	private:	
	};
}
#include "FrameEffect.h"
#include "Component.h"

namespace astro
{
	FrameEffect::FrameEffect(const ObjectType& frameOfObject)
	{
		Object::AddComponent(std::make_shared<FrameEffectComponent>(frameOfObject));
	}
}

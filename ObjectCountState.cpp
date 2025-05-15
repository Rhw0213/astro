#include "ObjectCountState.h"

namespace astro
{ 
	size_t ObjectCountState::AddObjectCount(ObjectType type, size_t count)
	{
		auto it = objectSizes.find(type);

		if (it == objectSizes.end())
		{
			objectSizes[type] = 0;
		}

		objectSizes[type] += count;

		return count;
	}

	size_t ObjectCountState::GetObjectCount(ObjectType type)
	{
		auto it = objectSizes.find(type);

		if (it != objectSizes.end())
		{
			return objectSizes[type];
		}

		return  0;
	}
}

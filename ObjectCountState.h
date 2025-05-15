#pragma once
#include <unordered_map>
#include "Common.h" 

namespace astro
{
	class ObjectCountState
	{
	public:
		static ObjectCountState& Instance()
		{
			static ObjectCountState instance;
			return instance;
		}

		size_t AddObjectCount(ObjectType type, size_t count);
		size_t GetObjectCount(ObjectType type);
	private:
		ObjectCountState() = default;
		std::unordered_map<ObjectType, size_t> objectSizes;
	};
}
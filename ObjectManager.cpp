#include "ObjectManager.h"

namespace astro
{
	void ObjectManager::Init()
	{
		for (const auto& object : objects)
		{
			object->Init();
		}
	}

	void ObjectManager::Update()
	{
		for (const auto& object : objects)
		{
			object->Update();
		}
	}
}

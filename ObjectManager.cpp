#include "ObjectManager.h"

namespace astro
{
	//void ObjectManager::InsertObject(std::shared_ptr<Object> object)
	//{
	//	objects.insert( {object.get()->GetInstanceID(), object});
	//}

	std::shared_ptr<Object> ObjectManager::GetObject(InstanceID instanceId)
	{
		auto it = objects.find(instanceId);

		if (it != objects.end())
		{
			return it->second;
		}

		return nullptr;
	}

	std::vector<std::shared_ptr<Object>> ObjectManager::GetObjects(ObjectType objectType)
	{
		std::vector<std::shared_ptr<Object>> finedObjects;

		for (const auto& [_, object] : objects)
		{
			if (object.get()->GetType() == objectType)
			{
				finedObjects.push_back(object);
			}
		}

		return finedObjects;
	}

	void ObjectManager::Init()
	{
		for (const auto& object : gameObjects)
		{
			object.get()->Init();
		}
	}

	void ObjectManager::Update()
	{
		for (const auto& object : gameObjects)
		{
			object.get()->Update();
		}
	}
}

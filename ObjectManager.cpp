#include "ObjectManager.h"

namespace astro
{
	void ObjectManager::InsertObject(std::shared_ptr<GameObject> gameObject)
	{
		gameObjects.insert( {gameObject.get()->GetInstanceID(), gameObject});
	}

	std::shared_ptr<GameObject> ObjectManager::GetGameObject(InstanceID instanceId)
	{
		auto it = gameObjects.find(instanceId);

		if ( it != gameObjects.end() )
		{
			return it->second;
		}

		return nullptr;
	}

	void ObjectManager::Init()
	{
		for (const auto& [objectId, object] : gameObjects)
		{
			object.get()->Init();
		}
	}

	void ObjectManager::Update()
	{
		for (const auto& [objectId, object] : gameObjects)
		{
			object.get()->Update();
		}
	}
}

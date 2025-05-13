#pragma once
#include "Common.h" 
#include <unordered_map>
#include <vector>

namespace astro
{
	class ComponentManager
	{
	public:
		~ComponentManager();

		static ComponentManager& Instance()
		{
			static ComponentManager instance;
			return instance;
		}

		void					RegisterComponent(uint64_t bitmask, InstanceID instanceId);
		std::vector<Archetype*> GetArchetypeQuery(uint64_t bitMask);

		template <typename T>		
		T* GetComponent(uint64_t bitMask, InstanceID instanceId)
		{
			auto it = instanceIdQueryCache.find(bitMask);

			if (it != instanceIdQueryCache.end())
			{
				return it->second->GetComponent<T>(instanceId);
			}

			for (auto& archetype : archetypes)
			{
				if (archetype.typeMask == bitMask)
				{
					instanceIdQueryCache[bitMask] = &archetype;
					return instanceIdQueryCache[bitMask]->GetComponent<T>(instanceId);
				}
			}

			return nullptr;
		}

		template <typename T>
		void RegisterData(uint64_t bitmask, InstanceID instanceId)
		{
			for (auto& archetype : archetypes)
			{
				if (archetype.typeMask == bitmask)
				{
					archetype.RegisterComponent<T>(instanceId);
					return;
				}
			}

			Archetype archetype;
			archetype.typeMask = bitmask;
			archetype.RegisterComponent<T>(instanceId);
			
			archetypes.push_back(archetype);
		}

	private:
		ComponentManager() = default;
		std::vector<Archetype> archetypes;

		struct QueryCache
		{
			std::vector<Archetype*> matchingArchetypes;
		};

		std::unordered_map<uint64_t, QueryCache> queryCache;
		std::unordered_map<uint64_t, Archetype*> instanceIdQueryCache;
	};
}

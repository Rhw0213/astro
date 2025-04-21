#pragma once
#include <map>
#include <vector>
#include <functional>
#include <typeindex>
#include "Event.h"

namespace astro
{
	class EventManager
	{
	public:
		~EventManager() = default;

		static EventManager& Instance()
		{
			static EventManager instance;
			return instance;
		}

		template <typename T>
		void RegisterEvent(std::function<void(const T*)> func)
		{
			auto event = [func](const Event* e) {
				func(static_cast<const T*>(e));
			};

			events[typeid(T)].push_back(event);
		}

		template <typename T>
		void RunEvent(const T& event)
		{
			auto it = events.find(typeid(T));

			if (it != events.end())
			{
				for (auto& e : it->second)
				{
					e(&event);
				}
			}
		}
	private:
		EventManager() = default;
		std::map<std::type_index, std::vector<std::function<void(const Event*)>>> events;
	};
}

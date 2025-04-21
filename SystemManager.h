#pragma once
#include <vector>
#include <memory>
#include <initializer_list>
#include "System.h" 
#include "ShaderSystem.h" 

namespace astro
{
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager() = default;
	public:
		enum SystemID
		{
			INPUT_SYSTEM,
			CAMERA_SYSTEM,
			MOVE_SYSTEM,
			STAR_EFFECT_SYSTEM,
			WARP_SYSTEM,
			ROTATION_SYSTEM,
			RENDER_SYSTEM,
			SHADER_SYSTEM
		};

		template <typename T>
		void RegisterObjectOfSystem(std::initializer_list<SystemID> ids, std::shared_ptr<T> ptr)
		{
			for (const auto& id : ids)
			{
				systems[id].get()->RegisterObject(ptr);
			}
		}

		void Init();
		void Update();
		void Draw();

	private:
		template <typename T>
		void RegisterSystem(std::shared_ptr<T> ptr)
		{
			systems.push_back(ptr);
		}

	private:
		std::vector<std::shared_ptr<System>> systems;
	};
}

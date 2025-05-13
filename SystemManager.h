#pragma once
#include <vector>
#include <memory>
#include <bitset>
#include <map>
#include <initializer_list>
#include "System.h" 
#include "ShaderSystem.h" 
#include "GameObject.h" 
#include "ObjectManager.h" 

namespace astro
{
/// @brief SystemManager 
	class SystemManager
	{
	public:
		SystemManager(std::shared_ptr<ObjectManager> objectManager);
		~SystemManager() = default;
	public:
		enum class SystemID
		{
			//input
			INPUT_SYSTEM			, 


			STAR_SYSTEM				,
			BRIGHT_EFFECT_SYSTEM	, 
			WARP_SYSTEM				, 
			FRAME_SYSTEM			, 
			FRAME_MANAGE_SYSTEM		, 

			//movement
			MOVE_SYSTEM				, 
			TRANSFORM_SYSTEM		,

			//effect

			//

			//
			CAMERA_SYSTEM			, 
			RENDER_SYSTEM			, 
			SHADER_SYSTEM			,
		};
			
		void RegisterObjectOfSystem(std::shared_ptr<Object> gameObject);

		void Init();
		void Update();
		void Draw();

	private:
		enum class RegisterLogic
		{
			ALL,
			ANY
		};

		struct Mask
		{
			unsigned int mask;
			RegisterLogic registerLogic;
		};

		template <typename T>
		void RegisterSystem(SystemID systemId, std::shared_ptr<T> system)
		{
			systems.insert({systemId, system});
		}

	private:
		std::map<SystemID, std::shared_ptr<System>> systems;
		std::map<SystemID, Mask> systemRequirement;
		std::shared_ptr<ObjectManager> objectManager;
	};
}

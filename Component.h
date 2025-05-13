#pragma once
#include "Common.h"
#include <vector> 
#include <map> 
#include "raylib.h" 

namespace astro
{
	class Object;

/// @brief Component
	struct Component 
	{ 
	public:
		virtual ComponentType GetType() = 0;
		virtual ~Component() = default; 
	};

/// @brief Component
	struct ActiveComponent  
	{ 
	public:
		ComponentType GetType() 
		{ 
			return ComponentType::ACTIVE_COMPONENT;
		}

		bool enable = true;
	};

/// @brief TransformComponent
	struct TransformComponent 
	{
		TransformComponent(InstanceID parentId = 0)
			: parentId(parentId)
			, worldPosition{ 0, 0 }
			, worldScale(1.f)
			, localPosition{ 0, 0 }
			, localScale(1.f)
			, frameUpdateNumber(0)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::TRANSFORM_COMPONENT;
		}

		InstanceID parentId;

		MyVector2 worldPosition{ 0, 0 };
		Angle worldRotation;
		float worldScale = 0;

		MyVector2 localPosition{ 0, 0 };
		Angle localRotation;
		float localScale = 0;
		
		int frameUpdateNumber = 0;
	};

/// @brief RenderComponent
	struct RenderComponent  
	{
		RenderComponent()
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::RENDER_COMPONENT;
		}

		std::vector<MyVector2> points;
		ObjectType objectType = ObjectType::NONE;
	};

/// @brief InputComponent
	struct InputComponent 
	{
		InputComponent() { }

		ComponentType GetType() 
		{ 
			return ComponentType::INPUT_COMPONENT;
		}
	};

/// @brief MoveComponent
	struct MoveComponent  
	{
		MoveComponent(const MyVector2& direction = { 0, 0 }, const float& speed = 0.f, const MyVector2& slowVelocity = { 0, 0 })
			: direction(direction)
			, speed(speed)
			, slowVelocity(slowVelocity)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::MOVE_COMPONENT;
		}

		MyVector2 direction{ 0, 0 };
		MyVector2 slowVelocity{ 0, 0 };
		float speed = 0.f;
	};

/// @brief BrightEffectComponent
	struct BrightEffectComponent 
	{
		BrightEffectComponent(int bright = 0.f, float twinkle = 0.f)
			: bright(bright)
			, twinkle(twinkle)
			, time(0.f)
			, distanceDepth(0.f)
			, maxSize(0.f)
			, color(WHITE)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::BRIGHT_EFFECT_COMPONENT;
		}

		int bright = 0;
		float twinkle = 0.f;
		float time = 0.f;
		float distanceDepth = 0.f;
		float maxSize = 0.f;
		Color color = WHITE;
	};

/// @brief CameraComponent
	struct CameraComponent 
	{
		CameraComponent(const MyVector2& offset = {0,0},
						const MyVector2& target = {0,0},
						float rotation = 0.f,
						float zoom = 1.f)
			: camera{ offset, target, rotation, zoom }
			, targetZoom(0.f)
			, zoomSpeed(0.f)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::CAMERA_COMPONENT;
		}

		Camera2D camera;
		float targetZoom = 0.f;
		float zoomSpeed = 0.f;
	};


/// @brief WarpComponent
	struct WarpComponent 
	{
		WarpComponent()
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::WARP_COMPONENT;
		}
		
		bool isWarp = false;
	};

/// @brief UIComponent
	struct UIComponent 
	{
		UIComponent()
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::UI_COMPONENT;
		}
		
		std::vector<std::shared_ptr<Texture2D>> textures;

	};

/// @brief FrameComponent
	struct FrameComponent 
	{
		FrameComponent(InstanceID target = 0, InstanceID manage = 0)
			: time(0)
			, speed(100.f)
			, target(target)
			, manage(manage)
			, index(0)
			, rotationDirection(0)
			, color{ 255,255,255,255 }
			, size(0)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::FRAME_COMPONENT;
		}
		
		float time = 0.f;
		float speed = 0.f;
		InstanceID target;
		InstanceID manage;
		size_t index;
		float rotationDirection;
		Color color;
		float size;
	};

/// @brief FrameManageComponent
	struct FrameManageComponent 
	{
		FrameManageComponent(InstanceID frameOwner = 0)
			: frameOwner(frameOwner)
			, frameNowIndex(0)
			, frameMaxIndex(0)
			, trigerTime(0.f)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::FRAME_MANAGE_COMPONENT;
		}

		InstanceID frameOwner;
		size_t frameNowIndex = 0;
		size_t frameMaxIndex = 0;
		float trigerTime = 0.f;
	};
	
/// @brief ShaderComponent
	struct ShaderComponent 
	{
		ShaderComponent(const Shader& shader = {}, ShaderName shaderName = ShaderName::NONE)
			: shader(shader)
			, shaderName(shaderName)
			, enabled(true)
			, sourceRec{0.f, 0.f, 0.f, 0.f}
			, destRec{0.f, 0.f, 0.f, 0.f}
			, origin{0.f, 0.f}
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::SHADER_COMPONENT;
		}

		Shader shader;
		ShaderName shaderName;
		bool enabled;

		Rectangle sourceRec;
		Rectangle destRec;
		MyVector2 origin;
	};
		
/// @brief ShaderColorDiffusionComponent
	struct ShaderColorDiffusionComponent : public ShaderComponent
	{
		ShaderColorDiffusionComponent()
			: ShaderComponent(LoadShader(defaultVs, colorDiffusionFs), ShaderName::COLOR_DIFFUSION)
			, textureLoc(0)
			, bleedRadiusLoc(0)
			, bleedIntensityLoc(0)
			, colorThresholdLoc(0)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT;
		}

		int textureLoc = 0;
		int bleedRadiusLoc = 0;
		int bleedIntensityLoc = 0;
		int colorThresholdLoc = 0;
	};

/// @brief ShaderFrameComponent
	struct ShaderFrameComponent : public ShaderComponent
	{
		ShaderFrameComponent()
			: ShaderComponent(LoadShader(defaultVs, frameFs), ShaderName::FRAME)
			, time(0)
			, timeLoc(0)
			, positionLoc(0)
			, directionLoc(0)
			, resolutionLoc(0)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::SHADER_FRAME_COMPONENT;
		}

		float time = 0.f;

		int timeLoc = 0;
		int positionLoc = 0;
		int directionLoc = 0;
		int resolutionLoc = 0;
	};

/// @brief MissileComponent
	struct MissileComponent 
	{
		MissileComponent(InstanceID missileOwner = 0)
			: missileOwner(missileOwner)
			, speed(0)
		{ }

		ComponentType GetType() 
		{ 
			return ComponentType::MISSILE_COMPONENT;
		}
		InstanceID missileOwner;
		float speed;
	};



}

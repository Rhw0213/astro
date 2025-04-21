#pragma once
#include "Common.h"
#include <vector> 
#include "raylib.h" 

namespace astro
{
	struct Component 
	{ 
	public:
		virtual ComponentID GetID() = 0;
		virtual ~Component() = default; 
	};

	struct TransformComponent : public Component
	{
		TransformComponent(const MyVector2& position = {0, 0}, const MyVector2& direction = {0, 0}, const float& size = 1.f)
			: position(position)
			, direction(direction)
			, size(size)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::TRANSFORM_COMPONENT;
		}

		MyVector2 position{ 0, 0 };
		MyVector2 direction{ 0, 0 };
		float size = 0;
	};

	struct RenderComponent : public Component
	{
		RenderComponent()
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::RENDER_COMPONENT;
		}

		std::vector<MyVector2> points;
	};

	struct InputComponent : public Component
	{
		InputComponent() { }

		ComponentID GetID() override 
		{ 
			return ComponentID::INPUT_COMPONENT;
		}
	};

	struct MoveComponent : public Component
	{
		MoveComponent(const MyVector2& direction = { 0, 0 }, const float& speed = 0.f, const MyVector2& slowVelocity = { 0, 0 })
			: direction(direction)
			, speed(speed)
			, slowVelocity(slowVelocity)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::MOVE_COMPONENT;
		}

		MyVector2 direction{ 0, 0 };
		MyVector2 slowVelocity{ 0, 0 };
		float speed = 0.f;
	};

	struct EffectComponent : public Component
	{
		EffectComponent(int bright = 0.f, float twinkle = 0.f)
			: bright(bright)
			, twinkle(twinkle)
			, time(0.f)
			, distanceDepth(0.f)
			, maxSize(0.f)
			, color(WHITE)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::EFFECT_COMPONENT;
		}

		int bright = 0;
		float twinkle = 0.f;
		float time = 0.f;
		float distanceDepth = 0.f;
		float maxSize = 0.f;
		Color color = WHITE;
	};

	struct CameraComponent : public Component
	{
		CameraComponent(const MyVector2& offset = {0,0},
						const MyVector2& target = {0,0},
						float rotation = 0.f,
						float zoom = 1.f)
			: camera{ offset, target, rotation, zoom }
			, targetZoom(0.f)
			, zoomSpeed(0.f)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::CAMERA_COMPONENT;
		}

		Camera2D camera;
		float targetZoom = 0.f;
		float zoomSpeed = 0.f;
	};

	struct RotationComponent : public Component
	{
		RotationComponent(float angle = 0.f, float previousAngle = 0.f)
			: angle{ angle }
			, previousAngle{ previousAngle }
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::ROTATION_COMPONENT;
		}

		Angle angle = { 0.f };
		Angle previousAngle = { 0.f };
	};

	struct WarpComponent : public Component
	{
		WarpComponent()
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::WARP_COMPONENT;
		}
		
		bool isWarp = false;
	};

	struct UIComponent : public Component
	{
		UIComponent()
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::UI_COMPONENT;
		}
		
		std::vector<std::shared_ptr<Texture2D>> textures;

	};
	
	struct ShaderComponent : public Component
	{
		ShaderComponent(const Shader& shader, ShaderName shaderName)
			: shader(shader)
			, shaderName(shaderName)
			, enabled(true)
			, sourceRec{0.f, 0.f, 0.f, 0.f}
			, destRec{0.f, 0.f, 0.f, 0.f}
			, origin{0.f, 0.f}
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::SHADER_COMPONENT;
		}

		Shader shader;
		ShaderName shaderName;
		bool enabled;

		Rectangle sourceRec;
		Rectangle destRec;
		MyVector2 origin;
	};
		
	struct ColorDiffusionShaderComponent : public ShaderComponent 
	{
		ColorDiffusionShaderComponent()
			: ShaderComponent(LoadShader(defaultVs, colorDiffusionFs), ShaderName::COLOR_DIFFUSION)
			, textureLoc(0)
			, bleedRadiusLoc(0)
			, bleedIntensityLoc(0)
			, colorThresholdLoc(0)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::SHADER_COLOR_DIFFUSION_COMPONENT;
		}

		int textureLoc = 0;
		int bleedRadiusLoc = 0;
		int bleedIntensityLoc = 0;
		int colorThresholdLoc = 0;
	};

	struct FrameShaderComponent : public ShaderComponent 
	{
		FrameShaderComponent()
			: ShaderComponent(LoadShader(defaultVs, frameFs), ShaderName::FRAME)
			, time(0)
			, timeLoc(0)
			, positionLoc(0)
			, directionLoc(0)
			, resolutionLoc(0)
		{ }

		ComponentID GetID() override 
		{ 
			return ComponentID::SHADER_FRAME_COMPONENT;
		}

		float time = 0.f;

		int timeLoc = 0;
		int positionLoc = 0;
		int directionLoc = 0;
		int resolutionLoc = 0;
	};
}

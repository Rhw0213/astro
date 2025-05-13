#pragma once
#include "raylib.h"
#include "Common.h"
#include "Object.h"

namespace astro
{
/// @brief ShaderEffect
	class ShaderEffect : public Object
	{
	public:
		ShaderEffect() = default;

		virtual void Init(std::shared_ptr<Object> object) = 0; 
		virtual void Update(std::shared_ptr<Object> object, const RenderTexture2D& inputTexture, const RenderTexture2D& outputTexture) = 0;

		ObjectType GetType() const override { return ObjectType::SHADER_ID; };
	};
}
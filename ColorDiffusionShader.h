#pragma once
#include "ShaderEffect.h"
#include "Object.h"

namespace astro
{
	class ColorDiffusionShader : public ShaderEffect
	{
	public:
		ColorDiffusionShader();

		void Init(std::shared_ptr<Object> object) override;
		void Update(std::shared_ptr<Object> object, const RenderTexture2D& inputTexture, const RenderTexture2D& outputTexture) override;

		ObjectID GetID() const override { return ObjectID::SHADER_COLOR_DIFFUSION_ID; }
	private:
	};
}

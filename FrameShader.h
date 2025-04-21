#pragma once
#include "ShaderEffect.h"

namespace astro
{
	class FrameShader : public ShaderEffect
	{
	public:
		virtual void Init(std::shared_ptr<Object> object) override; 
		virtual void Update(std::shared_ptr<Object> object, const RenderTexture2D& inputTexture, const RenderTexture2D& outputTexture) override;

		ObjectID GetID() const override { return ObjectID::SHADER_FRAME_ID; };
	private:

	};
}

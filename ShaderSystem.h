#pragma once
#include "System.h"
#include "ShaderEffect.h"
#include <vector> 

namespace astro
{
	class ShaderSystem : public System
	{
	public:
		ShaderSystem();
		~ShaderSystem();

		void Init() override;
		void Process() override;
		void FindObjectAndSetShader(std::shared_ptr<Object> object, std::shared_ptr<ShaderEffect> shaderEffect);

	private:
		struct ObjectAndShader
		{
			std::shared_ptr<Object> object;
			std::vector<std::shared_ptr<ShaderEffect>> shaders;
		};

		std::vector<ObjectAndShader> objectAndShaders;

		RenderTexture2D renderTarget;
		RenderTexture2D effectTarget;

		Rectangle screenDestRec;
		Rectangle screenDestRecYReverse;
	};
}

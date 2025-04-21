#pragma once
#include "System.h"
#include "ShaderEffect.h"
#include <vector> 

namespace astro
{
	//using FuncShader = std::function<void(const Shader&, const RenderTexture2D&, const RenderTexture2D&)>;

	class ShaderSystem : public System
	{
	public:
		ShaderSystem();
		~ShaderSystem();

		void Init() override;
		void Process() override;

	private:
		//struct ShaderEffect
		//{
		//	ShaderName name;
		//	Shader shader;
		//	bool enabled = true;
		//	FuncShader func;
		//};

		struct ObjectAndShader
		{
			std::shared_ptr<Object> object;
			std::vector<std::shared_ptr<ShaderEffect>> shaders;
		};

		std::vector<std::shared_ptr<ShaderEffect>> shaderEffects;

		std::vector<ObjectAndShader> objectAndShaders;

		RenderTexture2D renderTarget;
		RenderTexture2D effectTarget;
		Rectangle screenDestRec;
	};
}

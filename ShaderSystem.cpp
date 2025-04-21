#include "ShaderSystem.h"
#include "EventManager.h"
#include "ColorDiffusionShader.h"
#include "FrameShader.h"

namespace astro
{
	ShaderSystem::ShaderSystem()
			: renderTarget(LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT))
			, effectTarget(LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT))
			, screenDestRec{ 0.0f, 0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)}
	{ }

	void ShaderSystem::Init()
	{
		shaderEffects.push_back(std::make_shared<ColorDiffusionShader>());
		shaderEffects.push_back(std::make_shared<FrameShader>());

		//  오브젝트만 처리
		for (const auto& shaderEffect : shaderEffects)
		{
			for (const auto& object : objects)
			{
				if (shaderEffect.get()->GetID() == ObjectID::SHADER_COLOR_DIFFUSION_ID)
				{
					auto* shaderColorDiffusionComponent = object.get()->GetComponent<ColorDiffusionShaderComponent>(ComponentID::SHADER_COLOR_DIFFUSION_COMPONENT);

					if (shaderColorDiffusionComponent)
					{
						auto it = std::find_if(objectAndShaders.begin(), objectAndShaders.end(), [object](const ObjectAndShader& objectAndShader) {
								return object == objectAndShader.object;
						});

						if (it == objectAndShaders.end()) // 못찾으면
						{
							ObjectAndShader objectAndShader;

							objectAndShader.object = object;
							objectAndShader.shaders.push_back(shaderEffect);
							objectAndShaders.push_back(objectAndShader);
						}
						else
						{
							it->shaders.push_back(shaderEffect);
						}
					}
				}
				else if (shaderEffect.get()->GetID() == ObjectID::SHADER_FRAME_ID)
				{
					auto* frameShaderComponent = object.get()->GetComponent<FrameShaderComponent>(ComponentID::SHADER_FRAME_COMPONENT);

					if (frameShaderComponent)
					{
						auto it = std::find_if(objectAndShaders.begin(), objectAndShaders.end(), [object](const ObjectAndShader& objectAndShader) {
								return object == objectAndShader.object;
						});

						if (it == objectAndShaders.end()) // 못찾으면
						{
							ObjectAndShader objectAndShader;

							objectAndShader.object = object;
							objectAndShader.shaders.push_back(shaderEffect);
							objectAndShaders.push_back(objectAndShader);
						}
						else
						{
							it->shaders.push_back(shaderEffect);
						}
					}
				}
			}
		}

		for (const auto& objectAndShader : objectAndShaders)
		{
			std::shared_ptr<Object> object = objectAndShader.object;

			for (const auto& shaderEffect : objectAndShader.shaders)
			{
				shaderEffect.get()->Init(object);
			}
		}

		EventManager::Instance().RegisterEvent<ObjectRenderEndEvent>([&](const ObjectRenderEndEvent* e) {
				renderTarget = *e->endRenderTexture;
			}
		);
	}

	ShaderSystem::~ShaderSystem()
	{
		UnloadRenderTexture(renderTarget);
		UnloadRenderTexture(effectTarget);
	}

	void ShaderSystem::Process()
	{
		RenderTexture2D* inputTexture = &renderTarget;
		RenderTexture2D* outputTexture = &effectTarget;

		for (const auto& objectAndShader : objectAndShaders)
		{
			std::shared_ptr<Object> object = objectAndShader.object;

			for (const auto& shaderEffect : objectAndShader.shaders)
			{
				shaderEffect.get()->Update(object, *inputTexture, *outputTexture);
			}
		}

		std::swap(inputTexture, outputTexture);

		ClearBackground(BLANK);

		Rectangle sourceRec = { 0.0f, 0.0f, 
								static_cast<float>(inputTexture->texture.width), 
								static_cast<float>(-inputTexture->texture.height)
		}; 

		DrawTexturePro(inputTexture->texture, sourceRec, screenDestRec, {0.f, 0.f}, 0.0f, WHITE);
	}
}

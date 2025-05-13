#include "ShaderSystem.h"
#include "EventManager.h"
#include "ShaderColorDiffusion.h"
#include "ShaderFrame.h"

namespace astro
{
	ShaderSystem::ShaderSystem()
			: renderTarget(LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT))
			, effectTarget(LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT))
			, screenDestRec{ 0.0f, 0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)}
			, screenDestRecYReverse{ 0.0f, 0.0f, static_cast<float>(SCREEN_WIDTH), -static_cast<float>(SCREEN_HEIGHT)}
	{ }

	void ShaderSystem::Init()
	{
		//for (const auto& object : objects)
		//{
		//    auto* colorDiffusionComponent = object.get()->GetComponent<ShaderColorDiffusionComponent>(ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT);
		//    if (colorDiffusionComponent)
		//    {
		//		FindObjectAndSetShader(object, std::make_shared<ShaderColorDiffusion>());
		//    }
		//
		//	auto* FrameComponent = object.get()->GetComponent<ShaderFrameComponent>(ComponentType::SHADER_FRAME_COMPONENT);
		//	if (FrameComponent)
		//	{
		//		FindObjectAndSetShader(object, std::make_shared<ShaderFrame>());
		//	}
		//}

		//for (const auto& objectAndShader : objectAndShaders)
		//{
		//	std::shared_ptr<Object> object = objectAndShader.object;

		//	for (const auto& shaderEffect : objectAndShader.shaders)
		//	{
		//		shaderEffect.get()->Init(object);
		//	}
		//}

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

		//for (const auto& objectAndShader : objectAndShaders)
		//{
		//	std::shared_ptr<Object> object = objectAndShader.object;

		//	if (object && object.get()->IsEnable())
		//	{
		//		for (const auto& shaderEffect : objectAndShader.shaders)
		//		{
		//			shaderEffect.get()->Update(object, *inputTexture, *outputTexture);
		//			std::swap(inputTexture, outputTexture);
		//		}
		//	}
		//}

		BeginDrawing();
		ClearBackground(BLANK);

		DrawTexturePro(inputTexture->texture, screenDestRecYReverse, screenDestRec, {0.f, 0.f}, 0.0f, WHITE);
		DrawFPS(10, 10);
		EndDrawing();
	}

	void ShaderSystem::FindObjectAndSetShader(std::shared_ptr<Object> object, std::shared_ptr<ShaderEffect> shaderEffect)
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

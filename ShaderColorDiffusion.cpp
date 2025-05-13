#include "ShaderColorDiffusion.h"
#include <algorithm>

namespace astro
{
	ShaderColorDiffusion::ShaderColorDiffusion()
	{
	}

	void ShaderColorDiffusion::Init(std::shared_ptr<Object> object)
	{
		//auto* colorDiffusionShaderComponent = object.get()->GetComponent<ShaderColorDiffusionComponent>(ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT);
		//const Shader& shader = colorDiffusionShaderComponent->shader;

		//if (colorDiffusionShaderComponent)
		//{
		//	colorDiffusionShaderComponent->textureLoc = GetShaderLocation(shader, "screenTexture");
		//	colorDiffusionShaderComponent->bleedRadiusLoc = GetShaderLocation(shader, "bleedRadius");
		//	colorDiffusionShaderComponent->bleedIntensityLoc = GetShaderLocation(shader, "bleedIntensity");
		//	colorDiffusionShaderComponent->colorThresholdLoc = GetShaderLocation(shader, "colorThreshold");
		//}
	}

	void ShaderColorDiffusion::Update(std::shared_ptr<Object> object, const RenderTexture2D& inputTexture, const RenderTexture2D& outputTexture)
	{
		//auto* colorDiffusionShaderComponent = object.get()->GetComponent<ShaderColorDiffusionComponent>(ComponentType::SHADER_COLOR_DIFFUSION_COMPONENT);
		//const Shader& shader = colorDiffusionShaderComponent->shader;

		//int textureLoc = colorDiffusionShaderComponent->textureLoc;
		//int bleedRadiusLoc = colorDiffusionShaderComponent->bleedRadiusLoc;
		//int bleedIntensityLoc = colorDiffusionShaderComponent->bleedIntensityLoc;
		//int colorThresholdLoc = colorDiffusionShaderComponent->colorThresholdLoc;

		//Rectangle& sourceRec = colorDiffusionShaderComponent->sourceRec;
		//Rectangle& destRec = colorDiffusionShaderComponent->destRec;
		//MyVector2& origin = colorDiffusionShaderComponent->origin;

		//sourceRec = { 0.0f, 0.0f, 
		//				static_cast<float>(inputTexture.texture.width), 
		//				static_cast<float>(-inputTexture.texture.height) }; 
		//destRec = { 0.0f, 0.0f,
		//			  static_cast<float>(outputTexture.texture.width),
		//			  static_cast<float>(outputTexture.texture.height) };
		//origin = { 0.f, 0.f };

		//float bleedRadius = 2.6f;  // 번짐 반경 (1.0 ~ 10.0)
		//float bleedIntensity = .8f;  // 번짐 강도 (0.0 ~ 1.0)
		//float colorThreshold = 0.1f;  // 색상 감지 임계값 (0.1 ~ 0.5)

		//BeginTextureMode(outputTexture);
		//ClearBackground(BLANK);

		//{
		//	BeginShaderMode(shader);

		//	if (textureLoc != -1 && bleedRadiusLoc != -1 && bleedIntensityLoc != -1 && colorThresholdLoc != -1)
		//	{
		//		SetShaderValueTexture(shader, textureLoc, inputTexture.texture);
		//		SetShaderValue(shader, bleedRadiusLoc, &bleedRadius, SHADER_UNIFORM_FLOAT);
		//		SetShaderValue(shader, bleedIntensityLoc, &bleedIntensity, SHADER_UNIFORM_FLOAT);
		//		SetShaderValue(shader, colorThresholdLoc, &colorThreshold, SHADER_UNIFORM_FLOAT);
		//	}

		//	DrawTexturePro(inputTexture.texture, sourceRec, destRec, origin, 0.0f, WHITE);

		//	EndShaderMode();

		//}

		//EndTextureMode();
	}
}

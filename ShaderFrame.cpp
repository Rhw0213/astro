#include "ShaderFrame.h"

namespace astro
{
	void ShaderFrame::Init(std::shared_ptr<Object> object)
	{
		//auto* frameShaderComponent = object.get()->GetComponent<ShaderFrameComponent>(ComponentType::SHADER_FRAME_COMPONENT);
		//const Shader& shader = frameShaderComponent->shader;

		//if (frameShaderComponent)
		//{
		//	frameShaderComponent->timeLoc = GetShaderLocation(shader, "iTime");
		//	frameShaderComponent->resolutionLoc = GetShaderLocation(shader, "iResolution");
		//	frameShaderComponent->positionLoc = GetShaderLocation(shader, "shipPos");
		//	frameShaderComponent->directionLoc = GetShaderLocation(shader, "shipDir");
		//}
	}

	void ShaderFrame::Update(std::shared_ptr<Object> object, const RenderTexture2D& inputTexture, const RenderTexture2D& outputTexture)
	{
        //auto* frameShaderComponent = object.get()->GetComponent<ShaderFrameComponent>(ComponentType::SHADER_FRAME_COMPONENT);
        //auto* transformComponent = object.get()->GetComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);

        //const Shader& shader = frameShaderComponent->shader;
        //MyVector2 position = transformComponent->worldPosition;

        //int timeLoc = frameShaderComponent->timeLoc;
        //int resolutionLoc = frameShaderComponent->resolutionLoc;
        //int positionLoc = frameShaderComponent->positionLoc;
        //int directionLoc = frameShaderComponent->directionLoc;

        //Rectangle& sourceRec = frameShaderComponent->sourceRec;
        //Rectangle& destRec = frameShaderComponent->destRec;
        //MyVector2& origin = frameShaderComponent->origin;

        //sourceRec = { 0.0f, 0.0f,
        //                static_cast<float>(inputTexture.texture.width),
        //                static_cast<float>(-inputTexture.texture.height) };
        //destRec = { 0.0f, 0.0f,
        //              static_cast<float>(outputTexture.texture.width),
        //              static_cast<float>(outputTexture.texture.height) };
        //origin = { 0.f, 0.f };

        //BeginTextureMode(outputTexture);
        //ClearBackground(BLANK);
        //{
        //    BeginShaderMode(shader);
        //    if (timeLoc != -1 && resolutionLoc != -1 && positionLoc != -1 && directionLoc != -1)
        //    {
        //        frameShaderComponent->time += GetFrameTime() * 10;
        //        float time = frameShaderComponent->time;

        //        // 벡터 타입을 float 배열로 변환
        //        float resolution[2] = {
        //            static_cast<float>(outputTexture.texture.width),
        //            static_cast<float>(outputTexture.texture.height)
        //        };

        //        float pos[2] = { position.x(), position.y() };
        //        //float dir[2] = { direction.x(), -direction.y() };

        //        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        //        SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
        //        SetShaderValue(shader, positionLoc, pos, SHADER_UNIFORM_VEC2);
        //        //SetShaderValue(shader, directionLoc, dir, SHADER_UNIFORM_VEC2);
        //    }

        //    DrawTexturePro(inputTexture.texture, sourceRec, destRec, origin, 0.0f, WHITE);
        //    EndShaderMode();
        //}
        //EndTextureMode();
	}
}

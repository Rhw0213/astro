#pragma once
#include "Component.h"
#include "System.h"
#include <array>
#include <vector>
namespace astro
{
	class RenderSystem : public System
	{
	public:
		RenderSystem();
		void Init() override;
		void Process() override;
		void Render();

		void UpdateBatchData();
		void RenderBathces();
	private:
		std::array<float, 4> ColorToFloatArray(Color color)
		{
			return {
				color.r / 255.0f,
				color.g / 255.0f,
				color.b / 255.0f,
				color.a / 255.0f,
			};
		}

		void AddWorldVertex(std::vector<float>& vertices, MyVector2 localPoint, const TransformComponent& transformComponent, const std::array<float, 4>& colorArray)
		{
			MyVector2 scalePoint = localPoint * transformComponent.worldScale;

			MyVector2 worldPosition = transformComponent.worldPosition + scalePoint.Rotate(transformComponent.worldRotation);

			vertices.push_back(worldPosition.x());
			vertices.push_back(worldPosition.y());
			vertices.push_back(colorArray[0]);
			vertices.push_back(colorArray[1]);
			vertices.push_back(colorArray[2]);
			vertices.push_back(colorArray[3]);
		}

		struct BatchData
		{
			std::vector<float> vertices; 
			unsigned int vboId = 0;
			unsigned int vaoId = 0;
			bool dirty = true;
		};

		std::map<ObjectType, BatchData> batchs;
		RenderTexture2D texture;
	};
}

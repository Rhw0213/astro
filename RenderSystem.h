#pragma once
#include "Component.h"
#include "System.h"
#include "UI.h"
#include <vector>
namespace astro
{
	class RenderSystem : public System
	{
	public:
		RenderSystem();
		void Init() override;
		void Process() override;
	private:
		std::vector<std::shared_ptr<UI>> uiObjects;
		std::vector<std::shared_ptr<Object>> cameraObjects;
		RenderTexture2D texture;
	};
}

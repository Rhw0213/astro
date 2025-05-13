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
		void Render();
	private:
		RenderTexture2D texture;
	};
}

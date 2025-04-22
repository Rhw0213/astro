#pragma once
#include "UI.h"

namespace astro
{
	class UIControll : public UI
	{
	public:
		UIControll();
		ObjectType GetType() const override { return ObjectType::CONTROLL_UI_ID; };
		void Init() override;
		void Update() override;
		void Draw() override;
	};
}

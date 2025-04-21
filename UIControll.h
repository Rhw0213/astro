#pragma once
#include "UI.h"

namespace astro
{
	class UIControll : public UI
	{
	public:
		UIControll();
		ObjectID GetID() const override { return ObjectID::CONTROLL_UI_ID; };
		void Init() override;
		void Update() override;
		void Draw() override;
	};
}

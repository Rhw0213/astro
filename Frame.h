#pragma once
#include "GameObject.h"

namespace astro
{
	class Frame : public GameObject 
	{
	public:
		Frame(const MyVector2& position);
		void Init() override;
		void Update() override;

		ObjectID GetID() const override { return ObjectID::FRAME_ID; };
	private:
	};
}

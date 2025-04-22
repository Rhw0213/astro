#pragma once
#include "GameObject.h"

namespace astro
{
	class Frame : public GameObject 
	{
	public:
		Frame(InstanceID targetId);
		void Init() override;
		void Update() override;

		ObjectType GetType() const override { return ObjectType::FRAME_ID; };
	private:
	};
}

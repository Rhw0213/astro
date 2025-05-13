#pragma once
#include "GameObject.h"

namespace astro
{
/// @brief Frame
	class Frame : public GameObject 
	{
	public:
		Frame(InstanceID parentId = 0, InstanceID manageId = 0);
		void Init() override;
		void Update() override;

		ObjectType GetType() const override { return ObjectType::FRAME_ID; };
	private:
		InstanceID parentId;
		InstanceID manageId;
	};
}

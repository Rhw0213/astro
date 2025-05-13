#pragma once
#include "GameObject.h"

namespace astro
{
/// @brief FrameEffect
	class FrameManage: public GameObject 
	{
	public:
		FrameManage(InstanceID frameOwner = 0);
		ObjectType GetType() const override { return ObjectType::FRAME_MANAGE_ID; };

		void Init() override;
		void Update() override;
	private:	
		InstanceID frameOwner;
	};
}
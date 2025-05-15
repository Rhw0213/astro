#pragma once
#include "GameObject.h"

namespace astro
{
	class Missile : public GameObject
	{
	public:
		Missile(InstanceID missileOwner = 0, InstanceID frameManageId = 0);
		void Init() override;
		void Update() override;

		ObjectType GetType() const override { return ObjectType::MISSILE_ID; };
	private:
		InstanceID missileOwner;
		InstanceID frameManageId;
	};
}
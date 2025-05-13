#pragma once
#include "GameObject.h"

namespace astro
{
	class Missile : public GameObject
	{
	public:
		Missile(InstanceID missileOwner = 0);
		void Init() override;
		void Update() override;

		virtual ObjectType GetType() const override { return ObjectType::GAMEOBJECT_ID; };
	private:
		InstanceID missileOwner;
	};
}
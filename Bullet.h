#pragma once
#include "GameObject.h"

namespace astro
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		void Init() override;
		void Update() override;

		virtual ObjectType GetType() const override { return ObjectType::GAMEOBJECT_ID; };
	private:

	};
}
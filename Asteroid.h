#pragma once
#include "GameObject.h"
#include "PerlinNoise.h"

namespace astro
{
	class Asteroid : public GameObject
	{
	public:
		Asteroid(const MyVector2& position = {0, 0});
		void Init() override;
		void Update() override;

		ObjectID GetID() const override { return ObjectID::ASTEROID_ID; };
	private:
		void SetVertex();
		PerlinNoise perlinNoise;
	};
}

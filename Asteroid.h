#pragma once
#include "GameObject.h"
#include "PerlinNoise.h"

namespace astro
{
	class Asteroid : public GameObject
	{
	public:
		Asteroid(InstanceID parentId = 0);
		void Init() override;
		void Update() override;

		ObjectType GetType() const override { return ObjectType::ASTEROID_ID; };
	private:
		void SetVertex();
		PerlinNoise perlinNoise;
	};
}

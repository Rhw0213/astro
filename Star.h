#pragma once
#include "GameObject.h"

namespace astro
{
/// @brief Star
	class Star : public GameObject
	{
	public:
		Star(InstanceID parentId = 0);
		ObjectType GetType() const override { return ObjectType::STAR_ID; };
		void Init() override;
		void Update() override;
	private:

	};
}

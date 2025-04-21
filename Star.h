#pragma once
#include "GameObject.h"

namespace astro
{
	class Star : public GameObject
	{
	public:
		Star(const MyVector2& position = {0, 0});
		ObjectID GetID() const override { return ObjectID::STAR_ID; };
		void Init() override;
		void Update() override;


	private:
		struct IsLineOut
		{
			bool left = false;
			bool right = false;
			bool top = false;
			bool bottom = false;
		};

		struct Bound
		{
			float left = 0.f;
			float right = 0.f;
			float top = 0.f;
			float bottom = 0.f;
		};

		void Move();
		IsLineOut CheckCameraRangeOut(Bound bound, const MyVector2& position);
		Bound CalculaterBoundLine();
		void SetRandomPosition(Bound bound, IsLineOut isLineOut, MyVector2& position);
		const MyVector2& ViewScreenSize();
	};
}

#pragma once
#include "System.h"

namespace astro
{
	class StarSystem : public System
	{
	public:
		void Init() override;
		void Process() override;
	private:
		/// @brief IsLineOut
		struct IsLineOut
		{
			bool left = false;
			bool right = false;
			bool top = false;
			bool bottom = false;
		};

		/// @brief Bound
		struct Bound
		{
			float left = 0.f;
			float right = 0.f;
			float top = 0.f;
			float bottom = 0.f;
		};

		IsLineOut CheckCameraRangeOut(Bound bound, const MyVector2& position);
		Bound CalculaterBoundLine();
		void SetRandomPosition(Bound bound, IsLineOut isLineOut, MyVector2& position);
		MyVector2 ViewScreenSize();
	};
}
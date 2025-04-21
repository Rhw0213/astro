#pragma once
#include "System.h"

namespace astro
{
	class RotationSystem : public System
	{
	public:
		void Init() override;
		void Process() override;
	};
}

#pragma once
#include "System.h"

namespace astro
{
	class BulletSystem : public System
	{
		BulletSystem();
		void Init() override;
		void Process() override;
	};
}
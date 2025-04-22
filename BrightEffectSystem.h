#pragma once
#include "System.h"

namespace astro
{
	class BrightEffectSystem : public System
	{
	public:
		BrightEffectSystem() = default;
		void Init() override;
		void Process() override;
	private:
	};
}

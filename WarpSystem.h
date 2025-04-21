#pragma once
#include "System.h"

namespace astro
{
	class WarpSystem : public System
	{
	public:
		void Init() override;
		void Process() override;
	private:
	};
}

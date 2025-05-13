#pragma once
#include "System.h"

namespace astro
{
/// @brief WarpSystem
	class WarpSystem : public System
	{
	public:
		void Init() override;
		void Process() override;
	private:
	};
}

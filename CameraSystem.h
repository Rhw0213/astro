#pragma once
#include "System.h"

namespace astro
{
	class CameraSystem : public System
	{
	public:
		void Init() override;
		void Process() override;
	private:
	};
}

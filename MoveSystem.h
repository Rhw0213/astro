#pragma once
#include "System.h"
#include "Component.h"

namespace astro
{
	class MoveSystem : public System
	{
	public:
		void Init() override;
		void Process() override;
	private:
	};
}

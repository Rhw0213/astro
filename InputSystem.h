#pragma once
#include "System.h"
#include "Component.h"
#include <vector> 

namespace astro
{
	class InputSystem : public System
	{
	public:
		void Init() override;
		void Process() override;

	private:
	};
}

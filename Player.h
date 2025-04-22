#pragma once
#include "GameObject.h"
#include <memory> 

namespace astro
{
	class Player : public GameObject, public std::enable_shared_from_this<Player>
	{
	public:
		Player(const MyVector2& position = {0, 0});
		ObjectType GetType() const override { return ObjectType::PLAYER_ID; };
		void Init() override;
		void Update() override;
	private:
	};
}

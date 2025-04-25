#pragma once
#include <string>
#include <memory>

namespace astro
{
	class GameSettingManager
	{
	public:
		static GameSettingManager& Instance();

		bool LoadFile(const std::string& filename = "game/setting/setting.txt");

		float frameLifeTime;
		float frameSpeed;
		float framePlayerSize;
		float frameTargetOffsetX;
		float frameTargetOffsetY;
		float frameIncreaseFrameDefaultSize;
		float frameIncreaseFrameWarpSize;

		float bulletPlayerCount;
		float bulletSpeed;

	private:
		GameSettingManager() = default;
	};
}
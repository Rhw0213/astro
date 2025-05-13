#pragma once
#include <string>
#include <memory>

namespace astro
{
/// @brief GameSettingManager
	class GameSettingManager
	{
	public:
		static GameSettingManager& Instance();

		bool LoadFile(const std::string& filename = "game/setting/setting.txt");

		float frameLifeTime = 0;
		float frameSponTime = 0;
		float frameSpeed = 0;
		float frameSize = 0;
		float frameWarpSize = 0;
		float frameEnableTrigerMaxTime = 0;
		float frameTargetOffsetX = 0;
		float frameTargetOffsetY = 0;

		float bulletPlayerCount = 0;
		float bulletSpeed = 0;

		float warpStarTailLength = 0;
		float minStarSize = 0;
		float maxStarSize = 0;

		float playerSize = 0;

	private:
		GameSettingManager() = default;
	};
}
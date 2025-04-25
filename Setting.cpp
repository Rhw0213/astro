#include "Setting.h"
#include <fstream>
#include <sstream>

namespace astro
{
	GameSettingManager& GameSettingManager::Instance()
	{
		static GameSettingManager instance;
		return instance;
	}

	bool GameSettingManager::LoadFile(const std::string& filename)
	{
		std::ifstream file(filename);

		if (!file.is_open())
		{
			return false;
		}

		std::string line;

		while (std::getline(file, line))
		{
			if (line.empty() || line[0] == '#' || line[0] == '/')
			{
				continue;
			}

			std::istringstream streamLine(line);
			std::string key;
			float value;

			if (streamLine >> key >> value)
			{
				//Frame
				if (key == "FrameLifeTime")								{ frameLifeTime					= value; }
				else if (key == "FrameSpeed")							{ frameSpeed					= value; }
				else if (key == "FramePlayerSize")						{ framePlayerSize				= value; }
				else if (key == "FrameTargetOffsetX")					{ frameTargetOffsetX			= value; }
				else if (key == "FrameTargetOffsetY")					{ frameTargetOffsetY			= value; }
				else if (key == "FrameIncreaseFrameDefaultSize")		{ frameIncreaseFrameDefaultSize = value; }
				else if (key == "FrameIncreaseFrameWarpSize")			{ frameIncreaseFrameWarpSize	= value; }

				//PlayerBullet
				else if (key == "BulletPlayerCount")					{ bulletPlayerCount				= value; }
				else if (key == "BulletSpeed")							{ bulletSpeed					= value; }
		}

		file.close();

		return true;
	}
}

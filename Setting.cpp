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
				if (key == "FrameLifeTime")							{ frameLifeTime					= value; }
				else if (key == "FrameSpeed")						{ frameSpeed					= value; }
				else if (key == "FrameSize")						{ frameSize						= value; }
				else if (key == "FrameEnableTrigerMaxTime")			{ frameEnableTrigerMaxTime		= value; }
				else if (key == "FrameTargetOffsetX")				{ frameTargetOffsetX			= value; }
				else if (key == "FrameTargetOffsetY")				{ frameTargetOffsetY			= value; }

				//PlayerMissile
				else if (key == "MissilePlayerCount")				{ bulletPlayerCount				= value; }
				else if (key == "MissileSpeed")						{ bulletSpeed					= value; }

				//Warp
				else if (key == "WarpStarTailLength")				{ warpStarTailLength			= value; }
				else if (key == "MinStarSize")						{ minStarSize					= value; }
				else if (key == "MaxStarSize")						{ maxStarSize					= value; }
				else if (key == "PlayerSize")						{ playerSize					= value; }
				else if (key == "FrameWarpSize")					{ frameWarpSize					= value; }
				else if (key == "FrameSponTime")					{ frameSponTime					= value; }

			}
		}

		file.close();

		return true;
	}
}

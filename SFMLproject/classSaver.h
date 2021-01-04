#pragma once
#include <fstream>
#include <iomanip>


#include "level.h"
#include "json.hpp"

template<typename type>
class ClassSaver final
{
public:
	ClassSaver() = delete;
};

template<>
class ClassSaver<Level> final
{
public:
	ClassSaver() = delete;
	static void save(size_t numberLevel, Level& level)
	{
		nlohmann::json saveFile;
		saveFile["floatLimit"] = level.floatLimit;
		saveFile["wallSize"] = level.wallSize;
		saveFile["levelSize.x"] = level.levelSize.x;
		saveFile["levelSize.y"] = level.levelSize.y;
		saveFile["level.floor.textureName"] = level.floor.textureName;
		saveFile["level.walls.size"] = level.walls.size();
		for (size_t i = 0; i < level.walls.size(); ++i)
		{
			saveFile[std::string("level.walls[") + std::to_string(i) + "].wallName"] = level.walls[i].wallName;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].size"] = level.walls[i].size;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].type"] = level.walls[i].type;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.x"] = level.walls[i].coordinate.x;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.y"] = level.walls[i].coordinate.y;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].speed"] = level.walls[i].speed;
		}
		std::ofstream stream(std::string("../ResourceFile/Levels/Level_") + std::to_string(numberLevel) + ".json");
		stream << std::setw(4) << saveFile << std::endl;
	}

	static void download(size_t numberLevel, Level& level)
	{
		nlohmann::json saveFile;
		std::ifstream stream(std::string("../ResourceFile/Levels/Level_") + std::to_string(numberLevel) + ".json");
		stream >> saveFile;
		level.wallSize = saveFile["wallSize"];
		level.levelSize.x = saveFile["levelSize.x"];
		level.levelSize.y = saveFile["levelSize.y"];
		level.floor.textureName = saveFile["level.floor.textureName"];
		for (size_t i = 0; i < saveFile["level.walls.size"]; ++i)
		{
			Wall wall(saveFile[std::string("level.walls[") + std::to_string(i) + "].wallName"],
				{ saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.x"] ,
				saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.y"] }, 
				saveFile[std::string("level.walls[") + std::to_string(i) + "].type"], 
				saveFile[std::string("level.walls[") + std::to_string(i) + "].size"]);
			level.walls.push_back(wall);
		}
		
	}
	
};
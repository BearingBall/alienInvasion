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
		saveFile["wallSize"] = level.getWallSize();
		saveFile["levelSize.x"] = level.getLevelSize().x;
		saveFile["levelSize.y"] = level.getLevelSize().y;
		saveFile["level.floor.textureName"] = level.getFloor().getTextureName();
		saveFile["level.walls.size"] = level.getWalls().size();
		for (size_t i = 0; i < level.getWalls().size(); ++i)
		{
			saveFile[std::string("level.walls[") + std::to_string(i) + "].wallName"] = level.getWalls()[i].wallName;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].size"] = level.getWalls()[i].size;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].type"] = level.getWalls()[i].type;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.x"] = level.getWalls()[i].getCoordinate().x;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.y"] = level.getWalls()[i].getCoordinate().y;
			saveFile[std::string("level.walls[") + std::to_string(i) + "].speed"] = level.getWalls()[i].getSpeed();
		}
		std::ofstream stream(std::string("../ResourceFile/Levels/Level_") + std::to_string(numberLevel) + ".json");
		stream << std::setw(4) << saveFile << std::endl;
	}

	static void download(size_t numberLevel, Level& level)
	{
		nlohmann::json saveFile;
		std::ifstream stream(std::string("../ResourceFile/Levels/Level_") + std::to_string(numberLevel) + ".json");
		stream >> saveFile;
		level.getWallSize() = saveFile["wallSize"];
		level.getLevelSize().x = saveFile["levelSize.x"];
		level.getLevelSize().y = saveFile["levelSize.y"];
		level.getFloor().getTextureName() = saveFile["level.floor.textureName"];
		for (size_t i = 0; i < saveFile["level.walls.size"]; ++i)
		{
			Wall wall(saveFile[std::string("level.walls[") + std::to_string(i) + "].wallName"],
				{ saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.x"] ,
				saveFile[std::string("level.walls[") + std::to_string(i) + "].coordinate.y"] }, 
				saveFile[std::string("level.walls[") + std::to_string(i) + "].type"], 
				saveFile[std::string("level.walls[") + std::to_string(i) + "].size"]);
			level.getWalls().push_back(wall);
		}
		
	}
	
};
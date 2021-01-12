#pragma once
#include <string>

class ResourceFileNaming final
{
public:
	ResourceFileNaming() = delete;
	
	inline static const std::string windowName = "AlienInvasion";
	inline static const std::string fontName = "../ResourceFile/Konstanting.ttf";
	inline static const std::string groundName = "../ResourceFile/ground.png";
	inline static const std::string wallName = "../ResourceFile/wall.png";
	inline static const std::string spawnPointName = "../ResourceFile/spawnPoint.png";
	inline static const std::string doorInName = "../ResourceFile/doorIn.png";
	inline static const std::string doorOutName = "../ResourceFile/doorOut.png";
	inline static const std::string backgroundName = "../ResourceFile/background.png";
	inline static const std::string soldierName = "../ResourceFile/soldier.png";
	inline static const std::string heroName = "../ResourceFile/hero.png";
};

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
	static void save(size_t numberLevel, Level& level);

	static void download(size_t numberLevel, Level& level);
};
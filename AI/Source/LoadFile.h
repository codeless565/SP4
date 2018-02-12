//Load from files for control, map, etc.
#ifndef LOADFILE_H
#define LOADFILE_H

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../Common/Source/SingletonTemplate.h"

#include <string>
#include <vector>

class LoadFile : public Singleton<LoadFile>
{
	friend Singleton<LoadFile>;

public:
	std::vector<std::string> LoadCSV(const std::string filePath); // Load CSV file
	
};

#endif // ! LOADFILE


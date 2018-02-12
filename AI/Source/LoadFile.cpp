#include "LoadFile.h"

/*-----This function is to load CSV file (can be used for GameObject Factory, Minions Info, Shop Price Info-----*/
std::vector<std::string> LoadFile::LoadCSV(const std::string filePath)
{
	std::vector<std::string> tempVec;

	std::ifstream infile;
	infile.open(filePath);

	std::string line;
	if (infile)
	{
		getline(infile, line);
		while (getline(infile, line))
		{
			tempVec.push_back(line);
		}
	}
	else
		std::cout << "Impossible to open " << filePath << ". Are you sure you are in the right directory?\n";

	infile.close();

	return tempVec;
}


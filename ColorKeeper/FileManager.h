#pragma once

#include <string>
#include <map>
#include <fstream>
#include <vector>

using std::string;
using std::map;
using std::ofstream;
using std::ifstream;
using std::vector;

class FileManager
{
public:
	static FileManager* GetInstance();
	static bool WriteMap(const string& filename, const map<string, int>& fileMap);
	static bool ReadMap(const string& fileName, map<string, int>& fileMap);

private:
	static FileManager* instance;
	FileManager();
};
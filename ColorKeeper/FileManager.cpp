#include "FileManager.h"

FileManager* FileManager::instance = 0;

FileManager::FileManager()
= default;

FileManager* FileManager::GetInstance()
{
	if (!instance)
		instance = new FileManager();

	return instance;
}

bool FileManager::WriteMap(const string& filename, const map<string, int>& fileMap)
{
	ofstream ofile;
	
	ofile.open(filename.c_str());
	
	if (!ofile)
		return false;
	
	for (map<string, int>::const_iterator iter = fileMap.begin(); iter != fileMap.end(); ++iter)
	{
		ofile << iter->first << "|" << iter->second;
		ofile << "\n";
	}
	
	return true;
}

bool FileManager::ReadMap(const string& filename, map<string, int>& fileMap)
{
	ifstream ifile;
	ifile.open(filename.c_str());
	
	if (!ifile)
		return false;
	
	string line;
	const string delimiter = "|";
	string key, value;

	while (ifile >> line)
	{
		key = line.substr(0, line.find(delimiter));
		value = line.substr(line.find(delimiter) + 1, line.length());

		fileMap.insert(std::pair<string, int>(key, std::stoi(value)));
	}
	return true;
}
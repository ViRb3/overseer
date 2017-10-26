#pragma once
#include <string>
#include <vector>

using namespace std;

struct FileInfo
{
	string name;
	int type;
};

namespace Overseer
{
	vector<FileInfo> ListFiles(const string &path);

	vector<size_t> FindInFile(const string &needle, FILE *pFile);

	int CheckFile(const string &filePath);

	vector<string> Search(const string &path);
}
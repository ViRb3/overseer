#pragma once
#include <string>
#include <vector>

using namespace std;

namespace Overseer
{
	extern vector<string> BlacklistedDirs;
	extern vector<string> BlacklistedFiles;
	extern vector<string> BlacklistedExts;

	extern vector<string> MatchStrings;
	extern bool Verbose;
	extern const int BLOCKSIZE;
	extern const int MAXFILESIZE;
}
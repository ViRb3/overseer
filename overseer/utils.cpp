#include "utils.h"
#include "overseer.h"
#include "config.h"

#include <algorithm>
#include <sstream>

namespace Utils
{
	bool IsDirBlacklisted(const string &directoryPath)
	{
		for (const string &blacklistedDir : Overseer::BlacklistedDirs)
			if (directoryPath == blacklistedDir)
				return true;
		return false;
	}

	bool IsFileBlacklisted(const string &filePath)
	{
		for (const string &blacklistedFile : Overseer::BlacklistedFiles)
			if (filePath == blacklistedFile)
				return true;
		return false;
	}

	bool IsExtBlacklisted(const string &fileName)
	{

		const char *ext = strrchr(fileName.c_str(), '.');
		if (ext == nullptr)
			return false;

		for (const string &blacklistedExt : Overseer::BlacklistedExts)
			if (strcmp(ext, blacklistedExt.c_str()) == 0)
				return true;
		return false;
	}

	string ToLowerString(string data)
	{
		transform(data.begin(), data.end(), data.begin(),::tolower);
		return data;
	}

	string ToUpperString(string data)
	{
		transform(data.begin(), data.end(), data.begin(),::toupper);
		return data;
	}

	string GetSeparatedMac(string macAddr, char separator)
	{
		string result = string();
		for (int i = 0; i < macAddr.length(); i++)
		{
			if (i > 0 && i % 2 == 0) // every 2nd
			    result += separator;
			result += macAddr[i];
		}
		return result;
	}

	string GetBinaryMac(const string &macAddr)
	{
		istringstream buffer(macAddr);
		vector<unsigned char> bbuffer;

		unsigned char ch;
		while (buffer >> std::hex >> ch)
			bbuffer.push_back(ch);

		string result = string();
		for (char ch : bbuffer)
			result += ch;

		return result;
	}
}
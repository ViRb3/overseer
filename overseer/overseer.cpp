#include "overseer.h"
#include "utils.h"
#include "config.h"

#include "dirent.h"
#include "sys/stat.h"
#include <iostream>

using namespace std;

namespace Overseer
{
	vector<FileInfo> ListFiles(const string &path)
	{
		vector<FileInfo> result;
		dirent *pDirEntry;
		DIR *pDir;

		pDir = opendir(path.c_str());
		if (pDir == nullptr)
			return result;

		while ((pDirEntry = readdir(pDir)) != nullptr)
		{
			FileInfo fileInfo;
			fileInfo.name = string(pDirEntry->d_name);
			fileInfo.type = pDirEntry->d_type;
			result.push_back(fileInfo);
		}

		closedir(pDir);
		return result;
	}

	vector<size_t> FindInFile(const string &needle, FILE *pFile)
	{
		vector<size_t> result;
		size_t needleLength = needle.length();

		char buffer[BLOCKSIZE];
		char *buffer2 = new char[needleLength * 2]; //TODO: Free

		while(!feof(pFile))
		{
			size_t readBytes = fread(buffer, sizeof(char), sizeof(char) * BLOCKSIZE, pFile);
			string haystack(buffer, readBytes);

			size_t n = haystack.find(needle);
			if (n != string::npos)
			{
				size_t pos = ftell(pFile) - readBytes + n;
				cout << "Found string at: " << pos << "\n";
				result.push_back(pos);
				fseek(pFile, pos + needleLength, 0); //TODO: Fseek accepts long position while ftell outputs size_t
				continue;
			}

			if (readBytes < BLOCKSIZE) // end of file
			    break;

			// case if string is split in two blocks
			memcpy(buffer2, buffer + readBytes - needleLength, sizeof(char) * needleLength);
			size_t readBytes2 = fread(buffer, sizeof(char), sizeof(char) * needleLength, pFile);
			memcpy(buffer2 + needleLength, buffer, sizeof(char) * readBytes2);

			haystack = string(buffer2, needleLength + readBytes2);

			n = haystack.find(needle);
			if (n != string::npos)
			{
				size_t pos = ftell(pFile) - readBytes2 - needleLength + n;
				cout << "Found string 2 at: " << pos << "\n";
				result.push_back(pos);
			}
		}

		delete[] buffer2;
		fseek(pFile, 0, SEEK_SET);
		return result;
	}

	int CheckFile(const string &filePath)
	{
		FILE *pFile = fopen(filePath.c_str(), "rb"); // read binary
		if(pFile == nullptr)
		    return 0;

		if (fseek(pFile, 0L, SEEK_END) < 0)
		{
			fclose(pFile);
			return 0;
		}

		long size = ftell(pFile);
		if (size > MAXFILESIZE)
		{
			fclose(pFile);
			return 0;
		}

		rewind(pFile);

		if (Verbose)
			cout << "Checking file: " << filePath << "\n";

		vector<size_t> matches = vector<size_t>();

		for (const string &matchString : MatchStrings)
			for (size_t match : FindInFile(matchString, pFile))
				matches.push_back(match);

		if (!matches.empty())
			cout << "Matched file: " << filePath << "\n";

		fclose(pFile);
		return 1;
	}

	vector<string> Search(const string &path)
	{
		vector<string> result;

		vector<FileInfo> vecFiles = ListFiles(path);
		if (vecFiles.empty())
			return result;

		for (FileInfo file : vecFiles)
		{
			if (file.name == "." || file.name == "..")
				continue;

			if (path == "/")
				file.name = "/" + file.name;
			else
				file.name = path + "/" + file.name;

			struct stat st {};
			if (stat(file.name.c_str(), &st) == 0) // follows symlinks
			{
				if (st.st_mode & S_IFDIR && file.type != DT_LNK) // don't follow directory symlink (avoid loop)
				{
					if (!Utils::IsDirBlacklisted(file.name))
					{
						for (const string &result2 : Search(file.name))
							result.push_back(result2);
					}
				}
				else if (st.st_mode & S_IFREG) //TODO: Check and skip symlink files (lstat)
				{
					if (!Utils::IsExtBlacklisted(file.name) && !Utils::IsFileBlacklisted(file.name))
						CheckFile(file.name);
				}
			}
		}

		return result;
	}
}
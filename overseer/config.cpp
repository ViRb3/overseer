#include "config.h"

namespace Overseer
{
	vector<string> BlacklistedDirs = { 
		"/acct",
		"/cache",
		"/data/app",
		"/data/data",
		"/data/media",
		"/dev",
		"/mnt",
		"/proc",
		"/storage",
		"/sys/power",
		"/sys/kernel" 
	};
	vector<string> BlacklistedFiles = {};
	vector<string> BlacklistedExts = { 
		".zip",
		".gzip",
		".tar",
		".rar",
		".mp3",
		".ogg",
		".wav",
		".mp4",
		".mov",
		".jpg",
		".jpeg",
		".bmp",
		".png",
		".apk" 
	};

	vector<string> MatchStrings = vector<string>();
	bool Verbose = false;
	const int BLOCKSIZE = 4096;
	const int MAXFILESIZE = 10000000L;   // 10MB
}
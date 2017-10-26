#include "config.h"

namespace Overseer
{
	const int BLOCKSIZE = 4096;
	const int MAXFILESIZE = 10000000L; // 10MB
	
	vector<string> BlacklistedDirs = { 
		"/acct",
		"/cache",
		"/data/app",
		"/data/cache",
		"/data/dalvik-cache",
		"/data/data",
		"/data/media",
		"/dev",
		"/magisk",
		"/mnt",
		"/proc",
		"/storage",
		"/sys/power",
		"/sys/kernel",
		"/system/app",
		"/system/priv-app",
	};

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

	vector<string> BlacklistedFiles = {};
	vector<string> MatchStrings = vector<string>();
	bool Verbose = false;
}
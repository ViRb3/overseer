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
    extern vector<string> BlacklistedDirs;
    extern vector<string> BlacklistedFiles;
    extern vector<string> BlacklistedExts;

    extern vector<string> MatchStrings;
    extern bool Verbose;
    extern const int BLOCKSIZE;
    extern const int MAXFILESIZE;

    vector<FileInfo> ListFiles(const string &path);

    vector<size_t> FindInFile(const string &needle, FILE *pFile);

    int CheckFile(const string &filePath);

    vector<string> Search(const string &path);
}
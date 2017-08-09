#include <string>
#include <vector>

using namespace std;

namespace Utils
{
    bool IsDirBlacklisted(const string &directoryPath);

    bool IsFileBlacklisted(const string &filePath);

    bool IsExtBlacklisted(const string &fileName);

    string ToLowerString(string data);

    string ToUpperString(string data);

    string GetSeparatedMac(string macAddr, char separator);

    string GetBinaryMac(const string &macAddr);
}
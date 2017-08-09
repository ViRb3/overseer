#include "main.h"
#include "overseer.h"
#include "utils.h"

#include <iostream>

using namespace std;

bool Prepare(const string &inputMacStr)
{
    if (inputMacStr.find(':') != std::string::npos)
    {
        cout << "Incorrect MAC format! Check usage.\n";
        return false;
    }

    string macAddr = Utils::ToUpperString(inputMacStr);
    Overseer::MatchStrings.push_back(macAddr);
    Overseer::MatchStrings.push_back(Utils::GetSeparatedMac(macAddr, ':'));

    macAddr = Utils::ToLowerString(macAddr);
    Overseer::MatchStrings.push_back(macAddr);
    Overseer::MatchStrings.push_back(Utils::GetSeparatedMac(macAddr, ':'));

    Overseer::MatchStrings.push_back(Utils::GetBinaryMac(Utils::GetSeparatedMac(macAddr, ' ')));
    return true;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "uMAC Overseer v0.1 - ViR Dash (ViRb3) - 2017\n";
        cout << "Usage: " << argv[0] << " MAC_ADDR [-v] [-b /ex/skipfile.ext /ex/sub/skipfile2.ext ...]\n";
        cout << "MAC_ADDR	format: AABBCCDDEEFF\n";
        cout << "-v			Verbose output\n";
        cout << "-b			blacklisted paths to skip\n";
        return 0;
    }

    bool blacklisting = false;
    for (int i = 1; i < argc; i++)
    {
        string arg = string(argv[i]);
        if (arg == "-v")
        {
            Overseer::Verbose = true;
            blacklisting = false;
            continue;
        }
        if (arg == "-b")
        {
            blacklisting = true;
            continue;
        }
        if (blacklisting)
        {
            Overseer::BlacklistedFiles.emplace_back(argv[i]);
            continue;
        }

        if (!Prepare(arg))
            return -1;
    }

    Overseer::Search("/");
    return 0;
}
//
// Created by griff on 7/10/2021.
//

#include "StringUtil.h"

namespace StringUtil
{
    std::vector<std::string> split(const std::string &str, const std::string &delim)
    {
        std::vector<std::string> result;
        unsigned long long delimLength = delim.size();

        unsigned long long start = 0;
        unsigned long long end;
        while ((end = str.find(delim, start)) != std::string::npos)
        {
            result.push_back(str.substr(start, end - start));
            start = end + delimLength;
        }

        if (start != str.size())
            result.push_back(str.substr(start));

        return result;
    }

    std::string stringVec2NullSeparatedString(const std::vector<std::string> &items)
    {
        std::string result;
        for (const std::string &str : items)
            result += str + '\0';

        return result;
    }
}

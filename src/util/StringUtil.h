//
// Created by griff on 7/10/2021.
//

#ifndef DATAVISUALIZATION_STRINGUTIL_H
#define DATAVISUALIZATION_STRINGUTIL_H


#include <string>
#include <vector>

namespace StringUtil
{
    std::vector<std::string> split(const std::string &str, const std::string &delim);
    std::string stringVec2NullSeparatedString(const std::vector<std::string> &items);
}


#endif //DATAVISUALIZATION_STRINGUTIL_H

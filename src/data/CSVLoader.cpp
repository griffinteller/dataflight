//
// Created by griff on 7/10/2021.
//

#include <util/StringUtil.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "CSVLoader.h"

#define DELIM ','
#define DELIM_LEN 1

CSVLoader::CSVLoader(std::string inPath)
: path (std::move(inPath)), columnIndices (inPath.size())
{
    std::ifstream file(path);

    std::string topLine;

    getline(file, topLine);
    rows = getRowsInFile(file);

    file.close();

    columns = StringUtil::split(topLine, std::string(1, DELIM));

    for (int i = 0; i < columns.size(); i++)
    {
        columnIndices.emplace(columns[i], i);
    }
}

const std::vector<std::string> &CSVLoader::getColumns() const
{
    return columns;
}

std::vector<float> CSVLoader::getBatchedFloatData(const std::vector<std::string> &columnsToLoad)
{
    int cols = columnsToLoad.size();
    std::ifstream file(path);
    std::vector<float> result (rows * cols);
    for (int col = 0; col < cols; col++)
    {
        float *batchStart = &result[col * rows];
        int index = columnIndices.at(columnsToLoad[col]);
        loadFloatColumn(index, batchStart, rows);
    }

    return result;
}

size_t CSVLoader::getRowsInFile(std::ifstream &file) const
{
    std::string line;
    size_t i = 0;

    while (getline(file, line), !line.empty() && !file.eof())
        i++;

    if (!line.empty())
        i++;

    return i;
}

void CSVLoader::loadFloatColumn(int columnIndex, float *out, int maxPoints) const
{
    std::ifstream file(path);

    std::string line;
    getline(file, line);  // top line

    size_t rowsToLoad = std::min(rows, (size_t) maxPoints);

    for (size_t row = 0; row < rowsToLoad; row++)
    {
        getline(file, line);

        size_t floatStart = 0;
        size_t floatEnd = -DELIM_LEN;
        for (size_t col = 0; col <= columnIndex; col++)
        {
            floatStart = floatEnd + DELIM_LEN;
            floatEnd = line.find(DELIM, floatStart);
        }

        std::string floatString = line.substr(floatStart, floatEnd - floatStart);

        out[row] = std::stof(floatString);
    }
}
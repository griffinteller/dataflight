//
// Created by griff on 7/10/2021.
//

#ifndef DATAVISUALIZATION_CSVLOADER_H
#define DATAVISUALIZATION_CSVLOADER_H


#include <string>
#include <vector>
#include <unordered_map>

class CSVLoader
{
    /*
     * Expects just floats, no quotes in csv
     */

private:
    std::string path;
    size_t rows;
    std::vector<std::string> columns;
    std::unordered_map<std::string, int> columnIndices;

    // doesn't inlcude top line
    size_t getRowsInFile(std::ifstream &file) const;

    // if max points is not reached, just stops, doesn't zero out
    void loadFloatColumn(int columnIndex, float *out, int maxPoints) const;

public:
    explicit CSVLoader(std::string path);

    const std::vector<std::string> &getColumns() const;

    // vector is allocated on heap, so make sure to delete when done
    std::vector<float> getBatchedFloatData(const std::vector<std::string> &columnsToLoad);
};


#endif //DATAVISUALIZATION_CSVLOADER_H

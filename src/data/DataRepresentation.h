//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_DATAREPRESENTATION_H
#define DATAVISUALIZATION_DATAREPRESENTATION_H


#include <vector>
#include <typedefs.h>
#include <string>
#include <unordered_map>

class DataRepresentation
{

    /*
     * Currently only supports float data
     */

private:
    std::vector<float> data;  // data is kept in interleaved format (one float for each dim).
    std::vector<std::string> dimensionNames;
    std::unordered_map<std::string, int> dimensionIndices;  // index in GPU memory that dims are arranged (same as
                                                            // the order in dimensionNames)
    int activeDimensionIndices[3];  // dimensions on x, y, and z axes
    int dimensions;
    int points;
    uint VAO;
    uint vertexVBO;

    void syncDimsWithGPU();

public:

    // data must be in batched form (ie xxxyyyzzz)
    DataRepresentation(std::vector<float> inData, std::vector<std::string> dimensionNames);

    uint getVAO() const;
    uint getSize() const;  // total floats in data
    const std::vector<float> &getData() const;
    const std::vector<std::string> &getDimensionNames() const;
    int getDimensions() const;
    int getPoints() const;

    void setDimension(int visualDim, int dataDim);
    void setDimension(int visualDim, std::string dataDimName);
    void setDimensions(int dataDim0, int dataDim1, int dataDim2);
    void setDimensions(std::string dataDimName0, std::string dataDimName1, std::string dataDimName2);

    ~DataRepresentation();
    DataRepresentation(const DataRepresentation &data) = default;
    DataRepresentation(DataRepresentation &&data) noexcept = default;
    DataRepresentation &operator=(const DataRepresentation &data) = default;
    DataRepresentation &operator=(DataRepresentation &&data) noexcept = default;
};


#endif //DATAVISUALIZATION_DATAREPRESENTATION_H

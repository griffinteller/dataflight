//
// Created by griff on 6/27/2021.
//

#ifndef DATAVISUALIZATION_DATAREPRESENTATION_H
#define DATAVISUALIZATION_DATAREPRESENTATION_H


#include <vector>
#include <typedefs.h>

class DataRepresentation
{
private:
    std::vector<float> data;  // 3D
    uint VAO;
    uint vertexVBO;

public:
    explicit DataRepresentation(std::vector<float> &inData);

    uint getVAO() const;
    uint getSize() const;
    const std::vector<float> &getVector();
};


#endif //DATAVISUALIZATION_DATAREPRESENTATION_H

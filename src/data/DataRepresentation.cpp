//
// Created by griff on 6/27/2021.
//

#include <glad/glad.h>
#include "DataRepresentation.h"

DataRepresentation::DataRepresentation(std::vector<float> inData, std::vector<std::string> dimensionNames)
: data (std::move(inData)), dimensionNames (std::move(dimensionNames)), dimensionIndices (),
activeDimensionIndices {0, 1, 2}, VAO (0), vertexVBO (0)
{
    dimensions = DataRepresentation::dimensionNames.size();
    points = data.size() / dimensions;

    for (int i = 0; i < dimensions; i++)
    {
        dimensionIndices.emplace(DataRepresentation::dimensionNames[i], i);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vertexVBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, points * sizeof(float), nullptr, GL_STATIC_DRAW);

    for (int i = 0; i < 3; i++) // dimensions able to be active at once
    {
        glVertexAttribPointer(i, 1, GL_FLOAT, false, sizeof(float), (void *) (sizeof(float) * i * points));
        glEnableVertexAttribArray(i);
    }

    syncDimsWithGPU();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

uint DataRepresentation::getVAO() const
{
    return VAO;
}

uint DataRepresentation::getSize() const
{
    return data.size();
}

const std::vector<float> &DataRepresentation::getData() const
{
    return data;
}

DataRepresentation::~DataRepresentation()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexVBO);
}

const std::vector<std::string> &DataRepresentation::getDimensionNames() const
{
    return dimensionNames;
}

int DataRepresentation::getDimensions() const
{
    return dimensions;
}

void DataRepresentation::setDimension(int visualDim, int dataDim)
{

}

void DataRepresentation::syncDimsWithGPU()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);

    for (int i = 0; i < 3; i++)
    {
        glBufferSubData(
                GL_ARRAY_BUFFER, i * sizeof(float) * points,
                sizeof(float) * points, data.data() + activeDimensionIndices[i] * points);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

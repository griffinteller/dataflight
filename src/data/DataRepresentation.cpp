//
// Created by griff on 6/27/2021.
//

#include <glad/glad.h>
#include <iostream>
#include "DataRepresentation.h"

DataRepresentation::DataRepresentation(std::vector<float> inData, std::vector<std::string> dimensionNames)
: data (std::move(inData)), dimensionNames (std::move(dimensionNames)), dimensionIndices (),
  activeDimensionIndices {0, 1, 2}, VAO (0), vertexVBO (0),
  shader(getDefaultVertShaderSource(), getDefaultFragShaderSource(), nullptr)
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
    glBufferData(GL_ARRAY_BUFFER, 3 * points * sizeof(float), data.data(), GL_STATIC_DRAW);

    for (int i = 0; i < 3; i++) // dimensions able to be active at once
    {
        glVertexAttribPointer(i, 1, GL_FLOAT, false, sizeof(float), (void *) (sizeof(float) * i * points));
        glEnableVertexAttribArray(i);
    }

    //syncDimsWithGPU();

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
    activeDimensionIndices[visualDim] = dataDim;
    syncDimsWithGPU();
}

void DataRepresentation::syncDimsWithGPU()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);

    for (int i = 0; i < 3; i++)
    {
        float *offset = ((float *) data.data()) + activeDimensionIndices[i] * points;

        glBufferSubData(
                GL_ARRAY_BUFFER, i * sizeof(float) * points,
                sizeof(float) * points, offset);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int DataRepresentation::getPoints() const
{
    return points;
}

void DataRepresentation::setDimension(int visualDim, std::string dataDimName)
{
    setDimension(visualDim, dimensionIndices[dataDimName]);
    syncDimsWithGPU();
}

void DataRepresentation::setDimensions(int dataDim0, int dataDim1, int dataDim2)
{
    activeDimensionIndices[0] = dataDim0;
    activeDimensionIndices[1] = dataDim1;
    activeDimensionIndices[2] = dataDim2;
    syncDimsWithGPU();
}

void DataRepresentation::setDimensions(std::string dataDimName0, std::string dataDimName1, std::string dataDimName2)
{
    activeDimensionIndices[0] = dimensionIndices[dataDimName0];
    activeDimensionIndices[1] = dimensionIndices[dataDimName1];
    activeDimensionIndices[2] = dimensionIndices[dataDimName2];
    syncDimsWithGPU();
}

const char *DataRepresentation::getDefaultVertShaderSource()
{
    return
#include "shaders/data/rainbow.vert"
        ;
}

const char *DataRepresentation::getDefaultFragShaderSource() {
    return
#include "shaders/data/rainbow.frag"
        ;
}

const Shader &DataRepresentation::getShader() const {
    return shader;
}

const int *DataRepresentation::getActiveDimensionIndices() const
{
    return activeDimensionIndices;
}

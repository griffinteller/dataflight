//
// Created by griff on 6/27/2021.
//

#include <glad/glad.h>
#include "DataRepresentation.h"

DataRepresentation::DataRepresentation(std::vector<float> &inData)
: data (std::move(inData)), VAO (0), vertexVBO (0)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vertexVBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

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

const std::vector<float> &DataRepresentation::getVector()
{
    return data;
}

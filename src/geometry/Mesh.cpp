//
// Created by griffinteller on 7/25/21.
//

#include "Mesh.h"

#include <utility>
#include <stddeps.h>
#include <stdexcept>

Mesh::Mesh(std::vector<float> inVertices, std::vector<uint> inIndices)
: vertices(std::move(inVertices)), indices(std::move(inIndices))
{
    if (vertices.size() % 3 != 0 || indices.size() % 3 != 0)
    {
        throw std::invalid_argument("Vertex and index component list must be a multiple of 3 in length!");
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);  // to prevent accidentally unibinding ebo first
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &EBO);
}

uint Mesh::getVAO() const
{
    return VAO;
}

void Mesh::transform(const mat4 &transformation)
{
    for (int i = 0; i < vertices.size() / 3; i++)
    {
        vec4 homogeneousVertex = vec4(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2], 1);
        vec3 newVertex = transformation * homogeneousVertex;
        vertices[i * 3] = newVertex.x;
        vertices[i * 3 + 1] = newVertex.y;
        vertices[i * 3 + 2] = newVertex.z;
    }
}

//
// Created by griffinteller on 7/25/21.
//

#ifndef DATAVISUALIZATION_MESH_H
#define DATAVISUALIZATION_MESH_H


#include <vector>
#include <typedefs.h>

class Mesh
{
    // TODO: add support for uvs and normals

private:
    std::vector<float> vertices;
    std::vector<uint> indices;
    uint VAO;
    uint vertexVBO;
    uint EBO;

public:
    Mesh(std::vector<float> inVertices, std::vector<uint> inIndices);

    void transform(const mat4 &transformation);

    uint getVAO() const;

    ~Mesh();
};


#endif //DATAVISUALIZATION_MESH_H

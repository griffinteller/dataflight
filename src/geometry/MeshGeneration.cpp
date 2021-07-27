//
// Created by griffinteller on 7/25/21.
//

#include "MeshGeneration.h"

#define PI 3.141592653589793238

namespace MeshGeneration
{
    Mesh prism(float length, float radius, int verticesPerBase)
    {
        // generates prism with triangle fan base along x axis

        const float radsPerVert = 2 * PI / verticesPerBase;

        std::vector<float> vertices (verticesPerBase * 2 * 3);

        // 3 floats per triangle, verticesPerBase * 2 triangles on the sides, verticesPerBase - 2 triangles per base
        std::vector<uint> indices (3 * (verticesPerBase * 2 + (verticesPerBase - 2) * 2));

        // generate bases
        for (int i = 0; i < verticesPerBase; i++)
        {
            vec3 vertex1 (-length / 2, glm::sin(radsPerVert * i), glm::cos(radsPerVert * i));
            vec3 vertex2 = vertex1 + vec3(length, 0, 0);

            // base 1
            vertices[i * 3] = vertex1.x;
            vertices[i * 3 + 1] = vertex1.y;
            vertices[i * 3 + 2] = vertex1.z;

            // base 2
            vertices[3 * verticesPerBase + i * 3] = vertex1.x;
            vertices[3 * verticesPerBase + i * 3 + 1] = vertex1.y;
            vertices[3 * verticesPerBase + i * 3 + 2] = vertex1.z;
        }

        // generate base triangles
        for (int tri = 0; tri < verticesPerBase - 2; tri++)
        {
            // base 1
            indices[tri * 3] = 0;  // this isn't a typo, we're doing a triangle fan, so it always starts at 0
            indices[tri * 3 + 1] = tri + 1;
            indices[tri * 3 + 2] = tri + 2;

            // base 2
            indices[(verticesPerBase - 2) * 3 + tri * 3] = verticesPerBase;
            indices[(verticesPerBase - 2) * 3 + tri * 3] = verticesPerBase + tri + 2;  // winding order is important
            indices[(verticesPerBase - 2) * 3 + tri * 3] = verticesPerBase + tri + 1;
        }

        // generate lateral triangles
        int start = (verticesPerBase - 2) * 3 * 2;
        for (int side = 0; side < verticesPerBase; side++)
        {
            indices[start + side * 3 * 2] = side;
            indices[start + side * 3 * 2 + 1] = side + verticesPerBase;
            indices[start + side * 3 * 2 + 2] = side + 1;

            indices[start + side * 3 * 2 + 3] = side + 1;
            indices[start + side * 3 * 2 + 4] = side + verticesPerBase;
            indices[start + side * 3 * 2 + 5] = side + verticesPerBase + 1;
        }

        return Mesh(std::move(vertices), std::move(indices));
    }
}

//
// Created by griff on 6/28/2021.
//

#include <random>
#include "DataGen.h"

DataRepresentation DataGen::cube(float width, int pointsPerSide) // points per side must be >= 2
{
    std::vector<float> data (3 * pointsPerSide * pointsPerSide * pointsPerSide);

    vec3 startCorner (-width / 2, -width / 2, -width / 2);
    float step = width / (float) (pointsPerSide - 1);

    for (int xi = 0; xi < pointsPerSide; xi++)
        for (int yi = 0; yi < pointsPerSide; yi++)
            for (int zi = 0; zi < pointsPerSide; zi++)
            {
                int vertIndex = 3 * (xi * pointsPerSide * pointsPerSide + yi * pointsPerSide + zi);
                data[vertIndex] = startCorner.x + step * (float) xi;
                data[vertIndex + 1] = startCorner.y + step * (float) yi;
                data[vertIndex + 2] = startCorner.z + step * (float) zi;
            }

    return DataRepresentation(data);
}

DataRepresentation DataGen::gaussian(float stddev, int points, int seed)
{
    std::vector<float> data (3 * points);

    std::default_random_engine gen (seed);
    std::normal_distribution<float> dist (0.0, stddev);

    for (int i = 0; i < points; i++)
    {
        data[3 * i] = dist(gen);
        data[3 * i + 1] = dist(gen);
        data[3 * i + 2] = dist(gen);
    }

    return DataRepresentation(data);
}

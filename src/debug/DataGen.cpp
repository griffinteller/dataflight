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

DataRepresentation DataGen::gaussian(vec3 mean, float stddev, int points, int seed)
{
    std::vector<float> data (3 * points);

    std::default_random_engine gen (seed);
    std::normal_distribution<float> dist (0.0, stddev);

    for (int i = 0; i < points; i++)
    {
        data[3 * i] = mean.x + dist(gen);
        data[3 * i + 1] = mean.y + dist(gen);
        data[3 * i + 2] = mean.z + dist(gen);
    }

    return DataRepresentation(data);
}

DataRepresentation
DataGen::bigaussian(vec3 mean1, vec3 mean2, float stddev1, float stddev2, int points1, int points2, int seed)
{
    std::vector<float> data (3 * points1 + 3 * points2);

    std::default_random_engine gen (seed);
    std::normal_distribution<float> dist1 (0.0, stddev1);
    std::normal_distribution<float> dist2 (0.0, stddev2);

    for (int i = 0; i < points1; i++)
    {
        data[3 * i] = mean1.x + dist1(gen);
        data[3 * i + 1] = mean1.y + dist1(gen);
        data[3 * i + 2] = mean1.z + dist1(gen);
    }

    for (int i = points1; i < points1 + points2; i++)
    {
        data[3 * i] = mean2.x + dist2(gen);
        data[3 * i + 1] = mean2.y + dist2(gen);
        data[3 * i + 2] = mean2.z + dist2(gen);
    }

    return DataRepresentation(data);
}

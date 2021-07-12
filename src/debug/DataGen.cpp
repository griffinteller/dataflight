//
// Created by griff on 6/28/2021.
//

#include <random>
#include <iostream>
#include "DataGen.h"

#define XYZ_DIM_NAMES std::vector<std::string> {"x", "y", "z"}

DataRepresentation DataGen::cube(float width, int pointsPerSide) // points per side must be >= 2
{
    std::vector<float> data (3 * pointsPerSide * pointsPerSide * pointsPerSide);

    int totalPoints = pointsPerSide * pointsPerSide * pointsPerSide;

    vec3 startCorner (-width / 2, -width / 2, -width / 2);
    float step = width / (float) (pointsPerSide - 1);

    for (int xi = 0; xi < pointsPerSide; xi++)
        for (int yi = 0; yi < pointsPerSide; yi++)
            for (int zi = 0; zi < pointsPerSide; zi++)
            {
                int vertIndex = (xi * pointsPerSide * pointsPerSide + yi * pointsPerSide + zi);
                data[vertIndex] = startCorner.x + step * (float) xi;
                data[vertIndex + totalPoints] = startCorner.y + step * (float) yi;
                data[vertIndex + totalPoints * 2] = startCorner.z + step * (float) zi;
            }

    return DataRepresentation(data, XYZ_DIM_NAMES);
}

DataRepresentation DataGen::gaussian(vec3 mean, float stddev, int points, int seed)
{
    std::vector<float> data (3 * points);

    std::default_random_engine gen (seed);
    std::normal_distribution<float> dist (0.0, stddev);

    int i = 0;
    for (; i < points; i++)
    {
        data[i] = mean.x + dist(gen);
    }

    for (; i < points * 2; i++)
    {
        data[i] = mean.y + dist(gen);
    }

    for (; i < points * 3; i++)
    {
        data[i] = mean.z + dist(gen);
    }

    return DataRepresentation(data, XYZ_DIM_NAMES);
}

DataRepresentation DataGen::bigaussian(vec3 mean1, vec3 mean2, float stddev1, float stddev2, int points1, int points2, int seed)
{
    std::vector<float> data (3 * points1 + 3 * points2);

    std::default_random_engine gen (seed);
    std::normal_distribution<float> dist1 (0.0, stddev1);
    std::normal_distribution<float> dist2 (0.0, stddev2);

    int i = 0;

    for (; i < points1; i++)
    {
        data[i] = mean1.x + dist1(gen);
    }

    for (; i < points1 * 2; i++)
    {
        data[i] = mean1.y + dist1(gen);
    }

    for (; i < points1 * 3; i++)
    {
        data[i] = mean1.z + dist1(gen);
    }

    for (; i < points1 * 3 + points2; i++)
    {
        data[i] = mean2.x + dist2(gen);
    }

    for (; i < points1 * 3 + points2 * 2; i++)
    {
        data[i] = mean2.y + dist2(gen);
    }

    for (; i < points1 * 3 + points2 * 3; i++)
    {
        data[i] = mean2.z + dist2(gen);
    }

    auto dims = XYZ_DIM_NAMES;
    std::cout << dims.size() << std::endl;

    return DataRepresentation(data, std::move(dims));
}

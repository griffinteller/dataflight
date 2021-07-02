//
// Created by griff on 6/28/2021.
//

#ifndef DATAVISUALIZATION_DATAGEN_H
#define DATAVISUALIZATION_DATAGEN_H

#include <data/DataRepresentation.h>

namespace DataGen
{
    DataRepresentation cube(float width, int pointsPerSide); // points per side must be >= 2
    DataRepresentation gaussian(vec3 mean, float stddev, int points, int seed);
    DataRepresentation bigaussian(vec3 mean1, vec3 mean2, float stddev1, float stddev2, int points1, int points2, int seed);
}

#endif //DATAVISUALIZATION_DATAGEN_H

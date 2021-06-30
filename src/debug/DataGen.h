//
// Created by griff on 6/28/2021.
//

#ifndef DATAVISUALIZATION_DATAGEN_H
#define DATAVISUALIZATION_DATAGEN_H

#include <data/DataRepresentation.h>

namespace DataGen
{
    DataRepresentation cube(float width, int pointsPerSide); // points per side must be >= 2
    DataRepresentation gaussian(float stddev, int points, int seed);
}

#endif //DATAVISUALIZATION_DATAGEN_H

//
// Created by griff on 7/8/2021.
//

#include "HashID.h"

size_t HashID::nextID = 0;

HashID::HashID()
{
    id = nextID;
    nextID++;
}

size_t HashID::getID() const
{
    return id;
}

bool HashID::operator==(const HashID &other) const
{
    return other.id == id;
}

size_t IDHashFunc::operator()(const HashID &other) const
{
    return other.getID();
}

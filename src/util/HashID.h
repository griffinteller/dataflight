//
// Created by griff on 7/8/2021.
//

#ifndef DATAVISUALIZATION_HASHID_H
#define DATAVISUALIZATION_HASHID_H


#include <cstddef>

class HashID
{
private:
    size_t id;
    static size_t nextID;

public:
    HashID();

    size_t getID() const;
    virtual bool operator==(const HashID &other) const;
};

struct IDHashFunc
{
    size_t operator() (const HashID &other) const;
};


#endif //DATAVISUALIZATION_HASHID_H

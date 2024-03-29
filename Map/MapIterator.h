#pragma once
#include "Map.h"

class MapIterator
{
    // DO NOT CHANGE THIS PART
    friend class Map;

private:
    const Map &map;
    Node *curr;
    // TODO - Representation

    MapIterator(const Map &m);

public:
    void first();
    void next();
    TElem getCurrent();
    bool valid() const;
};

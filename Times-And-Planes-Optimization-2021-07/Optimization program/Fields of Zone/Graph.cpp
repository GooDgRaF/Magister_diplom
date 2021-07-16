//
// Created by Антон on 16.07.2021.
//

#include "Fields of Flow.h"
#include "Graph.h"

int Vertex::genID()
{
    id += 1;
    return id;
}
int Vertex::id = -1;
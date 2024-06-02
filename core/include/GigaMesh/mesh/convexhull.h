//
// Created by timo.homburg on 19.05.2024.
//

#ifndef GIGAMESH_CONVEXHULL_H
#define GIGAMESH_CONVEXHULL_H
#include <iostream>
#include <stack>
#include <cstdlib>
#include <list>
#include "vertex.h"

using namespace std;

class convexhull {
    std::list<Vertex> calculateConvexHull2D();
};


#endif //GIGAMESH_CONVEXHULL_H

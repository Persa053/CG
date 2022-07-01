//
// Created by persa53 on 03/04/22.
//

#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include <string>
#include <vector>

#include "Ponto.h"

using namespace std;

class Shape {
private:
    vector<Ponto> points;
public:
    Shape( vector<Ponto> points) {
        this->points = points;
    };

    vector<Ponto> getPoints() {return this->points;};
};

#endif //ENGINE_SHAPE_H

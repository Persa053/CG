//
// Created by persa53 on 16/03/22.
//

#ifndef ENGINE_ROTATE_H
#define ENGINE_ROTATE_H


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using  namespace std;

class Rotate{
private:
    float angle;
    float x;
    float y;
    float z;

public:
    Rotate();
    Rotate (float angle, float x, float y, float z);
    float getAngle();
    float getX();
    float getY();
    float getZ();
    void setAngle(float a);
    void setX(float a);
    void setY(float a);
    void setZ(float a);

    void add(Rotate r);
};


#endif //ENGINE_ROTATE_H

//
// Created by persa53 on 16/03/22.
//

#ifndef ENGINE_SCALE_H
#define ENGINE_SCALE_H


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using  namespace std;

class Scale{
private:
    float x;
    float y;
    float z;

public:
    Scale();
    Scale (float x, float y, float z);
    float getX();
    float getY();
    float getZ();
    void setX(float a);
    void setY(float b);
    void setZ(float c);

    void add(Scale s);
};



#endif //ENGINE_SCALE_H

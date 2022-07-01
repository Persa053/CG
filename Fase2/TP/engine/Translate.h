//
// Created by persa53 on 16/03/22.
//

#ifndef ENGINE_TRANSLATE_H
#define ENGINE_TRANSLATE_H




#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using  namespace std;

class Translate{
private:
    float x;
    float y;
    float z;

public:
    Translate();
    Translate (float x, float y, float z);
    float getX();
    float getY();
    float getZ();
    void setX(float a);
    void setY(float a);
    void setZ(float a);

    void add(Translate t);
};

#endif //ENGINE_TRANSLATE_H

//
// Created by persa53 on 07/03/22.
//
#ifndef Engine_Ponto_H
#define Engine_Ponto_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>

using  namespace std;

class Ponto{
private:
    float x;
    float y;
    float z;

public:
    Ponto (float x, float y, float z);
    Ponto (string linha);
    float getX();
    float getY();
    float getZ();
};

#endif //Engine_Ponto_H

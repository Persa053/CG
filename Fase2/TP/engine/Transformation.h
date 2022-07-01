//
// Created by persa53 on 16/03/22.
//

#ifndef ENGINE_TRANSFORMATION_H
#define ENGINE_TRANSFORMATION_H


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Rotate.h"
#include "Scale.h"
#include "Translate.h"

using  namespace std;

class Transformation{
private:
    Rotate rt;
    Scale sc;
    Translate tr;


public:
    Transformation();
    Rotate getRotate();
    Scale getScale();
    Translate getTranslate();

    void setTranslate(Translate tr);

    void setRotate(Rotate rt);

    void setScale(Scale sc);

};


#endif //ENGINE_TRANSFORMATION_H

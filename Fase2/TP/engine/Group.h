//
// Created by persa53 on 16/03/22.
//

#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Transformation.h"
#include "Shape.h"


class Group {
private:
    Transformation transformations;
    vector<Shape> pontos;
    vector<Group> groups;

public:
    Group();
    void addTranslate(float x, float y, float z);
    void addRotate(float angle, float axisX, float axisY, float axisZ);
    void addScale(float x, float y, float z);
    Transformation getTransformations();
    void addShape(Shape shape);
    vector<Shape> getShape();
    void addGroup(Group group);
    vector<Group> getGroups();
};

#endif //ENGINE_GROUP_H

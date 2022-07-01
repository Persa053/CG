//
// Created by persa53 on 16/03/22.
//

#include "Group.h"
#include "Shape.h"

using namespace std;

// * Group * //

Group::Group() {
    this->transformations = Transformation();
    this->pontos = {};
    this->groups = {};
}

void Group::addTranslate(float x, float y, float z) {
    Translate tr = Translate(x,y,z);
    this->transformations.setTranslate(tr);
}

void Group::addRotate(float angle, float axisX, float axisY, float axisZ) {
    Rotate rt = Rotate(angle,axisX,axisY,axisZ);
    this->transformations.setRotate(rt);
}

void Group::addScale(float x, float y, float z) {
    Scale sc = Scale(x,y,z);
    this->transformations.setScale(sc);
}

Transformation Group::getTransformations() {
    return this->transformations;
}

void Group::addShape(Shape shape) {
    this->pontos.push_back(shape);
}

vector<Shape> Group::getShape() {
    return this->pontos;
}

void Group::addGroup(Group group) {
    this->groups.push_back(group);
}

vector<Group> Group::getGroups() {
    return this->groups;
}
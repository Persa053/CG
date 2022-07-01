//
// Created by persa53 on 16/03/22.
//

#include "Group.h"
#include <sstream>


using namespace std;

// * Group * //

Group::Group() {
    this->transformations = {};
    this->pontos = {};
    this->groups = {};
}

void Group::addTranslate(float x, float y, float z) {
    Translate* tr = new Translate(x, y, z);
    this->transformations.push_back(tr);
}

void Group::addRotate(float angle, float axisX, float axisY, float axisZ) {
    Rotate* rt = new Rotate(angle,axisX,axisY,axisZ);
    this->transformations.push_back(rt);
}

void Group::addScale(float x, float y, float z) {
    Scale* sc = new Scale(x,y,z);
    this->transformations.push_back(sc);
}

vector<Transformation*> Group::getTransformations() {
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

void Group::addDynamicTR(float time, bool align, vector<Ponto> points) {
    DynamicTranslate* dtr = new DynamicTranslate(time, align, points);
    this->transformations.push_back(dtr);
}

void Group::addDynamicRT(float time, float axisX, float axisY, float axisZ) {
    DynamicRotate* drt = new DynamicRotate(time, axisX, axisY, axisZ);
    this->transformations.push_back(drt);
}
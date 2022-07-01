//
// Created by persa53 on 16/03/22.
//

#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H


#include <string>
#include <vector>
#include <cmath>
#include "Ponto.h"
#include "Matrix.h"
#include "Shape.h"

#define CATMULL_TESSELATION 0.01

using namespace std;

class Transformation {
public:
    virtual void smt(){};
};

class Translate : public Transformation {
private:
    float x, y, z;
public:
    float getX() {return this->x;};
    float getY() {return this->y;};
    float getZ() {return this->z;};
    Translate();
    Translate(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };
};

class DynamicTranslate : public Transformation {
private:
    float total_time;  // time to run the whole curve
    float segment_time;  // time to run each segment
    float timebase;  // last time measured
    float elapsed_time;  // time elapsed since beginning of the curve
    bool align;
    vector<Ponto> points;
    vector<Ponto> render_points;

    void generateRenderPoints();
public:
    void applyTransformation();
    void renderCatmullRomCurve();

    DynamicTranslate();
    DynamicTranslate(float total_time, bool align, vector<Ponto> points);
};

class Rotate : public Transformation {
private:
    float angle, axisX, axisY, axisZ;
public:
    float getAngle() {return this->angle;};
    float getAxisX() {return this->axisX;};
    float getAxisY() {return this->axisY;};
    float getAxisZ() {return this->axisZ;};
    Rotate();
    Rotate(float angle, float axisX, float axisY, float axisZ) {
        this->angle = angle;
        this->axisX = axisX;
        this->axisY = axisY;
        this->axisZ = axisZ;
    };
};

class DynamicRotate : public Transformation {
private:
    float total_time;  // time to perform 360 degrees rotation
    float timebase;  // time at the start of the rotation
    float axisX, axisY, axisZ;  // axis of rotation
public:
    void applyTransformation();

    DynamicRotate();
    DynamicRotate(float total_time, float axisX, float axisY, float axisZ);
};

class Scale : public Transformation {
private:
    float x, y, z;
public:
    float getX() {return this->x;};
    float getY() {return this->y;};
    float getZ() {return this->z;};
    Scale();
    Scale(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };
};


class Group {
private:
    vector<Transformation*> transformations;
    vector<Shape> pontos;
    vector<Group> groups;

public:
    Group();
    void addTranslate(float x, float y, float z);
    void addRotate(float angle, float axisX, float axisY, float axisZ);
    void addScale(float x, float y, float z);
    vector<Transformation*> getTransformations();
    void addShape(Shape shape);
    vector<Shape> getShape();
    void addGroup(Group group);
    vector<Group> getGroups();
    void addDynamicTR(float time, bool align, vector<Ponto> points);
    void addDynamicRT(float time, float axisX, float axisY, float axisZ);
};

#endif //ENGINE_GROUP_H

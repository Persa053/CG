//
// Created by persa on 23-04-2022.
//

#include "Group.h"

DynamicRotate::DynamicRotate(float total_time, float axisX, float axisY, float axisZ) {
    this->total_time = total_time;
    this->timebase = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    this->axisX = axisX;
    this->axisY = axisY;
    this->axisZ = axisZ;
}

void DynamicRotate::applyTransformation() {
    // Get the time elapsed since the beginning of this full rotation
    float elapsed_time = fmod(glutGet(GLUT_ELAPSED_TIME)/1000.0 - timebase, total_time);

    // Get the current angle of the object
    float angle = 360 * elapsed_time / total_time;

    // Apply the rotation
    glRotatef(angle, axisX, axisY, axisZ);
}

DynamicRotate::DynamicRotate() {
    this->total_time = 0;
    this->timebase = 0;
    this->axisX = 0;
    this->axisY = 0;
    this->axisZ = 0;
}



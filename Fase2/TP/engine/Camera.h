//
// Created by persa53 on 07/03/22.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using namespace std;

class Camera {
    private:
    float Px;
    float Py;
    float Pz;
    float Lookx;
    float Looky;
    float Lookz;
    float upx;
    float upy;
    float upz;
    float fov;
    float near;
    float far;

    public:
    Camera();
    Camera(float Px, float Py, float Pz,
           float LookAtx, float LookAty, float LookAtz,
           float fov, float near, float far);
    void setPx(float x);
    void setPy(float x);
    void setPz(float x);
    void setLookx(float x);
    void setLooky(float x);
    void setLookz(float x);
    void setupx(float x);
    void setupy(float x);
    void setupz(float x);
    void setfov(float x);
    void setnear(float x);
    void setfar(float x);

    float getPx() const;

    float getPy() const;

    float getPz() const;

    float getLookx() const;

    float getLooky() const;

    float getLookz() const;

    float getUpx() const;

    float getUpy() const;

    float getUpz() const;

    float getFov() const;

    float getNear() const;

    float getFar() const;

};


#endif //ENGINE_CAMERA_H

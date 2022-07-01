//
// Created by persa53 on 16/03/22.
//

#include "Rotate.h"

Rotate::Rotate(float angle, float x, float y, float z){
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
}

Rotate::Rotate(){
    this->angle = 0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
}


float Rotate::getAngle(){
    return this->angle;
}

float Rotate::getX(){
    return this->x;
}

float Rotate::getY(){
    return this->y;
}

float Rotate::getZ(){
    return this->z;
}

void Rotate::setAngle(float a){
    this->angle = a;
}

void Rotate::setX(float x){
    this->x = x;
}

void Rotate::setY(float y){
    this->y = y;
}

void Rotate::setZ(float z){
    this->z = z;
}

void Rotate::add(Rotate r){
    this->angle = r.getAngle();
    this->x = r.getX();
    this->y = r.getY();
    this->z = r.getZ();
}
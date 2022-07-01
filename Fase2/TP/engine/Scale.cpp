//
// Created by persa53 on 16/03/22.
//

#include "Scale.h"

Scale::Scale(){
    this->x = 1;
    this->y = 1;
    this->z = 1;
}

Scale::Scale(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}


float Scale::getX(){
    return this->x;
}

float Scale::getY(){
    return this->y;
}

float Scale::getZ(){
    return this->z;
}

void Scale::setX(float x){
    this->x = x;
}

void Scale::setY(float y){
    this->y = y;
}

void Scale::setZ(float z){
    this->z = z;
}

void Scale::add(Scale s){
    this->x *= s.getX();
    this->y *= s.getY();
    this->z *= s.getZ();
}
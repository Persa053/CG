//
// Created by persa53 on 07/03/22.
//

#include "Camera.h"

Camera::Camera(){
    this->Px = 0;
    this->Py = 0;
    this->Pz = 0;
    this->Lookx = 0;
    this->Looky = 0;
    this->Lookz = 0;
    this->fov = 0;
    this->near = 0;
    this->far = 0;

}
Camera::Camera(float Px, float Py, float Pz,
             float LookAtx, float LookAty, float LookAtz,
             float fov, float near, float far){

    this->Px = Px;
    this->Py = Py;
    this->Pz = Pz;
    this->Lookx = LookAtx;
    this->Looky = LookAty;
    this->Lookz = LookAtz;
    this->fov = fov;
    this->near = near;
    this->far = far;

}

void Camera:: setPx(float x){
    this->Px=x;
}

void Camera:: setPy(float x){
    this->Py=x;
}
void Camera:: setPz(float x){
    this->Pz=x;
}
void Camera:: setLookx(float x){
    this->Lookx=x;
}
void Camera:: setLooky(float x){
    this->Looky=x;
}
void Camera:: setLookz(float x){
    this->Lookz=x;
}
void Camera:: setupx(float x){
    this->upx=x;
}

void Camera:: setupy(float x){
    this->upy=x;
}
void Camera:: setupz(float x){
    this->upz=x;
}
void Camera:: setfov(float x){
    this->fov=x;
}
void Camera:: setnear(float x){
    this->near=x;
}

void Camera:: setfar(float x){
    this->far=x;
}

float Camera::getPx() const {
    return Px;
}

float Camera::getPy() const {
    return Py;
}

float Camera::getPz() const {
    return Pz;
}

float Camera::getLookx() const {
    return Lookx;
}

float Camera::getLooky() const {
    return Looky;
}

float Camera::getLookz() const {
    return Lookz;
}

float Camera::getUpx() const {
    return upx;
}

float Camera::getUpy() const {
    return upy;
}

float Camera::getUpz() const {
    return upz;
}

float Camera::getFov() const {
    return fov;
}

float Camera::getNear() const {
    return near;
}

float Camera::getFar() const {
    return far;
}

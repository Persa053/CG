//
// Created by persa53 on 07/03/22.
//
#include <valarray>
#include "Ponto.h"



Ponto::Ponto(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Ponto::Ponto(string line){

    char *linha,*token;

    linha = const_cast<char *>(line.c_str());
    token = strtok(linha, ",");
    this->x =atof(token);
    token = strtok(NULL, ",");
    this->y=atof(token);
    token = strtok(NULL, ",");
    this->z=atof(token);
}

float Ponto::getX(){
    return this->x;
}

float Ponto::getY(){
    return this->y;
}

float Ponto::getZ(){
    return this->z;
}





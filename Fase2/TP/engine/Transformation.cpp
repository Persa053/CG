//
// Created by persa53 on 16/03/22.
//

#include "Transformation.h"

#include "Rotate.h"

Transformation::Transformation(){
    this->rt = Rotate();
    this->sc = Scale();
    this->tr = Translate();
}

Rotate Transformation::getRotate(){
    return rt;
}

Scale Transformation::getScale(){
    return sc;
}

Translate Transformation::getTranslate(){
    return tr;
}

void Transformation::setTranslate(Translate tr){
    this->tr.add(tr);
}

void Transformation::setRotate(Rotate rt){
    this->rt.add(rt);
}

void Transformation::setScale(Scale sc){
    this->sc.add(sc);
}
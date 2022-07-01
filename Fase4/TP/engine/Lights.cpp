#include "Lights.h"
float dark[4] = {0.2, 0.2, 0.2, 1.0};
float white[4] = {1.0, 1.0, 1.0, 1.0};
float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
void LightPoint::apply() {

    int index = this->getIndex();

    glLightfv(GL_LIGHT0+index, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0+index, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0+index, GL_SPECULAR, white);

    // Set point light properties
    GLfloat pos[4] = {this->pos->getX(), this->pos->getY(), this->pos->getZ(), 1.0};
    glLightfv(GL_LIGHT0+index, GL_POSITION, pos);
}

void LightDirectional::apply() {

    int index = this->getIndex();

    glLightfv(GL_LIGHT0+index, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0+index, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0+index, GL_SPECULAR, white);

    // Set directional light properties
    GLfloat dir[4] = {this->dir->getX(), this->dir->getY(), this->dir->getZ(), 0.0};
    glLightfv(GL_LIGHT0+index, GL_POSITION, dir);
}

void LightSpot::apply() {

    int index = this->getIndex();


    glLightfv(GL_LIGHT0+index, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0+index, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0+index, GL_SPECULAR, white);

    // Set spot light properties
    GLfloat pos[4] = {this->pos->getX(), this->pos->getY(), this->pos->getZ(), 1.0};
    glLightfv(GL_LIGHT0+index, GL_POSITION, pos);

    GLfloat dir[3] = {this->dir->getX(), this->dir->getY(), this->dir->getZ()};
    glLightfv(GL_LIGHT0+index, GL_SPOT_DIRECTION, dir);

    glLightfv(GL_LIGHT0+index, GL_SPOT_CUTOFF, &this->cutoff);

}
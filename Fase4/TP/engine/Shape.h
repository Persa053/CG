//
// Created by persa53 on 03/04/22.
//

#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include <string>
#include <GL/glut.h>
#include <IL/il.h>

using namespace std;

class Shape {
public:
    GLuint p_vbo_ind;
    GLuint n_vbo_ind;
    GLuint t_vbo_ind;
    GLuint texture_id;

    GLsizei vertice_count;
    GLfloat ambient[4];
    GLfloat specular[4];
    GLfloat diffuse[4];
    GLfloat emissive[4];
    GLfloat shininess;
public:
    Shape() {
        this->p_vbo_ind = 0;
        this->n_vbo_ind = 0;
        this->t_vbo_ind = 0;
        this->texture_id = 0;
        this->vertice_count = 0;
    };
    Shape(GLuint p_vbo_ind, GLuint n_vbo_ind, GLuint t_vbo_ind, GLsizei vertice_count) {
        this->p_vbo_ind = p_vbo_ind;
        this->n_vbo_ind = n_vbo_ind;
        this->t_vbo_ind = t_vbo_ind;
        this->vertice_count = vertice_count;
    };

    void setTextureID(GLuint id) {this->texture_id = texture_id;};

    void setAmbient(GLfloat* ambient) {
        this->ambient[0] = ambient[0]/255;
        this->ambient[1] = ambient[1]/255;
        this->ambient[2] = ambient[2]/255;
        this->ambient[3] = ambient[3];
    };

    void setSpecular(GLfloat* ambient) {
        this->specular[0] = ambient[0]/255;
        this->specular[1] = ambient[1]/255;
        this->specular[2] = ambient[2]/255;
        this->specular[3] = ambient[3];
    };

    void setDiffuse(GLfloat* ambient) {
        this->diffuse[0] = ambient[0]/255;
        this->diffuse[1] = ambient[1]/255;
        this->diffuse[2] = ambient[2]/255;
        this->diffuse[3] = ambient[3];
    };

    void setEmissive(GLfloat* ambient) {
        this->emissive[0] = ambient[0]/255;
        this->emissive[1] = ambient[1]/255;
        this->emissive[2] = ambient[2]/255;
        this->emissive[3] = ambient[3];
    };


    void setShininess(GLfloat shininess) {this->shininess = shininess;};

    GLuint getPVBOInd() {return this->p_vbo_ind;};
    GLuint getNVBOInd() {return this->n_vbo_ind;};
    GLuint getTVBOInd() {return this->t_vbo_ind;};
    GLsizei getVerticeCount() {return this->vertice_count;};

    GLuint getTextureID() {return this->texture_id;};

    GLfloat* getAmbient() {return this->ambient;};
    GLfloat* getSpecular() {return this->specular;};
    GLfloat* getDiffuse() {return this->diffuse;};
    GLfloat* getEmissive() {return this->emissive;};
    GLfloat getShininess() {return this->shininess;};

    void loadTexture(string texture_file);
};


#endif //ENGINE_SHAPE_H

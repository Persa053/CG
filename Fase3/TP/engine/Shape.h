//
// Created by persa53 on 03/04/22.
//

#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include <GL/glut.h>

using namespace std;

class Shape {
    private:
        GLuint vbo_ind;
        GLsizei vertice_count;
    public:
        Shape() {
            this->vbo_ind = 0;
            this->vertice_count = 0;
        };
        Shape(GLuint vbo_ind, GLsizei vertice_count) {
            this->vbo_ind = vbo_ind;
            this->vertice_count = vertice_count;
        };

        GLuint getVBOInd() {return this->vbo_ind;};
        GLsizei getVerticeCount() {return this->vertice_count;};
};

#endif //ENGINE_SHAPE_H

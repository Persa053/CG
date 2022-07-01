//
// Created by persa53 on 07/03/22.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <string>
#include "tinyxml2.h"
#include "Ponto.h"
#include "Camera.h"


using namespace tinyxml2;
using namespace std;



float alpha = 0.61547999;
float bet = 0.61547999;
float rad = 4;

Camera* cam = new Camera();
vector <Ponto> shape;

void readFile(string fich) {
    ifstream file;
    file.open(fich.c_str());
    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            Ponto p = Ponto(line);
            shape.push_back(p);
        }
        file.close();
    }
    else {
        printf("NAO ABRIU O FICHEIRO\n");
    }
}

void lerXML(string ficheiro) {
    XMLDocument docxml;

    if (!(docxml.LoadFile(ficheiro.c_str()))) {
        XMLElement *root = docxml.FirstChildElement();
        XMLElement *camera = root->FirstChildElement();
        for (XMLElement *elem = camera->FirstChildElement(); elem; elem = elem->NextSiblingElement()) {
            if (strcmp(elem->Name(), "position") == 0) {
                if (elem->Attribute("x"))
                    cam->setPx(stof(elem->Attribute("x")));
                if (elem->Attribute("y"))
                    cam->setPy(stof(elem->Attribute("y")));
                if (elem->Attribute("z"))
                    cam->setPz(stof(elem->Attribute("z")));
            } else if (strcmp(elem->Name(), "lookAt") == 0) {
                if (elem->Attribute("x"))
                    cam->setLookx(stof(elem->Attribute("x")));
                if (elem->Attribute("y"))
                    cam->setLooky(stof(elem->Attribute("y")));
                if (elem->Attribute("z"))
                    cam->setLookz(stof(elem->Attribute("z")));
            } else if (strcmp(elem->Name(), "up") == 0) {
                if (elem->Attribute("x"))
                    cam->setupx(stof(elem->Attribute("z")));
                if (elem->Attribute("y"))
                    cam->setupy(stof(elem->Attribute("y")));
                if (elem->Attribute("z"))
                    cam->setupz(stof(elem->Attribute("z")));
            } else if (strcmp(elem->Name(), "projection") == 0) {
                if (elem->Attribute("fov"))
                    cam->setfov(stof(elem->Attribute("fov")));
                if (elem->Attribute("near"))
                    cam->setnear(stof(elem->Attribute("near")));
                if (elem->Attribute("far"))
                    cam->setfar(stof(elem->Attribute("far")));
            }
        }
        XMLElement *group = camera->NextSiblingElement();
        XMLElement *models = group->FirstChildElement();
        for (XMLElement *model = models->FirstChildElement(); model; model = model->NextSiblingElement()) {
            string fich = model->Attribute("file");
            cout << "Ficheiro: " << fich << " lido com sucesso " << endl;
            readFile(fich);
        }
    } else {
        cout << "Ficheiro XML não foi encontrado" << endl;
    }
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(cam->getFov(), ratio, cam->getNear(), cam->getFar());

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    //cam->getPx(),cam->getPy() , cam->getPz(),
    gluLookAt(rad*cos(bet)*sin(alpha),rad*sin(bet) , rad*cos(bet)*cos(alpha),
              cam->getLookx(), cam->getLooky(), cam->getLookz(),
              cam->getUpx(), cam->getUpy(), cam->getUpz());

    glPolygonMode(GL_FRONT,GL_LINE);

    glBegin(GL_LINE);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();


    for(int j = 0; j < shape.size(); j += 3){
        glBegin(GL_TRIANGLES);
        //glColor3f(sin(j)*cos(j*M_PI),sin(j),1/cos(j));
        glColor3f(1,1,1);
        glVertex3f(shape[j].getX(),shape[j].getY(),shape[j].getZ());
        glVertex3f(shape[j+1].getX(),shape[j+1].getY(),shape[j+1].getZ());
        glVertex3f(shape[j+2].getX(),shape[j+2].getY(),shape[j+2].getZ());
        glEnd();
    }
    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void keys(unsigned char c, int xx, int yy){
    switch (c) {

        case 'w':
            if(bet <= M_PI/2) {
                bet += M_PI / 64;
            }
            glutPostRedisplay();
            break;
        case 's':
            if(bet >= -M_PI/2){
                bet -= M_PI/64;
            }
            glutPostRedisplay();
            break;
        case 'a':
            alpha -= M_PI/64;
            glutPostRedisplay();
            break;
        case 'd':
            alpha += M_PI/64;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}



int main(int argc, char** argv) {
    if(argc < 2){
        return 0;
    }
    if(!strcmp(argv[1],"-h")){
        return 0;
    }
    char path[1024];
    strcpy(path, "../test_files_phase_1/");
    strcat(path, argv[1]);
    lerXML(path);
    rad = sqrt(pow(cam->getLookx() - cam->getPx(), 2) + pow(cam->getLooky() - cam->getPy(), 2) + pow(cam->getLookz() - cam->getPz(), 2));
    bet = atan2(cam->getPy(),cam->getPx());
    alpha = atan2(sqrt(cam->getPx()*cam->getPx()+cam->getPy()*cam->getPy()),cam->getPz());
    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI");
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc(keys);


    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
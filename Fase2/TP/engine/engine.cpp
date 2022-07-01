//
// Created by persa53 on 07/03/22.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "Ponto.h"
#include "Camera.h"
#include "Group.h"
#include "Shape.h"
#include <math.h>


using namespace tinyxml2;
using namespace std;




float alpha = 0.0f;
float bet = 0.5f;
float rad = 100.0f;

Camera* cam = new Camera();
vector <Group> groups;


//Parsers Camera
void parseCamera(XMLElement* elem, Camera* cam){
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
//Parser translação
void parseTranslate(XMLElement* elemento, Translate *translate){
    if(elemento->Attribute("x"))
        translate->setX(stof(elemento->Attribute("x")));
    if (elemento->Attribute("y"))
        translate->setY(stof(elemento->Attribute("y")));
    if (elemento->Attribute("z"))
        translate->setZ(stof(elemento->Attribute("z")));
}

//Parser Rotação
void parseRotate(XMLElement* elemento, Rotate *rotate){
    if(elemento->Attribute("x"))
        rotate->setX(stof(elemento->Attribute("x")));
    if (elemento->Attribute("y"))
        rotate->setY(stof(elemento->Attribute("y")));
    if (elemento->Attribute("z"))
        rotate->setZ(stof(elemento->Attribute("z")));
    if (elemento->Attribute("angle"))
        rotate->setAngle(stof(elemento->Attribute("angle")));
}


//Parser Escala
void parseScale(XMLElement* elemento, Scale *scale){
    if(elemento->Attribute("x"))
        scale->setX(stof(elemento->Attribute("x")));
    if (elemento->Attribute("y"))
        scale->setY(stof(elemento->Attribute("y")));
    if (elemento->Attribute("z"))
        scale->setZ(stof(elemento->Attribute("z")));
}

vector<Ponto> readFile(string fich) {
    ifstream file;
    string s = "../3d/" + fich;
    file.open(s.c_str());
    vector<Ponto> pontos;
    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            Ponto p = Ponto(line);
            pontos.push_back(p);
        }
        file.close();
    }
    else {
        printf("NAO ABRIU O FICHEIRO\n");
    }

    return pontos;

}




Group parseXMLGroupElement (XMLElement* main_element) {
    Group new_group = Group();
    XMLElement* transform = main_element->FirstChildElement("transform");
    // Trying to get translate element
    if(transform) {
        XMLElement* elem = transform->FirstChildElement();
        while (elem) {
            if (strcmp(elem->Name(), "translate") == 0) {
                // Get x attribute
                const XMLAttribute *x_attribute = elem->FindAttribute("x");
                float x_trans;
                x_attribute ? x_trans = atof(x_attribute->Value()) : x_trans = 0;

                // Get y attribute
                const XMLAttribute *y_attribute = elem->FindAttribute("y");
                float y_trans;
                y_attribute ? y_trans = atof(y_attribute->Value()) : y_trans = 0;

                // Get z attribute
                const XMLAttribute *z_attribute = elem->FindAttribute("z");
                float z_trans;
                z_attribute ? z_trans = atof(z_attribute->Value()) : z_trans = 0;

                new_group.addTranslate(x_trans, y_trans, z_trans);

                // Only used if we wanted to support multiple translates in a group
                // If so, needed to change the 'if' to a 'while' too
                //translate_element = translate_element->NextSiblingElement("translate");
            }

            // Trying to get rotate element
            if (strcmp(elem->Name(), "rotate") == 0) {
                // Get angle attribute
                const XMLAttribute *angle_attribute = elem->FindAttribute("angle");
                float angle_rot;
                angle_attribute ? angle_rot = atof(angle_attribute->Value()) : angle_rot = 0;

                // Get axisX attribute
                const XMLAttribute *axisX_attribute = elem->FindAttribute("x");
                float axisX_rot;
                axisX_attribute ? axisX_rot = atof(axisX_attribute->Value()) : axisX_rot = 0;

                // Get axisY attribute
                const XMLAttribute *axisY_attribute = elem->FindAttribute("y");
                float axisY_rot;
                axisY_attribute ? axisY_rot = atof(axisY_attribute->Value()) : axisY_rot = 0;

                // Get axisZ attribute
                const XMLAttribute *axisZ_attribute = elem->FindAttribute("z");
                float axisZ_rot;
                axisZ_attribute ? axisZ_rot = atof(axisZ_attribute->Value()) : axisZ_rot = 0;

                new_group.addRotate(angle_rot, axisX_rot, axisY_rot, axisZ_rot);

                // Only used if we wanted to support multiple rotates in a group
                // If so, needed to change the 'if' to a 'while' too
                //rotate_element = rotate_element->NextSiblingElement("rotate");
            }

            // Trying to get scale element
            if (strcmp(elem->Name(), "scale") == 0) {
                // Get x attribute
                const XMLAttribute *x_attribute = elem->FindAttribute("x");
                float x_scale;
                x_attribute ? x_scale = atof(x_attribute->Value()) : x_scale = 1;

                // Get y attribute
                const XMLAttribute *y_attribute = elem->FindAttribute("y");
                float y_scale;
                y_attribute ? y_scale = atof(y_attribute->Value()) : y_scale = 1;

                // Get z attribute
                const XMLAttribute *z_attribute = elem->FindAttribute("z");
                float z_scale;
                z_attribute ? z_scale = atof(z_attribute->Value()) : z_scale = 1;

                new_group.addScale(x_scale, y_scale, z_scale);

                // Only used if we wanted to support multiple scales in a group
                // If so, needed to change the 'if' to a 'while' too
                //scale_element = scale_element->NextSiblingElement("scale");
            }
            elem = elem->NextSiblingElement();
        }
    }
    // Trying to get models element
    XMLElement* models_element = main_element->FirstChildElement("models");
    if (models_element) {
        // Get all model elements
        XMLElement* model_element = models_element->FirstChildElement("model");
        while (model_element) {
            vector<Ponto> object_points;
            string object_description;

            // Parse model file attribute
            const XMLAttribute* file_attribute = model_element->FindAttribute("file");
            if (file_attribute) {
                string file = file_attribute->Value();
                object_points = readFile(file);
            }
            Shape new_shape = Shape( object_points);
            new_group.addShape(new_shape);

            model_element = model_element->NextSiblingElement("models");
        }
    }

    // Trying to get group elements
    XMLElement* group_element = main_element->FirstChildElement("group");
    while (group_element) {
        Group g = parseXMLGroupElement(group_element);
        new_group.addGroup(g);

        group_element = group_element->NextSiblingElement("group");
    }

    return new_group;
}


int lerXML(string xmlFileString) {
    XMLDocument doc;

    // Trying to open XML File
    XMLError load_result = doc.LoadFile(xmlFileString.c_str());
    if (load_result != XML_SUCCESS)  {
        std::cout << "Unable to load XML File!\n";
        return 0;
    }

    // Trying to get scene element
    XMLElement* root = doc.FirstChildElement("world");
    if (root == nullptr) {
        std::cout << "XML File has wrong sintax! -> scene element\n";
        return 0;
    }
    XMLElement *camera = root->FirstChildElement();
    for (XMLElement *elem = camera->FirstChildElement(); elem; elem = elem->NextSiblingElement())
        parseCamera(elem, cam);


    // Trying to get all group elements
    XMLElement* group_element = root->FirstChildElement("group");
    while (group_element) {
        Group g = parseXMLGroupElement(group_element);
        groups.push_back(g);

        group_element = group_element->NextSiblingElement("group");
    }

    return 1;
}


void drawAxis(void) {
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1000.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1000.0f);
    glEnd();
}

// Function to draw a single object, given its points
void drawObject(Shape shape) {
    vector<Ponto> points = shape.getPoints();

    for (int j = 0; j < points.size(); j+=3) {
        glBegin(GL_TRIANGLES);
        glVertex3f(points[j].getX(),points[j].getY(),points[j].getZ());
        glVertex3f(points[j+1].getX(),points[j+1].getY(),points[j+1].getZ());
        glVertex3f(points[j+2].getX(),points[j+2].getY(),points[j+2].getZ());
        glEnd();
    }
}

// Function to draw a single group
void drawGroup(Group g) {

    // Set the model view matrix as current, just for safety
    glMatrixMode(GL_MODELVIEW);

    // Push matrix on beggining
    glPushMatrix();

    // Trying to get transformations from group
    Transformation t = g.getTransformations();
    glRotatef(t.getRotate().getAngle(), t.getRotate().getX(),t.getRotate().getY(),t.getRotate().getZ());
    glTranslatef(t.getTranslate().getX(),t.getTranslate().getY(),t.getTranslate().getZ());
    glScalef(t.getScale().getX(),t.getScale().getY(),t.getScale().getZ());


    glColor3f(1.0f, 1.0f, 1.0f);

    // Drawing objects in this group
    vector<Shape> shapes = g.getShape();
    for (Shape shape : shapes) {
        drawObject(shape);
    }

    // Drawing groups in this group
    vector<Group> groups = g.getGroups();
    for (Group group : groups) {
        drawGroup(group);
    }

    // Popping matrix after drawing all objects in this group
    glPopMatrix();
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
    //cam->getPx(), cam->getPy(),cam->getPz(),
    gluLookAt(rad*cos(bet)*sin(alpha), rad*sin(bet), rad*cos(bet)*cos(alpha),
              cam->getLookx(), cam->getLooky(), cam->getLookz(),
              cam->getUpx(), cam->getUpy(), cam->getUpz());
    drawAxis();
    for (Group g : groups) {
        drawGroup(g);
    }
    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void specialKeys(int key, int xx, int yy) {

    switch (key) {

        case GLUT_KEY_RIGHT:
            alpha -= 0.1; break;

        case GLUT_KEY_LEFT:
            alpha += 0.1; break;

        case GLUT_KEY_UP:
            bet += 0.1f;
            if (bet > 1.5f)
                bet = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            bet -= 0.1f;
            if (bet < -1.5f)
                bet = -1.5f;
            break;

        case GLUT_KEY_PAGE_DOWN: rad -= 1.0f;
            if (rad < 1.0f)
                rad = 1.0f;
            break;

        case GLUT_KEY_PAGE_UP: rad += 1.0f; break;
    }
    glutPostRedisplay();

}



int main(int argc, char** argv) {
    if(argc < 2){
        return 0;
    }
    char path[1024];
    strcpy(path, "../test_files_phase_2/");
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
    glClearColor(0,0,0,0);glPolygonMode(GL_FRONT,GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT);

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // put here the registration of the keyboard callbacks
    glutSpecialFunc(specialKeys);



    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
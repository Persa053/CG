//
// Created by persa53 on 07/03/22.
//


#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "Ponto.h"
#include "Camera.h"
#include "Group.h"
#include "Shape.h"
#include <math.h>
#include <vector>


using namespace tinyxml2;
using namespace std;




float alpha = 0.0f;
float bet = 0.5f;
float rad = 100.0f;

Camera* cam = new Camera();
vector <Group> groups;


Shape load3dFile(string _3dFile) {
    string line;
    string delim = ", ";
    ifstream file;
    vector<float> points;

    file.open(_3dFile.c_str(), ios::in);

    if (file.is_open()) {
        while (getline(file, line)) {
            string token;
            istringstream tokenStream(line);

            while (getline(tokenStream, token, ',')) {
                points.push_back(atof(token.c_str()));
            }
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << _3dFile.c_str() << "\n";
    }

    GLuint vertice_count = (GLuint) (points.size() / 3);
    GLuint vbo_ind;

    glGenBuffers(1, &vbo_ind);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ind);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

    return Shape(vbo_ind, vertice_count);
}

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




Group parseXMLGroupElement (XMLElement* main_element) {
    Group new_group = Group();
    XMLElement* transform = main_element->FirstChildElement("transform");
    // Trying to get translate element
    if(transform) {
        XMLElement* elem = transform->FirstChildElement();
        while (elem) {

            if (strcmp(elem->Name(), "translate") == 0) {
                // Trying to get time attribute, so we know if it's a static or dynamic translation
                const XMLAttribute* time_attribute = elem->FindAttribute("time");
                if (time_attribute){
                    float time = atof(time_attribute->Value());
                    vector<Ponto> points = {};

                    const XMLAttribute* align_attribute = elem->FindAttribute("align");
                    string str = align_attribute->Value();
                    bool align = !str.compare("True");
                    vector<Ponto> temp_points;
                    XMLElement* point_element = elem->FirstChildElement("point");

                    while (point_element) {
                        float x_value = atof(point_element->FindAttribute("x")->Value());
                        float y_value = atof(point_element->FindAttribute("y")->Value());
                        float z_value = atof(point_element->FindAttribute("z")->Value());
                        temp_points.push_back( Ponto(x_value, y_value, z_value) );
                        point_element = point_element->NextSiblingElement("point");
                    }

                    // Duplicate some points so we get a closed curve
                    points.push_back(temp_points.back());
                    for (int i = 0; i < temp_points.size(); i++)
                        points.push_back(temp_points[i]);
                    points.push_back(temp_points[0]);
                    points.push_back(temp_points[1]);


                    new_group.addDynamicTR(time, align, points);
                    }

                else {
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
                }

            }

            // Trying to get rotate element
            if (strcmp(elem->Name(), "rotate") == 0) {
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

                const XMLAttribute* time_attribute = elem->FindAttribute("time");

                // Test if we have a dynamic rotation
                if (time_attribute) {
                    float time = atof(time_attribute->Value());

                    new_group.addDynamicRT(time, axisX_rot, axisY_rot, axisZ_rot);
                }

                    // Static rotation
                else {
                    // Get angle attribute
                    const XMLAttribute* angle_attribute = elem->FindAttribute("angle");
                    float angle_rot;
                    angle_attribute ? angle_rot = atof(angle_attribute->Value()) : angle_rot = 0;

                    new_group.addRotate(angle_rot, axisX_rot, axisY_rot, axisZ_rot);
                }

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

            }
            elem = elem->NextSiblingElement();
        }
    }
    // Trying to get models element
    XMLElement* models_element = main_element->FirstChildElement("models");
    if (models_element) {
        // Get all model elements
        XMLElement *model_element = models_element->FirstChildElement("model");
        while (model_element) {
            Shape shape;

            // Parse model file attribute
            const XMLAttribute *file_attribute = model_element->FindAttribute("file");
            if (file_attribute) {
                string file = file_attribute->Value();
                shape = load3dFile("../3d/" + file);
            }

            new_group.addShape(shape);

            model_element = model_element->NextSiblingElement("models");
        }
    }

    // Trying to get group elements
    XMLElement *group_element = main_element->FirstChildElement("group");
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


// Function to draw a single group
void drawGroup(Group g) {

    // Set the model view matrix as current, just for safety
    glMatrixMode(GL_MODELVIEW);

    // Push matrix on beggining
    glPushMatrix();

    // Trying to get transformations from group
    vector<Transformation*> t = g.getTransformations();

    for (Transformation* trans : t) {
        Translate* t_t = dynamic_cast<Translate*>(trans);
        if (t_t) {
            glTranslatef(t_t->getX(), t_t->getY(), t_t->getZ());
            continue;
        }
        Scale* t_s = dynamic_cast<Scale*>(trans);
        if (t_s) {
            glScalef(t_s->getX(), t_s->getY(), t_s->getZ());
            continue;
        }
        Rotate* t_r = dynamic_cast<Rotate*>(trans);
        if (t_r) {
            glRotatef(t_r->getAngle(), t_r->getAxisX(), t_r->getAxisY(), t_r->getAxisZ());
            continue;
        }

        DynamicTranslate* t_dt = dynamic_cast<DynamicTranslate*>(trans);
        if (t_dt) {
            t_dt->renderCatmullRomCurve();
            t_dt->applyTransformation();
            continue;
        }

        DynamicRotate* t_dr = dynamic_cast<DynamicRotate*>(trans);
        if (t_dr) {
            t_dr->applyTransformation();
            continue;
        }
    }


    glColor3f(1.0f, 1.0f, 1.0f);

    // Drawing objects in this group
    vector<Shape> shapes = g.getShape();
    for (Shape model : shapes) {
        glBindBuffer(GL_ARRAY_BUFFER, model.getVBOInd());
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, model.getVerticeCount());
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
    //
    //
    gluLookAt(rad*cos(bet)*sin(alpha), rad*sin(bet), rad*cos(bet)*cos(alpha),
              cam->getLookx(), cam->getLooky(), cam->getLookz(),
              cam->getUpx(), cam->getUpy(), cam->getUpz());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //drawAxis();
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("CG");

    glewInit();

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);


    //  OpenGL settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutSpecialFunc(specialKeys);

    strcpy(path, "../test_files_phase_3/");
    strcat(path, argv[1]);
    lerXML(path);

    rad = sqrt(pow(cam->getLookx() - cam->getPx(), 2) + pow(cam->getLooky() - cam->getPy(), 2) + pow(cam->getLookz() - cam->getPz(), 2));
    bet = atan2(cam->getPy(),cam->getPx());
    alpha = atan2(sqrt(cam->getPx()*cam->getPx()+cam->getPy()*cam->getPy()),cam->getPz());

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
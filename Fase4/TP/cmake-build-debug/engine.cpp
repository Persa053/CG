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
#include "Lights.h"
#include <math.h>
#include <vector>


using namespace tinyxml2;
using namespace std;




float alpha = 0.0f;
float bet = 0.5f;
float rad = 100.0f;

Camera* cam = new Camera();
vector <Group> groups;
vector<Light*> lights_vector = {};


Shape load3dFile(string _3dFile) {
    string line;
    string delim = ", ";
    ifstream file;
    vector<float> points;
    vector<float> normais;
    vector<float> texturas;

    file.open(_3dFile.c_str(), ios::in);

    if (file.is_open()) {
        while (getline(file, line)) {
            //get all pointstextures
            string token;
            istringstream tokenStream(line);
            while (getline(tokenStream, token, ',')) {
                points.push_back(atof(token.c_str()));

            }
            //get all normals
            getline(file,line);
            string token1;
            istringstream tokenStream1(line);
            while (getline(tokenStream1, token1, ','))
                normais.push_back(atof(token1.c_str()));

            //
            string token2;
            istringstream tokenStream2(line);
            getline(file,line);
            while (getline(tokenStream2, token2, ','))
            texturas.push_back(atof(token2.c_str()));


        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << _3dFile.c_str() << "\n";
    }

    GLuint vertice_count = (GLuint) (points.size() / 3);
    GLuint vbo_ind;
    GLuint n_vbo_ind = 0;
    GLuint t_vbo_ind = 0;

    // Push points to VBO
    glGenBuffers(1, &vbo_ind);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ind);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

    // Push normals to VBO
    glGenBuffers(1, &n_vbo_ind);
    glBindBuffer(GL_ARRAY_BUFFER, n_vbo_ind);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normais.size(), normais.data(), GL_STATIC_DRAW);


    // Push textures to VBO
    glGenBuffers(1, &t_vbo_ind);
    glBindBuffer(GL_ARRAY_BUFFER, t_vbo_ind);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texturas.size(), texturas.data(), GL_STATIC_DRAW);

    return Shape(vbo_ind, n_vbo_ind, t_vbo_ind, vertice_count);
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

                // Only used if we wanted to support multiple translates in a group
                // If so, needed to change the 'if' to a 'while' too
                //translate_element = translate_element->NextSiblingElement("translate");
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
        XMLElement *model_element = models_element->FirstChildElement("model");
        while (model_element) {
            Shape shape;

            // Parse model file attribute
            const XMLAttribute *file_attribute = model_element->FindAttribute("file");
            if (file_attribute) {
                string file = file_attribute->Value();
                shape = load3dFile("../3d/" + file);
            }

            const XMLElement* texture_element = model_element->FirstChildElement("texture");
            if (texture_element){
                const XMLAttribute *texture_attribute = model_element->FindAttribute("file");
                string texture_file;
                texture_attribute ? texture_file = texture_attribute->Value() : texture_file = "";

                shape.loadTexture("textures/" + texture_file);
            }

            XMLElement* color_element = model_element->FirstChildElement("color");
            if (color_element) {
                const XMLElement *elem = color_element->FirstChildElement();
                while (elem) {
                    if (strcmp(elem->Name(), "diffuse") == 0) {
                        GLfloat diffuse[4];

                        const XMLAttribute *r_attribute = elem->FindAttribute("R");
                        r_attribute ? diffuse[0] = atof(r_attribute->Value()) : diffuse[0] = 1.0f;

                        const XMLAttribute *g_attribute = elem->FindAttribute("G");
                        g_attribute ? diffuse[1] = atof(g_attribute->Value()) : diffuse[1] = 1.0f;

                        const XMLAttribute *b_attribute = elem->FindAttribute("B");
                        b_attribute ? diffuse[2] = atof(b_attribute->Value()) : diffuse[2] = 1.0f;

                        diffuse[3] = 1.0f;

                        shape.setDiffuse(diffuse);
                    }

                    else if (strcmp(elem->Name(), "ambient") == 0) {
                        GLfloat amb[4];

                        const XMLAttribute *r_attribute = elem->FindAttribute("R");
                        r_attribute ? amb[0] = atof(r_attribute->Value()) : amb[0] = 0.0;

                        const XMLAttribute *g_attribute = elem->FindAttribute("G");
                        g_attribute ? amb[1] = atof(g_attribute->Value()) : amb[1] = 0.0;

                        const XMLAttribute *b_attribute = elem->FindAttribute("B");
                        b_attribute ? amb[2] = atof(b_attribute->Value()) : amb[2] = 0.0;

                        amb[3] = 1.0;

                        shape.setAmbient(amb);
                    }

                    else if (strcmp(elem->Name(), "specular") == 0) {
                        GLfloat spec[4];

                        const XMLAttribute *r_attribute = elem->FindAttribute("R");
                        r_attribute ? spec[0] = atof(r_attribute->Value()) : spec[0] = 0.0;

                        const XMLAttribute *g_attribute = elem->FindAttribute("G");
                        g_attribute ? spec[1] = atof(g_attribute->Value()) : spec[1] = 0.0;

                        const XMLAttribute *b_attribute = elem->FindAttribute("B");
                        b_attribute ? spec[2] = atof(b_attribute->Value()) : spec[2] = 0.0;

                        spec[3] = 1.0;

                        shape.setSpecular(spec);
                    }

                    else if (strcmp(elem->Name(), "emissive") == 0) {
                        GLfloat emi[4];

                        const XMLAttribute *r_attribute = elem->FindAttribute("R");
                        r_attribute ? emi[0] = atof(r_attribute->Value()) : emi[0] = 0.0;

                        const XMLAttribute *g_attribute = elem->FindAttribute("G");
                        g_attribute ? emi[1] = atof(g_attribute->Value()) : emi[1] = 0.0;

                        const XMLAttribute *b_attribute = elem->FindAttribute("B");
                        b_attribute ? emi[2] = atof(b_attribute->Value()) : emi[2] = 0.0;

                        emi[3] = 1.0;

                        shape.setEmissive(emi);
                    }

                    else if (strcmp(elem->Name(), "shininess") == 0) {
                        GLfloat shinniness[1];

                        const XMLAttribute *r_attribute = elem->FindAttribute("value");
                        r_attribute ? shinniness[0] = atof(r_attribute->Value()) : shinniness[0] = 0;

                        shape.setShininess(shinniness);
                    }

                    elem = elem->NextSiblingElement();
                }
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

Light* parseXMLLightElement (XMLElement* light_element, int light_ind) {
    Light* new_light = nullptr;

    GLfloat ambient[4] = { 0, 0, 0,1 };
    GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[4] = { 1, 1, 1,1 };

    // Get light type: POINT, DIRECTIONAL or SPOT
    const XMLAttribute* type_attribute = light_element->FindAttribute("type");
    const char* light_type;
    type_attribute ? light_type = type_attribute->Value() : light_type = "";

    if (strcmp(light_type, "point") == 0) {
        float posX = 0.0, posY = 0.0, posZ = 0.0;
        if (light_element->Attribute("posx"))
            posX = stof(light_element->Attribute("posx"));
        if (light_element->Attribute("posy"))
            posY = stof(light_element->Attribute("posy"));
        if (light_element->Attribute("posz"))
            posZ = stof(light_element->Attribute("posz"));

        new_light = new LightPoint(light_ind, new Ponto(posX, posY, posZ), ambient, diffuse, specular);
    }
    else if (strcmp(light_type, "directional") == 0) {
        float dirX = 0.0, dirY = 0.0, dirZ = 0.0;
        if (light_element->Attribute("dirx"))
            dirX = stof(light_element->Attribute("dirx"));
        if (light_element->Attribute("diry"))
            dirY = stof(light_element->Attribute("diry"));
        if (light_element->Attribute("dirz"))
            dirZ = stof(light_element->Attribute("dirz"));

        new_light = new LightDirectional(light_ind, new Ponto(dirX, dirY, dirZ), ambient, diffuse, specular);
    }
    else if (strcmp(light_type, "spot") == 0) {
        float posX = 0.0, posY = 0.0, posZ = 0.0;
        if (light_element->Attribute("posx"))
            posX = stof(light_element->Attribute("posx"));
        if (light_element->Attribute("posy"))
            posY = stof(light_element->Attribute("posy"));
        if (light_element->Attribute("posz"))
            posZ = stof(light_element->Attribute("posz"));

        float dirX = 0.0, dirY = 0.0, dirZ = 0.0;
        if (light_element->Attribute("dirx"))
            dirX = stof(light_element->Attribute("dirx"));
        if (light_element->Attribute("diry"))
            dirY = stof(light_element->Attribute("diry"));
        if (light_element->Attribute("dirz"))
            dirZ = stof(light_element->Attribute("dirz"));

        float cutoff = 0.0;
        if (light_element->Attribute("cutoff"))
            cutoff = stof(light_element->Attribute("cutoff"));

        new_light = new LightSpot(light_ind, new Ponto(posX, posY, posZ), new Ponto(dirX, dirY, dirZ), cutoff, ambient, diffuse, specular);
    }

    return new_light;
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

    XMLElement* light_element = root->FirstChildElement("lights");
    if (light_element) {
        int light_ind = 0;

        XMLElement* elem = light_element->FirstChildElement("light");
        while (elem) {
            Light* l = parseXMLLightElement(elem, light_ind);
            if (l != nullptr)
                lights_vector.push_back(l);

            elem = light_element->NextSiblingElement("light");
            light_ind++;
        }
    }


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



void drawShape(Shape s) {

    // Set model material properties
    //GLfloat dif[4] = {200, 200, 0, 1};
    //GLfloat amb[4] = {50, 50, 0, 1};
    //GLfloat spe[4] = {0, 0, 0, 1};
    //GLfloat emi[4] = {0, 0, 0, 1};
    //GLfloat shi[1] = {0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, s.getAmbient());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, s.getDiffuse());
    glMaterialfv(GL_FRONT, GL_SPECULAR, s.getSpecular());
    glMaterialfv(GL_FRONT, GL_EMISSION, s.getEmissive());
    glMaterialfv(GL_FRONT, GL_SHININESS, s.getShininess());


    // Bind points VBO
    glBindBuffer(GL_ARRAY_BUFFER, s.getPVBOInd());
    glVertexPointer(3, GL_FLOAT, 0, 0);


    GLuint n_vbo_ind = s.getNVBOInd();
    if (n_vbo_ind != 0) {
        // Bind normals VBO
        glBindBuffer(GL_ARRAY_BUFFER, n_vbo_ind);
        glNormalPointer(GL_FLOAT, 0, 0);
    }


    GLuint t_vbo_ind = s.getTVBOInd();
    if (t_vbo_ind != 0) {
        // Bind textures VBO
        glBindBuffer(GL_ARRAY_BUFFER, t_vbo_ind);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glBindTexture(GL_TEXTURE_2D, s.getTextureID());
    }

    glBindBuffer(GL_ARRAY_BUFFER, t_vbo_ind);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
    glBindTexture(GL_TEXTURE_2D, s.getTextureID());

    glDrawArrays(GL_TRIANGLES, 0, s.getVerticeCount());

    glBindTexture(GL_TEXTURE_2D, 0);
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


    // Drawing objects in this group
    vector<Shape> shapes = g.getShape();
    for (Shape shape : shapes) {
        drawShape(shape);

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


    gluLookAt(rad*cos(bet)*sin(alpha), rad*sin(bet), rad*cos(bet)*cos(alpha),
              cam->getLookx(), cam->getLooky(), cam->getLookz(),
              cam->getUpx(), cam->getUpy(), cam->getUpz());
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (Light* l : lights_vector) {
        l->apply();
    }

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

        case GLUT_KEY_PAGE_DOWN: rad -= rad*0.05;
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

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("CG");
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


    // init GLEW
    #ifndef __APPLE__
        glewInit();
    #endif

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutSpecialFunc(specialKeys);

    strcpy(path, "../test_files_phase_4/");
    strcat(path, argv[1]);
    lerXML(path);
    rad = sqrt(pow(cam->getLookx() - cam->getPx(), 2) + pow(cam->getLooky() - cam->getPy(), 2) + pow(cam->getLookz() - cam->getPz(), 2));


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    // Enable lights parsed in XML file
    for (int i = 0; i < lights_vector.size(); i++)
        glEnable(GL_LIGHT0 + (GLenum) i);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
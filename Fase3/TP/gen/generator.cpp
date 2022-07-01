//
// Created by persa53 on 07/03/22.
//

#include "generator.h"


void plano(float lado, float grid, string nome) {

    float tlado = lado /grid;
    ofstream file(nome);
    float met =(float) lado/2;
    float x,y,z;
    float x1,z1;

    for(int i=0;i<grid;i++){
        for(int j = 0;j<grid;j++){
            x = met - j*tlado;
            z = -met + i*tlado;
            x1 = met - (j + 1) * tlado;
            z1 = -met + (i + 1) * tlado;

            printf("%f %f %f\n",x,y,z);
            file << x << "," << y << "," << z << endl;
            printf("%f %f %f\n",x,y,-z);
            file << x1 << "," << y << "," << z << endl;
            printf("%f %f %f\n",-x,y,-z);
            file << x1 << "," << y << "," << z1 << endl;


            // Triangulo 2
            printf("%f %f %f\n",-x,y,z);
            file << x << "," << y << "," << z << endl;
            printf("%f %f %f\n",x,y,z);
            file << x1 << "," << y << "," << z1 << endl;
            printf("%f %f %f\n",-x,y,-z);
            file << x << "," << y << "," << z1 << endl;
        }
    }


    file.close();
}
void box(int aresta, int grid, string nome){

    float tlado = (float) aresta /grid;
    ofstream file(nome);
    float met =(float) aresta/2;
    float x,y,z;
    float x1,z1, ybase, yteto;

    for(int i=0;i<grid;i++) {
        for (int j = 0; j < grid; j++) {
            x = -met;
            z = -met + i * tlado;
            x1 = met;
            z1 = -met + (i + 1) * tlado;
            ybase = met - j * tlado;
            yteto = met - (j + 1) * tlado;

            printf("%f %f %f\n", x, y, z);
            file << x << "," << ybase << "," << z << endl;
            printf("%f %f %f\n", x, y, -z);
            file << x << "," << yteto << "," << z << endl;
            printf("%f %f %f\n", -x, y, -z);
            file << x << "," << yteto << "," << z1 << endl;


            // Triangulo 2
            printf("%f %f %f\n", -x, y, z);
            file << x << "," << ybase << "," << z << endl;
            printf("%f %f %f\n", x, y, z);
            file << x << "," << yteto << "," << z1 << endl;
            printf("%f %f %f\n", -x, y, -z);
            file << x << "," << ybase << "," << z1 << endl;

            printf("%f %f %f\n", x, y, z);
            file << x1 << "," << ybase << "," << z << endl;
            printf("%f %f %f\n", -x, y, -z);
            file << x1 << "," << yteto << "," << z1 << endl;
            printf("%f %f %f\n", x, y, -z);
            file << x1 << "," << yteto << "," << z << endl;



            // Triangulo 2
            printf("%f %f %f\n", -x, y, z);
            file << x1 << "," << ybase << "," << z << endl;
            printf("%f %f %f\n", -x, y, -z);
            file << x1 << "," << ybase << "," << z1 << endl;
            printf("%f %f %f\n", x, y, z);
            file << x1 << "," << yteto << "," << z1 << endl;

        }
    }

        for(int i=0;i<grid;i++) {
            for (int j = 0; j < grid; j++) {
                x = met - j * tlado;
                z = -met;
                x1 = met - (j + 1) * tlado;
                z1 = met;
                ybase = -met + i * tlado;
                yteto = -met + (i + 1) * tlado;

                printf("%f %f %f\n", x, y, z);
                file << x << "," << ybase << "," << z << endl;
                printf("%f %f %f\n", x, y, -z);
                file << x1 << "," << ybase << "," << z << endl;
                printf("%f %f %f\n", -x, y, -z);
                file << x1 << "," << yteto << "," << z << endl;


                // Triangulo 2
                printf("%f %f %f\n", -x, y, z);
                file << x << "," << ybase << "," << z << endl;
                printf("%f %f %f\n", x, y, z);
                file << x1 << "," << yteto << "," << z << endl;
                printf("%f %f %f\n", -x, y, -z);
                file << x << "," << yteto << "," << z << endl;

                printf("%f %f %f\n", x, y, z);
                file << x << "," << ybase << "," << z1 << endl;
                printf("%f %f %f\n", -x, y, -z);
                file << x1 << "," << yteto << "," << z1 << endl;
                printf("%f %f %f\n", x, y, -z);
                file << x1 << "," << ybase << "," << z1 << endl;



                // Triangulo 2
                printf("%f %f %f\n", -x, y, z);
                file << x << "," << ybase << "," << z1 << endl;
                printf("%f %f %f\n", -x, y, -z);
                file << x << "," << yteto << "," << z1 << endl;
                printf("%f %f %f\n", x, y, z);
                file << x1 << "," << yteto << "," << z1 << endl;

            }
        }
        for(int i=0;i<grid;i++) {
            for (int j = 0; j < grid; j++) {
                x = met - j * tlado;
                z = -met + i * tlado;
                x1 = met - (j + 1) * tlado;
                z1 = -met + (i + 1) * tlado;
                ybase = -met;
                yteto = met;

                        printf("%f %f %f\n", x, y, z);
                        file << x << "," << ybase << "," << z << endl;
                        printf("%f %f %f\n", -x, y, -z);
                        file << x1 << "," << ybase << "," << z1 << endl;
                        printf("%f %f %f\n", x, y, -z);
                        file << x1 << "," << ybase << "," << z << endl;

                        // Triangulo 2
                        printf("%f %f %f\n", -x, y, z);
                        file << x << "," << ybase << "," << z << endl;
                        printf("%f %f %f\n", -x, y, -z);
                        file << x << "," << ybase << "," << z1 << endl;
                        printf("%f %f %f\n", x, y, z);
                        file << x1 << "," << ybase << "," << z1 << endl;


                        printf("%f %f %f\n", x, y, z);
                        file << x << "," << yteto << "," << z << endl;
                        printf("%f %f %f\n", x, y, -z);
                        file << x1 << "," << yteto << "," << z << endl;
                        printf("%f %f %f\n", -x, y, -z);
                        file << x1 << "," << yteto << "," << z1 << endl;


                        // Triangulo 2
                        printf("%f %f %f\n", -x, y, z);
                        file << x << "," << yteto << "," << z << endl;
                        printf("%f %f %f\n", x, y, z);
                        file << x1 << "," << yteto << "," << z1 << endl;
                        printf("%f %f %f\n", -x, y, -z);
                        file << x << "," << yteto << "," << z1 << endl;
                    }
                }
    file.close();
    }

void sphere(int raio, int slices, int stacks, string nome){

    ofstream file(nome);
    float espca = (2 * M_PI)/ slices;
    float espcb= M_PI / stacks;
    float alpha,beta = M_PI/2;
    for(int i = 0; i < stacks; i++){
        alpha = 0;
        for(int j = 0; j < slices; j++){

            float x1 = raio * sin(alpha) * cos(beta);
            float y1 = raio * sin(beta);
            float z1 = raio * cos(alpha) * cos(beta);

            float x2 = raio * sin(alpha + espca) * cos(beta - espcb);
            float y2 = raio * sin(beta - espcb);
            float z2 = raio * cos(alpha + espca) * cos(beta - espcb);

            float x3 = raio * sin(alpha) * cos(beta - espcb);
            float y3 = raio * sin(beta - espcb);
            float z3 = raio * cos(alpha) * cos(beta - espcb);

            float x4 = raio * sin(alpha + espca) * cos(beta);
            float y4 = raio * sin(beta);
            float z4 = raio * cos(alpha + espca) * cos(beta);

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;

            alpha += espca;
        }

        beta -= espcb;
    }
    file.close();
}

void cone(float raio, float height, float slices, float stacks, string nome){

    ofstream file(nome);
    float espca = (float)( 2 * M_PI)/ slices;
    float esph = height/stacks;
    float r = raio/stacks;
    float alpha;
    float proxRaio;

    alpha = 0;
    for(int i = 0; i < slices; i++){

        float x1 = raio * sin(alpha);
        float z1 = raio * cos(alpha);

        float x2 = raio * sin(alpha + espca);
        float z2 = raio * cos(alpha + espca);

        file << x1 << "," << 0 << "," << z1 << endl;
        file << 0 << "," << 0 << "," << 0 << endl;
        file << x2 << "," << 0 << "," << z2 << endl;

        alpha += espca;
    }

    for(int i = 0; i < stacks; i++){
        alpha = 0;
        proxRaio = raio - r;
        for(int j = 0; j < slices; j++){

            float x1 = raio * sin(alpha);
            float y1 = esph*i;
            float z1 = raio * cos(alpha);

            float x2 = raio * sin(alpha + espca);
            float y2 = esph*i;
            float z2 = raio * cos(alpha + espca);

            float x3 = proxRaio * sin(alpha);
            float y3 = esph*(i + 1);
            float z3 = proxRaio * cos(alpha);

            float x4 = proxRaio * sin(alpha + espca) ;
            float y4 = esph*(i + 1);
            float z4 = proxRaio * cos(alpha + espca);

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;

            file << x3 << "," << y3 << "," << z3 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;

            alpha += espca;
        }
        raio -=r;
    }


    file.close();
}

void torus(double r1, double r2, double divc, double divd, string nome){
    ofstream file(nome);

    double alpha = (2 * M_PI) / divc;
    double beta = (2 * M_PI) / divd;

    for(float i = 0; i <=(2*M_PI); i+= alpha){

        for(float j = 0; j <= 2*M_PI; j+= beta){

            float x1 = cos(j) * (cos(i) * r1 + r2);
            float y1 = sin(j) * (cos(i) * r1 + r2);
            float z1 = r1 * sin(i);

            float x2 = cos(j + beta) * (cos(i) * r1 + r2);
            float y2 = sin(j + beta) * (cos(i) * r1 + r2);
            float z2 = r1 * sin(i);

            float x3 = cos(j + beta) * (cos(i + alpha) * r1 + r2);
            float y3 = sin(j + beta) * (cos(i + alpha) * r1 + r2);
            float z3 = r1 * sin(i + alpha);

            float x4 = cos(j) * (cos(i + alpha) * r1 + r2);
            float y4 = sin(j) * (cos(i + alpha) * r1 + r2);
            float z4 = r1 * sin(i + alpha);

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;


        }
    }

    file.close();
}


float* bezierCubica(float u, float* p0, float* p1, float* p2, float* p3){

    float t = 1.0 - u;
    float* ponto = new float[3];

    ponto[0] = pow(t,3) * p0[0] + 3 * u * pow(t,2) * p1[0] + 3 * pow(u,2) * t * p2[0] + pow(u,3) * p3[0];
    ponto[1] = pow(t,3) * p0[1] + 3 * u * pow(t,2) * p1[1] + 3 * pow(u,2) * t * p2[1] + pow(u,3) * p3[1];
    ponto[2] = pow(t,3) * p0[2] + 3 * u * pow(t,2) * p1[2] + 3 * pow(u,2) * t * p2[2] + pow(u,3) * p3[2];

    return ponto;
}

float* bezier(float u, float v, int* patches, float** pontos){
    float calcv[4][3];
    float calcu[4][3];
    float* ponto = new float[3];
    float* res;
    int j = 0, r = 0;

    for(int i = 0; i < 16;i++){
        calcv[j][0] = pontos[patches[i]][0];
        calcv[j][1] = pontos[patches[i]][1];
        calcv[j][2] = pontos[patches[i]][2];

        j++;
        if((j % 4) == 0){
            ponto = bezierCubica(v, calcv[0], calcv[1], calcv[2], calcv[3]);
            calcu[r][0] = ponto[0];
            calcu[r][1] = ponto[1];
            calcu[r][2] = ponto[2];
            r++;
            j=0;
        }
    }

    res = bezierCubica(u, calcu[0], calcu[1], calcu[2], calcu[3]);

    return res;
}

void patch(string file, int tess, string nome){

    ofstream  fileo;
    fileo.open(nome, ios::out);
    ifstream filei;
    filei.open(file, ios::in);
    string line, aux;

    int i = 0;




    if(filei.is_open()){
        getline(filei,line);
        int npatch = atoi(line.c_str());

        int** patches = new int*[npatch];


        for(int r = 0; r<npatch; r++){
            getline(filei,line);
            patches[r] = new int[16];

            for(int j = 0; j<16; j++){
                i = line.find(",");
                aux = line.substr(0,i);
                patches[r][j] = atoi(aux.c_str());
                line.erase(0,i+1);
            }
        }

        getline(filei,line);
        int npontos = atoi(line.c_str());
        float** pontos = new float*[npontos];
        for(int r = 0; r<npontos; r++){
            getline(filei,line);
            pontos[r] = new float[3];
            for(int j = 0; j<3;j++){
                i = line.find(",");
                aux = line.substr(0,i);
                pontos[r][j] = atof(aux.c_str());
                line.erase(0,i+1);
            }
        }

        float t = 1.0/tess, u, v, u2, v2;
        float*** res = new float**[npatch];

        for(int r = 0; r<npatch; r++){
            res[r] = new float*[4];

            for(int nu = 0; nu < tess; nu++){

                for(int nv = 0; nv < tess; nv++){


                    u = nu * t;
                    v = nv * t;
                    u2 = (nu + 1) * t;
                    v2 = (nv + 1) * t;

                    res[r][0] = bezier(u, v, patches[r], pontos);
                    res[r][1] = bezier(u2, v, patches[r], pontos);
                    res[r][2] = bezier(u, v2, patches[r], pontos);
                    res[r][3] = bezier(u2, v2, patches[r], pontos);

                    fileo << res[r][0][0] << "," << res[r][0][1] << "," << res[r][0][2] << endl;
                    fileo << res[r][2][0] << "," << res[r][2][1] << "," << res[r][2][2] << endl;
                    fileo << res[r][1][0] << "," << res[r][1][1] << "," << res[r][1][2] << endl;

                    fileo << res[r][1][0] << "," << res[r][1][1] << "," << res[r][1][2] << endl;
                    fileo << res[r][2][0] << "," << res[r][2][1] << "," << res[r][2][2] << endl;
                    fileo << res[r][3][0] << "," << res[r][3][1] << "," << res[r][3][2] << endl;
                }
            }
        }
    }
    filei.close();
    fileo.close();
}


int main (int argc , char **argv){


    if( argc > 1) {
        char path[1024];
        strcpy(path, "../3d/");
        if (strcmp(argv[1],"plano") == 0) {
            strcat(path,argv[4]);
            plano(atof(argv[2]),atof(argv[3]),path);
        }

        else if (strcmp(argv[1],"box") == 0) {
            strcat(path,argv[4]);
            box(atoi(argv[2]),atoi(argv[3]),path);
        }
        else if (strcmp(argv[1],"sphere") == 0) {
            strcat(path,argv[5]);
            sphere(atoi(argv[2]),atoi(argv[3]), atoi(argv[4]),path);
        }
        else if (strcmp(argv[1],"cone") == 0) {
            strcat(path,argv[6]);
            cone(atof(argv[2]),atoi(argv[3]), atoi(argv[4]), atoi(argv[5]),path);
        }

        else if (strcmp(argv[1],"torus") == 0) {
            strcat(path,argv[6]);
            torus(atof(argv[2]),atof(argv[3]), atoi(argv[4]), atoi(argv[5]),path);
        }
        else if (strcmp(argv[1],"bezier") == 0) {
            strcat(path,argv[4]);
            char path2[1024];
            strcpy(path2, "../3d/");
            strcat(path2,argv[2]);
            patch(path2, atoi(argv[3]), path);
        }
        else {
            printf("FIGURA IMPOSSÍVEL\n");
        }

    }
    else {
        printf("ARGUMENTOS INSUFICIENTES\n");
    }

    return 0;
}
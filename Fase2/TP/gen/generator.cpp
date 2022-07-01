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
        else {
            printf("FIGURA IMPOSSÍVEL\n");
        }

    }
    else {
        printf("ARGUMENTOS INSUFICIENTES\n");
    }

    return 0;
}
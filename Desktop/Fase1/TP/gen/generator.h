//
// Created by persa53 on 07/03/22.
//

#ifndef TP_GENERATOR_H
#define TP_GENERATOR_H


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

void plano(int lado, int grid, string nome);
void box(int aresta, int grid, string nome);
void sphere(int raio, int slices, int stacks, string nome);
void cone(float raio, float height, float slices, float stacks, string nome);




#endif //TP_GENERATOR_H

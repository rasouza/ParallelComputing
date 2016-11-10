#ifndef VECTOR_H
#define VECTOR_H

#define _USE_MATH_DEFINES

#include "ppm.h"
#include <math.h>

// Vetor de cor decomposto em coordenadas cartesianas
typedef struct {
	int x, y;
} COLOR;

// Vetor de interação entre os pixels
typedef struct {
	double theta;
	COLOR red, blue;
} vetor;

// Stencil com as possíveis interações entre os pixels da imagem
typedef struct {
	int x, y;
	PPMPixel *up, *left, *down, *right, *center;
} Stencil;



void interactTwoBodies(double* center, double* target, double qty);
vetor getVetor(PPMPixel* pixel);
void interact(Stencil mask, vetor interacao);
int isExcess(PPMPixel pixel);


#endif // !VECTOR_H


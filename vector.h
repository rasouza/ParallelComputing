#ifndef VECTOR_H
#define VECTOR_H

#define M_PI		3.14159265358979323846	/* pi */
#define M_PI_2		1.57079632679489661923	/* pi/2 */
#define M_PI_4		0.78539816339744830962	/* pi/4 */

#define TRUE 1
#define FALSE 0

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "ppm.h"
#include <omp.h>
#include <math.h>

// Vetor de cor decomposto em coordenadas cartesianas
typedef struct {
	double x, y;
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


vetor getVetor(PPMPixel pixel);
Stencil fillStencil(PPMImage *image, int x, int y);

void interactTwoBodies(double* center, double* target, double qty, omp_lock_t lock);
void interact(Stencil *mask, vetor interacao, omp_lock_t lock);

int isExcess(PPMPixel pixel);
void checkExcess(PPMImage *image);
void shareExcess(Stencil *mask);

void rotateTheta(PPMPixel *pixel);

#endif // !VECTOR_H


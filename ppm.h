#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float red, green, blue;
} PPMPixel;

typedef struct {
	int x, y;
	PPMPixel **data;
} PPMImage;

#define RGB_COMPONENT_COLOR 255
#define CREATOR "RPFELGUEIRAS"

static PPMImage *readPPM(const char *filename);

#endif
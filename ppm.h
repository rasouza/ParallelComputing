#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double red, green, blue;
} PPMPixel;

typedef struct {
	int x, y;
	PPMPixel **data;
} PPMImage;

#define RGB_COMPONENT_COLOR 255

static PPMImage *readPPM(const char *filename);
void writePPM(const char *filename, PPMImage *img);

#endif
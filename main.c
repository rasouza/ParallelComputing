#include "ppm.h"
#include "vector.h"

int main() {
	PPMImage *image;
	image = readPPM("data/linux.ppm");
	printf("vermelho em (0,0): %f", image->data[2][0].red);
}
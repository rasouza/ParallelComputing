#include "vector.h"

int main() {
	PPMImage *image;
	image = readPPM("data/linux.ppm");
	printf("vermelho em (2,0): %lf\n", image->data[2][0].red);
	printf("O tamanho da imagem eh: %dx%d\n", image->x, image->y);
	writePPM("data/linux2.ppm", image);
}

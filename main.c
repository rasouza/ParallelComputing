#include "ppm.h"
#include "vector.h"

int main() {
	PPMImage *image;
	vetor interacao;
	image = readPPM("data/linux.ppm");
	printf("Pixel (53,11) R: %lf | G: %lf | B: %lf\n\n", image->data[53][11].red, image->data[53][11].green, image->data[53][11].blue);

	printf("Seus vizinhos sao:\n");
	printf("(52,11) R: %lf | G: %lf | B: %lf\n", image->data[52][11].red, image->data[52][11].green, image->data[52][11].blue);
	printf("(54,11) R: %lf | G: %lf | B: %lf\n", image->data[54][11].red, image->data[54][11].green, image->data[54][11].blue);
	printf("(53,10) R: %lf | G: %lf | B: %lf\n", image->data[53][10].red, image->data[53][10].green, image->data[53][10].blue);
	printf("(53,12) R: %lf | G: %lf | B: %lf\n", image->data[53][12].red, image->data[53][12].green, image->data[53][12].blue);

	interacao = getVetor(image->data[53][11]);
	printf("\nO vetor eh: \n");
	printf("Theta: %lf\nRed: (%lf,%lf)\nBlue: (%lf,%lf)\n", interacao.theta, interacao.red.x, interacao.red.y, interacao.blue.x, interacao.blue.y);

	writePPM("data/linux2.ppm", image);
}
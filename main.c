#include "vector.h"

void debugPixel(PPMImage *image, int x, int y);

int main() {
	PPMImage *image;
	vetor interacao;
	image = readPPM("data/linux.ppm");

	debugPixel(image, 199, 68);

	printf("\n\n [[[ Interagindo 2 corpos... ]]] \n");
	printf(" [[[ Pixel (199,68) com (198,68) ]]] \n");
	printf(" [[[ vermelho na direcao Y ]]] \n\n");
	interacao = getVetor(image->data[199][68]);
	interactTwoBodies(&image->data[199][68].red, &image->data[198][68].red, interacao.red.y);


	debugPixel(image, 199, 68);

	// writePPM("data/linux2.ppm", image);
}

void debugPixel(PPMImage *image, int x, int y)
{
	vetor interacao;
	printf("Pixel (%d,%d) R: %lf | G: %lf | B: %lf\n\n", x, y, image->data[x][y].red, image->data[x][y].green, image->data[x][y].blue);

	printf("Seus vizinhos sao:\n");
	printf("(%d,%d) R: %lf | G: %lf | B: %lf\n", x-1, y, image->data[x-1][y].red, image->data[x-1][y].green, image->data[x-1][y].blue);
	printf("(%d,%d) R: %lf | G: %lf | B: %lf\n", x+1, y, image->data[x+1][y].red, image->data[x+1][y].green, image->data[x+1][y].blue);
	printf("(%d,%d) R: %lf | G: %lf | B: %lf\n", x, y-1, image->data[x][y-1].red, image->data[x][y-1].green, image->data[x][y-1].blue);
	printf("(%d,%d) R: %lf | G: %lf | B: %lf\n", x, y+1, image->data[x][y+1].red, image->data[x][y+1].green, image->data[x][y+1].blue);

	interacao = getVetor(image->data[x][y]);
	printf("\nO vetor eh: \n");
	printf("Theta: %lf\nRed: (%lf,%lf)\nBlue: (%lf,%lf)\n", interacao.theta, interacao.red.x, interacao.red.y, interacao.blue.x, interacao.blue.y);

}
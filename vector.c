#include "vector.h"

void interactTwoBodies(double* center, double* target, double qty)
{
	double delta = (1 - *target) * qty;

	*target += delta;
	*center -= delta;
}

vetor getVetor(PPMPixel* pixel)
{
	vetor interacao;

	interacao.theta = 2 * M_PI * pixel->green; // Angulo Theta (Tomar cuidado pra ser no maximo 2pi)
	interacao.red.x = pixel->red * sin(interacao.theta); // Quantidade de vermelho no eixo X
	interacao.blue.x = -(pixel->blue * sin(interacao.theta)); // Quantidade de azul no eixo X
	interacao.red.y = pixel->red * cos(interacao.theta); // Quantidade de vermelho no eixo Y
	interacao.blue.y = -(pixel->blue * cos(interacao.theta)); // Quantidade de azul no eixo Y

	return interacao;
}

void interact(stencil* mask, vetor interacao)
{
	// @TO-DO: Existe algum jeito de fazer ser um bloco de codigo só?

	// P.S. O angulo neste EP começa a partir do eixo vertical Y positivo

	// Angulo no primeiro quadrante
	if (interacao.theta > 0 && interacao.theta < M_PI_4) {
		interactTwoBodies(&mask->center->red, &mask->up->red, interacao.red.y); // Vermelho em Y
		interactTwoBodies(&mask->center->red, &mask->right->red, interacao.red.x); // Vermelho em X
		interactTwoBodies(&mask->center->blue, &mask->down->blue, interacao.blue.y); // Azul em Y
		interactTwoBodies(&mask->center->blue, &mask->left->blue, interacao.blue.x); // Azul em X
	}

	// Angulo no segundo quadrante
	else if (interacao.theta >= M_PI_4 && interacao.theta < M_PI_2) {
		interactTwoBodies(&mask->center->red, &mask->down->red, interacao.red.y); // Vermelho em Y
		interactTwoBodies(&mask->center->red, &mask->right->red, interacao.red.x); // Vermelho em X
		interactTwoBodies(&mask->center->blue, &mask->up->blue, interacao.blue.y); // Azul em Y
		interactTwoBodies(&mask->center->blue, &mask->left->blue, interacao.blue.x); // Azul em X
	}

	// Angulo no terceiro quadrante
	else if (interacao.theta >= M_PI_2 && interacao.theta < 3 * M_PI_4) {
		interactTwoBodies(&mask->center->red, &mask->down->red, interacao.red.y); // Vermelho em Y
		interactTwoBodies(&mask->center->red, &mask->left->red, interacao.red.x); // Vermelho em X
		interactTwoBodies(&mask->center->blue, &mask->up->blue, interacao.blue.y); // Azul em Y
		interactTwoBodies(&mask->center->blue, &mask->right->blue, interacao.blue.x); // Azul em X
	}

	// Angulo no quarto quadrante
	else if (interacao.theta >= 3 * M_PI_4 && interacao.theta < 2 * M_PI) {
		interactTwoBodies(&mask->center->red, &mask->up->red, interacao.red.y); // Vermelho em Y
		interactTwoBodies(&mask->center->red, &mask->left->red, interacao.red.x); // Vermelho em X
		interactTwoBodies(&mask->center->blue, &mask->down->blue, interacao.blue.y); // Azul em Y
		interactTwoBodies(&mask->center->blue, &mask->right->blue, interacao.blue.x); // Azul em X
	}


}

int isExcess(PPMPixel pixel)
{
	return pixel.red > 1.0 || pixel.green > 1.0 || pixel.blue > 1.0;
}
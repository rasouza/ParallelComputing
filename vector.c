#include "vector.h"

void interactTwoBodies(double* center, double* target, double qty)
{
	double delta = (1 - *target) * qty / 4;

	*target += delta;
	*center -= delta;
}

vetor getVetor(PPMPixel pixel)
{
	vetor interacao;

	interacao.theta = 2 * M_PI * pixel.green; // Angulo Theta (Tomar cuidado pra ser no maximo 2pi)
	interacao.red.x = fabs(pixel.red * sin(interacao.theta)); // Quantidade de vermelho no eixo X
	interacao.blue.x = fabs(pixel.blue * sin(interacao.theta)); // Quantidade de azul no eixo X
	interacao.red.y = fabs(pixel.red * cos(interacao.theta)); // Quantidade de vermelho no eixo Y
	interacao.blue.y = fabs(pixel.blue * cos(interacao.theta)); // Quantidade de azul no eixo Y

	if(interacao.theta > 2 * M_PI)
		printf("\n[ERRO] Angulo maior que 2pi!\n");

	if(interacao.red.x > 1.0 || interacao.red.y > 1.0 || interacao.blue.x > 1.0 || interacao.blue.y > 1.0)
		printf("\n[ERRO] Pixel esta com alguma cor em excesso!\n");

	return interacao;
}

Stencil populaStencil(PPMImage *image, int x, int y) {
	Stencil mask;

	mask.x = x;
	mask.y = y;
    if (x > 0)
	    mask.up		= &image->data[x-1][y];
    else mask.up = NULL;
	if (y < image->y)
        mask.right	= &image->data[x][y+1];
    else mask.right = NULL;
	if (x < image->x)
        mask.down	= &image->data[x+1][y];
    else mask.down = NULL;
    if (y > 0)
        mask.left	= &image->data[x][y-1];
    else mask.left = NULL;
	mask.center	= &image->data[x][y];

	return mask;
}

void interact(Stencil *mask, vetor interacao)
{

	// @TO-DO: Existe algum jeito de fazer ser um bloco de codigo só?

	// P.S. O angulo neste EP começa a partir do eixo vertical Y positivo

	// Angulo no primeiro quadrante
	if (interacao.theta > 0 && interacao.theta < M_PI_4) {
        if (mask->up != NULL)
		    interactTwoBodies(&mask->center->red, &mask->up->red, interacao.red.y); // Vermelho em Y
		if (mask->right != NULL)
            interactTwoBodies(&mask->center->red, &mask->right->red, interacao.red.x); // Vermelho em X
		if (mask->down != NULL)
            interactTwoBodies(&mask->center->blue, &mask->down->blue, interacao.blue.y); // Azul em Y
		if (mask->left != NULL)
            interactTwoBodies(&mask->center->blue, &mask->left->blue, interacao.blue.x); // Azul em X
	}

	// Angulo no segundo quadrante
	else if (interacao.theta >= M_PI_4 && interacao.theta < M_PI_2) {
		if (mask->down != NULL)
            interactTwoBodies(&mask->center->red, &mask->down->red, interacao.red.y); // Vermelho em Y
		if (mask->right != NULL)
            interactTwoBodies(&mask->center->red, &mask->right->red, interacao.red.x); // Vermelho em X
		if (mask->up != NULL) 
            interactTwoBodies(&mask->center->blue, &mask->up->blue, interacao.blue.y); // Azul em Y
		if (mask->left != NULL)
            interactTwoBodies(&mask->center->blue, &mask->left->blue, interacao.blue.x); // Azul em X
	}

	// Angulo no terceiro quadrante
	else if (interacao.theta >= M_PI_2 && interacao.theta < 3 * M_PI_4) {
		if (mask->down != NULL)
            interactTwoBodies(&mask->center->red, &mask->down->red, interacao.red.y); // Vermelho em Y
		if (mask->left != NULL)
            interactTwoBodies(&mask->center->red, &mask->left->red, interacao.red.x); // Vermelho em X
		if (mask->up != NULL)
            interactTwoBodies(&mask->center->blue, &mask->up->blue, interacao.blue.y); // Azul em Y
		if (mask->right != NULL)
            interactTwoBodies(&mask->center->blue, &mask->right->blue, interacao.blue.x); // Azul em X
	}

	// Angulo no quarto quadrante
	else if (interacao.theta >= 3 * M_PI_4 && interacao.theta < 2 * M_PI) {
		if (mask->up != NULL)
            interactTwoBodies(&mask->center->red, &mask->up->red, interacao.red.y); // Vermelho em Y
		if (mask->left != NULL)
            interactTwoBodies(&mask->center->red, &mask->left->red, interacao.red.x); // Vermelho em X
		if (mask->down != NULL)
            interactTwoBodies(&mask->center->blue, &mask->down->blue, interacao.blue.y); // Azul em Y
		if (mask->right != NULL)
            interactTwoBodies(&mask->center->blue, &mask->right->blue, interacao.blue.x); // Azul em X
	}


}

int isExcess(PPMPixel pixel)
{
	return pixel.red > 1.0 || pixel.green > 1.0 || pixel.blue > 1.0;
}

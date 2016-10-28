#ifndef VECTOR_H
#define VECTOR_H

#define _USE_MATH_DEFINES

#include "ppm.h"
#include <math.h>

// Vetor de interação que cada pixel exerce em função das cores
typedef struct {
	double theta; // Valor de GREEN
	double red_x, red_y; // Decomposição de RED em X e Y
	double blue_x, blue_y; // Decomposição de BLUE em X e Y
} vetor;

// Stencil com as possíveis interações entre os pixels da imagem
typedef struct {
	int x, y;
	PPMPixel* up, left, down, right, center;
} stencil;

vetor getVetor(PPMPixel* pixel)
{
	vetor interacao;
	
	interacao.theta = 2 * M_PI * pixel->green; // Angulo Theta (Tomar cuidado pra ser no maximo 2pi)
	interacao.red_x = pixel->red * sin(interacao.theta); // Quantidade de vermelho no eixo X
	interacao.blue_x = -(pixel->blue * sin(interacao.theta)); // Quantidade de azul no eixo X
	interacao.red_y = pixel->red * cos(interacao.theta); // Quantidade de vermelho no eixo Y
	interacao.blue_y = -(pixel->blue * cos(interacao.theta)); // Quantidade de azul no eixo Y

	return interacao;
}

void interact(stencil *mask, vetor interacao)
{
	// Existe algum jeito de fazer ser um bloco de codigo só?

	if (interacao.theta > 0 && interacao.theta < M_PI_4) {
		// @TO-DO: talvez reduzir uma parte das contas repetidas pra uma variavel temporaria?
		// Vermelho em Y
		mask->up->red += (1 - mask->up->red) * interacao.red_y;
		mask->center->red -= (1 - mask->up->red) * interacao.red_y;
		// Vermelho em X
		mask->right->red += (1 - mask->right->red)*interacao.red_x;
		mask->center->red -= (1 - mask->right->red)*interacao.red_x;
		// Azul em X
		mask->left->blue += (1 - mask->left->blue)*interacao.blue_x;
		mask->center->blue -= (1 - mask->left->blue)*interacao.blue_x;
		// Azul em Y
		mask->down->blue += (1 - mask->down->blue)*interacao.blue_y;
		mask->center->blue -= (1 - mask->down->blue)*interacao.blue_y;
	}

	if (interacao.theta >= M_PI_4 && interacao.theta < M_PI_2) {
		// @TO-DO: talvez reduzir uma parte das contas repetidas pra uma variavel temporaria?
		// Vermelho em Y
		mask->down->red += (1 - mask->down->red) * interacao.red_y;
		mask->center->red -= (1 - mask->down->red) * interacao.red_y;
		// Vermelho em X
		mask->right->red += (1 - mask->right->red)*interacao.red_x;
		mask->center->red -= (1 - mask->right->red)*interacao.red_x;
		// Azul em X
		mask->left->blue += (1 - mask->left->blue)*interacao.blue_x;
		mask->center->blue -= (1 - mask->left->blue)*interacao.blue_x;
		// Azul em Y
		mask->up->blue += (1 - mask->up->blue)*interacao.blue_y;
		mask->center->blue -= (1 - mask->up->blue)*interacao.blue_y;
	}

	if (interacao.theta >= M_PI_2 && interacao.theta < 3*M_PI_4) {
		// @TO-DO: talvez reduzir uma parte das contas repetidas pra uma variavel temporaria?
		// Vermelho em Y
		mask->down->red += (1 - mask->down->red) * interacao.red_y;
		mask->center->red -= (1 - mask->down->red) * interacao.red_y;
		// Vermelho em X
		mask->left->red += (1 - mask->left->red)*interacao.red_x;
		mask->center->red -= (1 - mask->left->red)*interacao.red_x;
		// Azul em X
		mask->right->blue += (1 - mask->right->blue)*interacao.blue_x;
		mask->center->blue -= (1 - mask->right->blue)*interacao.blue_x;
		// Azul em Y
		mask->up->blue += (1 - mask->up->blue)*interacao.blue_y;
		mask->center->blue -= (1 - mask->up->blue)*interacao.blue_y;
	}

	if (interacao.theta >= 3 * M_PI_4 && interacao.theta < 2*M_PI) {
		// @TO-DO: talvez reduzir uma parte das contas repetidas pra uma variavel temporaria?
		// Vermelho em Y
		mask->up->red += (1 - mask->up->red) * interacao.red_y;
		mask->center->red -= (1 - mask->up->red) * interacao.red_y;
		// Vermelho em X
		mask->left->red += (1 - mask->left->red)*interacao.red_x;
		mask->center->red -= (1 - mask->left->red)*interacao.red_x;
		// Azul em X
		mask->right->blue += (1 - mask->right->blue)*interacao.blue_x;
		mask->center->blue -= (1 - mask->right->blue)*interacao.blue_x;
		// Azul em Y
		mask->down->blue += (1 - mask->down->blue)*interacao.blue_y;
		mask->center->blue -= (1 - mask->down->blue)*interacao.blue_y;
	}


}



#endif // !VECTOR_H


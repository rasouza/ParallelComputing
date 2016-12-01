#include "vector.h"

void interactTwoBodies(double* center, double* target, double qty, omp_lock_t lock)
{
	double delta = (1 - *target) * qty / 4;


	// if (*center - delta < 0.0 || *target  delta > 1.0 )
	// printf("[DEBUG] center: %lf | target: %lf | delta: %lf\n", *center, *target, qty);

    omp_set_lock(&lock);
	*target += delta;
	*center -= delta;
    omp_unset_lock(&lock);

    if (*target < 0.0)
    	*target = 0.0;

    if (*center < 0.0)
    	*center = 0.0;
    

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
	if(interacao.red.x > 1.0 || interacao.red.y > 1.0 || interacao.blue.x > 1.0 || interacao.blue.y > 1.0) {
        // printf("R (%lf, %lf) B (%lf, %lf)\n", interacao.red.x, interacao.red.y, interacao.blue.x, interacao.blue.y);
		// printf("\n[ERRO] Pixel esta com alguma cor em excesso!\n");
    }
	return interacao;
}

Stencil fillStencil(PPMImage *image, int x, int y) {
	Stencil mask;

	mask.x = x;
	mask.y = y;

    mask.up		= &image->data[x-1][y];
    mask.right	= &image->data[x][y+1];
    mask.down	= &image->data[x+1][y];
    mask.left	= &image->data[x][y-1];
	mask.center	= &image->data[x][y];

	return mask;
}

void interact(Stencil *mask, vetor interacao, omp_lock_t lock)
{

	// @TO-DO: Existe algum jeito de fazer ser um bloco de codigo só?

	// P.S. O angulo neste EP começa a partir do eixo vertical Y positivo

	// Angulo no primeiro quadrante
	if (interacao.theta > 0 && interacao.theta < M_PI_4) {       
	    interactTwoBodies(&mask->center->red, &mask->up->red, interacao.red.y, lock); // Vermelho em Y		
        interactTwoBodies(&mask->center->red, &mask->right->red, interacao.red.x, lock); // Vermelho em X		
        interactTwoBodies(&mask->center->blue, &mask->down->blue, interacao.blue.y, lock); // Azul em Y
        interactTwoBodies(&mask->center->blue, &mask->left->blue, interacao.blue.x, lock); // Azul em X
	}

	// Angulo no segundo quadrante
	else if (interacao.theta >= M_PI_4 && interacao.theta < M_PI_2) {
        interactTwoBodies(&mask->center->red, &mask->down->red, interacao.red.y, lock); // Vermelho em Y
        interactTwoBodies(&mask->center->red, &mask->right->red, interacao.red.x, lock); // Vermelho em X	
        interactTwoBodies(&mask->center->blue, &mask->up->blue, interacao.blue.y, lock); // Azul em Y
        interactTwoBodies(&mask->center->blue, &mask->left->blue, interacao.blue.x, lock); // Azul em X
	}

	// Angulo no terceiro quadrante
	else if (interacao.theta >= M_PI_2 && interacao.theta < 3 * M_PI_4) {
        interactTwoBodies(&mask->center->red, &mask->down->red, interacao.red.y, lock); // Vermelho em Y
        interactTwoBodies(&mask->center->red, &mask->left->red, interacao.red.x, lock); // Vermelho em X
        interactTwoBodies(&mask->center->blue, &mask->up->blue, interacao.blue.y, lock); // Azul em Y
        interactTwoBodies(&mask->center->blue, &mask->right->blue, interacao.blue.x, lock); // Azul em X
	}

	// Angulo no quarto quadrante
	else if (interacao.theta >= 3 * M_PI_4 && interacao.theta < 2 * M_PI) {
        interactTwoBodies(&mask->center->red, &mask->up->red, interacao.red.y, lock); // Vermelho em Y
        interactTwoBodies(&mask->center->red, &mask->left->red, interacao.red.x, lock); // Vermelho em X
        interactTwoBodies(&mask->center->blue, &mask->down->blue, interacao.blue.y, lock); // Azul em Y
        interactTwoBodies(&mask->center->blue, &mask->right->blue, interacao.blue.x, lock); // Azul em X
	}


}

int isExcess(PPMPixel pixel)
{

	// printf("pixel.red %lf pixel.blue %lf\n", pixel.red, pixel.blue);
	if (pixel.red > 1.0 || pixel.blue > 1.0)
		return TRUE;

	return FALSE;
}

void checkExcess(PPMImage *image)
{
	for(int i = 0; i < image->y; i++)
		for(int j = 0; j < image->x; j++)
			if (isExcess(image->data[i][j])) {
				Stencil mask = fillStencil(image, i, j);
				shareExcess(&mask);
			}
}

void shareExcess(Stencil *mask)
{
	int count;
	double delta;

	if (mask->center->red > 1.0) {
		count = 0;
		if (mask->up->red < 1.0) count++;
		if (mask->right->red < 1.0) count++;
		if (mask->down->red < 1.0) count++;
		if (mask->up->red < 1.0) count++;

		delta = (mask->center->red - 1.0);
		mask->center->red -= delta;

		if (mask->up->red < 1.0) mask->up->red += delta/count;
		if (mask->right->red < 1.0) mask->right->red += delta/count;
		if (mask->down->red < 1.0) mask->down->red += delta/count;
		if (mask->up->red < 1.0) mask->left->red += delta/count;
	}

	if (mask->center->blue > 1.0) {
		count = 0;
		if (mask->up->blue < 1.0) count++;
		if (mask->right->blue < 1.0) count++;
		if (mask->down->blue < 1.0) count++;
		if (mask->up->blue < 1.0) count++;

		delta = (mask->center->blue - 1.0);
		mask->center->blue -= delta;

		if (mask->up->blue < 1.0) mask->up->blue += delta/count;
		if (mask->right->blue < 1.0) mask->right->blue += delta/count;
		if (mask->down->blue < 1.0) mask->down->blue += delta/count;
		if (mask->up->blue < 1.0) mask->left->blue += delta/count;
	}
}

void rotateTheta(PPMPixel *pixel)
{
	double modulo_v = sqrt(pixel->red*pixel->red + pixel->blue*pixel->blue);

	if (modulo_v != 0.0) {
		double theta = acos(pixel->blue/modulo_v);
		theta += pixel->green * 2 * M_PI;

		if (theta > 2 * M_PI)
			theta -= 2 * M_PI;

		theta = theta / (2*M_PI);

		
		// printf("G: %lf | Theta: %lf | Modulo_v: %lf\n", pixel->green, theta, modulo_v);

		pixel->green = theta;
	}
}

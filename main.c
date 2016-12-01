#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void debugPixel(PPMImage *image, int x, int y);

int main(int argc, char **argv) {
	PPMImage *image;
	vetor interacao;
	Stencil mask;

	int iteracoes = atoi(argv[3]);
	int processadores = atoi(argv[4]);
    omp_lock_t lock;
    omp_init_lock(&lock);
	image = readPPM(argv[1]);

	omp_set_num_threads(processadores);

    #pragma omp parallel  
	for (int iter = 0; iter < iteracoes; iter++) {
		int ROW = image->y;
		int COL = image->x;
		// There will be ROW+COL-1 lines in the output
        #pragma omp for
	    for (int line=1; line<=(ROW + COL -1); line++)
	    {
	        /* Get column index of the first element in this line of output.
	           The index is 0 for first ROW lines and line - ROW for remaining
	           lines  */
	        int start_col =  max(0, line-ROW);
	 
	        /* Get count of elements in this line. The count of elements is
	           equal to minimum of line number, COL-start_col and ROW */
	        int count = min(line, ROW);
	        count = min(count, (COL-start_col));
	 
	        /* Print elements of this line */
	        for (int j=1; j<count-1; j++) {
	        	// printf("(%d, %d)", min(ROW, line)-j-1, start_col+j);
	            mask = fillStencil(image, min(ROW, line)-j-1, start_col+j);
	            interacao = getVetor(*mask.center);
	            interact(&mask, interacao, lock);
	        }

	    }

	   
	    for(int i = 1; i < image->y - 1; i++)
	    	for(int j = 1; j < image->x - 1; j++) {
	    		
				rotateTheta(&image->data[i][j]);
	    	}

    }

    writePPM(argv[2], image);
    
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
	printf("Theta: %lf\nRed: (%lf,%lf)\nBlue: (%lf,%lf)\n\n\n", interacao.theta, interacao.red.x, interacao.red.y, interacao.blue.x, interacao.blue.y);

}

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void debugPixel(PPMImage *image, int x, int y);

int main(int argc, char **argv) {
	/*PPMImage *image;
	vetor interacao;
	Stencil mask;

	int x, y, x_max, y_max, sub_x, sub_y;

	int iteracoes = atoi(argv[3]);
	int processadores = atoi(argv[4]);

	image = readPPM(argv[1]);

	x_max = image->y - 1;
	y_max = image->x - 1;

	omp_set_num_threads(processadores);

	#pragma omp ordered
	for (int i = 0; i < iteracoes; i++) {

		x = 1;
		y = 1;     

	    while (x < x_max - 1 && y < y_max -1) {

	    	// Loop na diagonal, por causa dos vetores de dependencia
	    	#pragma omp parallel
	    	{
	    		int nthreads = omp_get_num_threads();
    			int ithread = omp_get_thread_num();
    			x = (ithread * image->y / nthreads) + 1;
    			x_max = ((ithread + 1) * image->y / nthreads) - 1;

		        for (sub_x = x, sub_y = y; sub_x >= 1 && sub_y < y_max; sub_x--, sub_y++) {
		            mask = fillStencil(image, sub_x, sub_y);
		            interacao = getVetor(*mask.center);
		            interact(&mask, interacao);
		        }
			    

		        if (x < x_max - 1) x++;
		        else if (y < y_max - 1) y++;


		    }
	    }

	    x = 1;
		y = 1; 

	    while (x < x_max - 1 && y < y_max -1) {

	    	// Loop na diagonal, por causa dos vetores de dependencia
	    	#pragma omp parallel
	    	{
	    		int nthreads = omp_get_num_threads();
    			int ithread = omp_get_thread_num();
    			x = (ithread * image->y / nthreads) + 1;
    			x_max = ((ithread + 1) * image->y / nthreads) - 1;

		        for (sub_x = x, sub_y = y; sub_x >= 1 && sub_y < y_max; sub_x--, sub_y++)
		            rotateTheta(&image->data[sub_x][sub_y]);
	
		        if (x < x_max - 1) x++;
		        else if (y < y_max - 1) y++;

	        }
	    }
	}
   
	writePPM(argv[2], image);*/

	// int dim = 5;
	// for( int k = 0 ; k < dim * 2 ; k++ ) {
 //        for( int j = 0 ; j <= k ; j++ ) {
 //            int i = k - j;
 //            if(( i < dim && j < dim ) && (i != 0 && i != dim - 1 && j != 0 && j != dim - 1) ) {
 //                printf("(%d, %d)", i, j);;
 //            }
 //        }
 //        printf("\n");
 //    }

	int ROW = 10;
	int COL = 10;
	// There will be ROW+COL-1 lines in the output
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
        for (int j=1; j<count-1; j++)
            printf("(%d, %d) ", min(ROW, line)-j-1, start_col+j);
 
        /* Ptint elements of next diagonal on next line */
        printf("\n");
    }
    
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

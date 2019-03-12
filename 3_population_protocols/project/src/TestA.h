#ifndef TestA_h
#define TestA_h

#include "Main.h"

void testA()
{
    printf("Test A: ");

    int N = 5;
    int s = (N+1)*(N+2)/2;
    FILE* fp=fopen("TestA.csv", "w");

    auto* matrix = new Matrix(N);
    auto* montecarlo = new MonteCarlo(N);

    fill(matrix);
    gauss(matrix,false);
    montecarlo->experiment( 1000 , false );

    fprintf(fp,"gauss;montecarlo\n");
    for(int i=0; i<s; i++)
        fprintf(fp,"%f;%f\n",matrix->getVectorX(i),montecarlo->getResult(i));

    fclose(fp);
    printf("done\n");

    delete(matrix);
    delete(montecarlo);
}




#endif

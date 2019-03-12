#ifndef Jacobi_h
#define Jacobi_h

#include "Main.h"

template <typename T>
void jacobi( T *matrix , int times ) {

    int size = matrix->getMSize();
    double *tempX = new double[size];

    for(int t=0; t<times; t++)
    {
        for(int i=0; i<size; i++)
        {
            tempX[i] = matrix->getVectorB(i);
            for(int j=0; j<size; j++)
            {
                if (j!=i)
                {
                    tempX[i] += matrix->getMatrixA(i,j) * matrix->getVectorX(j);
                }
            }
            tempX[i] = tempX[i] / abs(matrix->getMatrixA(i,i));
        }
        for(int k=0; k<size; k++)
        {
            matrix->setVectorX( k , tempX[k] );
        }
    }
    delete tempX;
}

#endif

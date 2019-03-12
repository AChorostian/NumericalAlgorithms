#ifndef Seidel_h
#define Seidel_h

#include "Main.h"

template <typename T>
void seidel( T *matrix , int times ) {

    int size = matrix->getMSize();
    double tempX;

    for(int t=0; t<times; t++)
    {
        for(int i=0; i<size; i++) // wiersz
        {
            tempX = matrix->getVectorB(i);
            for(int j=0; j<size; j++) // kolumna
            {
                if (j!=i)
                {
                    tempX += matrix->getMatrixA(i,j) * matrix->getVectorX(j);
                }
            }
            matrix->setVectorX( i , tempX / abs(matrix->getMatrixA(i,i)) );
        }
    }
}

template <typename T>
int seidelPrec( T *matrix , double precission )
{
    int size = matrix->getMSize();
    int init=0;
    double tempX;
    do
    {
        init++;
        for(int i=0; i<size; i++) // wiersz
        {
            tempX = matrix->getVectorB(i);
            for(int j=0; j<size; j++) // kolumna
            {
                if (j!=i)
                {
                    tempX += matrix->getMatrixA(i,j) * matrix->getVectorX(j);
                }
            }
            matrix->setVectorX( i , tempX / abs(matrix->getMatrixA(i,i)) );
        }
    }
    while (init <5 || precission < multiplicationprec(matrix,size));
    return init;
}

#endif

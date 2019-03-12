#ifndef Gauss_h
#define Gauss_h

#include "Main.h"

template <typename T>
void gauss(T *matrix, bool faster) {
    int size = matrix->getMSize();

    for (int n = 1; n < size ; n++)
    {
        // wybieranie max elementu
        int maxIndex = n - 1;
        double maxValue = matrix->getMatrixA( n-1 , n-1 );

        for (int i = n-1; i < size; i++)
        {
            if ( abs(matrix->getMatrixA(i,n-1)) > abs(maxValue) )
            {
                maxIndex = i;
                maxValue = matrix->getMatrixA(i,n-1);
            }
        }
        if ( maxIndex != n-1 )
        {
            // zamiana max elementu
            matrix->swapRows( maxIndex , n-1 );
        }
        // liczenie gaussa
        for (int y = n; y < size; y++)
        {
            if ( !faster || matrix->getMatrixA(y,n-1) != 0) // pomijanie dla 0
            {
                double a = matrix->getMatrixA( y , n - 1  ) / matrix->getMatrixA( n - 1 , n - 1 );
                for (int x = n - 1; x < size; x++)
                    matrix->setMatrixA( y , x , matrix->getMatrixA( y , x ) - ( a * matrix->getMatrixA( n-1 , x ) ) );
                matrix->setVectorB( y , matrix->getVectorB(y) - (a * matrix->getVectorB(n - 1) ) );
            }
        }
    }
    // wyciaganie wyniku z macierzy trojkatnej
    for (int y = size - 1; y >= 0; y--)
    {
        matrix->setVectorX( y , matrix->getVectorB(y) / matrix->getMatrixA(y,y) );

        for (int x = size - 1; x > y; x--)
        {
            matrix->setMatrixA( y , x , matrix->getMatrixA(y,x) / matrix->getMatrixA(y,y) );
            matrix->setVectorX( y , matrix->getVectorX(y) - (matrix->getMatrixA(y,x) * matrix->getVectorX(x)) );
        }
    }
}

#endif

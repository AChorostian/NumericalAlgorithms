#ifndef Multiplication_h
#define Multiplication_h

#include "Main.h"

template <typename T>
double multiplication( T* matrix , int size )
{
    auto* matrixclear= new T(matrix->getSize());
    fill(matrixclear);

    double tempB;
    double diff=0;
    for(int i=0; i<size ; i++)
    {
        tempB=0;
        for(int j=0; j<size ; j++)
            tempB += matrixclear->getMatrixA(i,j) * matrix->getVectorX(j);

        if(i!=size-1)
            diff += abs(tempB);
        else
            diff += abs(1-tempB);
    }
    delete matrixclear;
    return diff/size;
}

template <typename T>
double multiplicationprec( T* matrix , int size )
{
    auto* matrixclear= new T(matrix->getSize());
    fill(matrixclear);

    double tempB;
    double diff=0;
    for(int i=0; i<size ; i++)
    {
        tempB=0;
        for(int j=0; j<size ; j++)
            tempB += matrixclear->getMatrixA(i,j) * matrix->getVectorX(j);

        if(i!=size-1)
        {
            if (abs(tempB) > diff)
                diff = abs(tempB);
        }
        else
        {
            if (abs(1-tempB) > diff)
                diff = abs(1-tempB);
        }
    }
    delete(matrixclear);
    return diff;
}



#endif
